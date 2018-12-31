#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>
using namespace std;

#define ACC 0		//ACC代表这个位置是通路
#define OBS 1		//OBS为障碍物

struct Point
{
	int x, y;
	Point() = default;
	Point(int a, int b) :x(a), y(b) {}
	bool operator==(const Point &rhv);
};
struct Offsets
{
	Point pos;			//方向向量
	const char *dir;	//方向名字
};
Offsets Move[4] = { { Point(-1,0),"N" },{ Point(0,1),"E" },
{ Point(1,0),"S" },{ Point(0,-1),"W" }, };
//四个方位的向量

class Maze
{
private:
	int row, col;
	vector<vector<int> > Map;		//地图
	vector<vector<int> > mark;		//标记地图, 用于判定某个位置是否已经走过

	Point start, dest;				//起点和终点

	stack<Point> AccessStack;		//使用工作栈储存行进中各点的坐标
public:
	Maze() = default;
	Maze(int _row, int _col);

	void InitMap();					//输入迷宫地图
	void FindGap();					//寻找起点和终点
	void showGap();					//显示起点和终点

	void SeekPath();				//无参的寻路函数
	bool SeekPath(Point now);		//递归调用的寻路函数

	void showRoute();				//显示寻路的结果
	void showMap();					//输出地图
};

int main(void)
{
	int row, col;
	cout << "请输入迷宫行数和列数: ";
	cin >> row >> col;
	
	/*创建 row*col 尺寸的地图*/
	Maze maze(row, col);

	/*读入地图*/
	cout << "请输入迷宫地图: " << endl;
	maze.InitMap();

	/*寻找出发点和终点坐标*/
	maze.FindGap();

	/*调试用: 显示出发点坐标和终点坐标*/
	//maze.showGap();

	/*寻路算法*/
	maze.SeekPath();

	/*输出找到的路径或者无解信息*/
	maze.showRoute();

	/*调试用: 输出寻路后的地图*/
	//maze.showMap();


	system("pause");
	return 0;
}

bool Point::operator==(const Point &rhv)
{
	if (this->x == rhv.x && this->y == rhv.y)
	{
		return true;
	}
	else { return false; }
}


Maze::Maze(int _row, int _col)
	:row(_row),col(_col)
{
	Map.resize(row, vector<int>(col, 0));
	mark.resize(row, vector<int>(col, 0));
}

void Maze::InitMap()
{
	//读入row行col列的迷宫
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			mark[i][j] = 0;
			cin >> Map[i][j];
		}
	}
}

void Maze::FindGap()
//在地图上找出发点和终点的位置坐标
//做法是在地图的四周找唯一的两个ACC, 然后随机赋值给出发点和终点
//默认是四周有且仅有两个ACC
{
	int i, j;
	int cnt = 0;
	//上
	for (int j = 0; j < col; ++j)
	{
		if (Map[0][j] == ACC)
		{
			++cnt;
			if (cnt == 1)
			{
				start = Point(0, j);
			}
			else if (cnt == 2)
			{
				dest = Point(0, j);
				return;
			}
		}
	}
	//下
	for (j = 0; j < col; ++j)
	{
		if (Map[row - 1][j] == ACC)
		{
			++cnt;
			if (cnt == 1)
			{
				start = Point(row - 1, j);
			}
			else if (cnt == 2)
			{
				dest = Point(row - 1, j);
				return;
			}
		}
	}
	//左
	for (i = 1; i < row - 1; ++i)
	{
		if (Map[i][0] == ACC)
		{
			++cnt;
			if (cnt == 1)
			{
				start = Point(i, 0);
			}
			else if (cnt == 2)
			{
				dest = Point(i, 0);
				return;
			}
		}
	}
	//右
	for (i = 1; i < row - 1; ++i)
	{
		if (Map[i][col - 1] == ACC)
		{
			++cnt;
			if (cnt == 1)
			{
				start = Point(i, col - 1);
			}
			else if (cnt == 2)
			{
				dest = Point(i, col - 1);
				return;
			}
		}
	}
}

void Maze::showGap()
{
	printf("\n///////////////////////////////////////////////\n");
	printf("the start pos is (%d, %d)\n", start.x, start.y);
	printf("the dest pos is (%d, %d)\n", dest.x, dest.y);
	printf("///////////////////////////////////////////////\n\n");
}

void Maze::SeekPath()
{
	mark[start.x][start.y] = 1;			//出发点位置坐标

	if (SeekPath(start))
	{
		AccessStack.push(start);		//如果此迷宫有解,则把起始点位置压入栈中
		Map[start.x][start.y] = 5;
	}
}

bool Maze::SeekPath(Point now)
//当前位置 终点位置 整张地图 记录哪些点走过了的地图 结果栈用于记录每一步的坐标
{
	Offsets buf;	//假设往这个方向走的替代变量

	if (now == dest) { return true; }	//如果找到终点了就退出递归并返回true

	for (int i = 0; i < 4; ++i)
		//4个方向都尝试一遍能不能走
	{
		buf.pos.x = now.x + Move[i].pos.x;
		buf.pos.y = now.y + Move[i].pos.y;
		buf.dir = Move[i].dir;

		if (buf.pos.x < 0 || buf.pos.y < 0) { continue; }	//如果试探的走出了地图则直接换方向

		if (Map[buf.pos.x][buf.pos.y] == ACC && mark[buf.pos.x][buf.pos.y] == 0)
			//如果地图上这个点可以走 && 以前没往这尝试过
		{
			mark[buf.pos.x][buf.pos.y] = 1;		//往这尝试的时候把mark地图修改一下

			if (SeekPath(buf.pos))
			{
				AccessStack.push(buf.pos);
				//因为只有最后一步可以走,才可以把坐标压入栈中
				//所以使用后进先出的结构储存行进中各点的坐标
				Map[buf.pos.x][buf.pos.y] = 5;		//地图上显示走的路径
				return true;
			}
		}
	}

	return false;
}

void Maze::showRoute()
{
	cout << endl;
	if (!AccessStack.empty())
	{
		Point buf;
		for (buf = AccessStack.top(); AccessStack.size() != 1; buf = AccessStack.top())
		{
			AccessStack.pop();
			printf("(%d, %d)->", buf.x, buf.y);
		}
		printf("(%d, %d)\n", buf.x, buf.y);		//最后一个结点不输出箭头
	}
	else
	{
		cout << "此迷宫无解!\n";
	}
}

void Maze::showMap()
{
	cout << endl << "**********************" << endl;
	printf("   ");
	for (int i = 0; i < col; ++i)
	{
		printf("%-3d", i);
	}
	cout << endl;
	for (int i = 0; i < row; ++i)
	{
		printf("%-3d", i);
		for (int j = 0; j < col; ++j)
		{
			printf("%-3d", Map[i][j]);
		}
		cout << endl;
	}
}
