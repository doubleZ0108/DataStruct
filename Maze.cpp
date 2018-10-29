#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
using namespace std;

#define ACC 0		//ACC代表这个位置是通路
#define OBS 1		//OBS为障碍物

struct Point
{
	int x, y;
	Point() = default;
	Point(int a,int b):x(a),y(b){}
	bool operator==(const Point &rhv);
};
struct Offsets
{
	Point pos;			//方向向量
	const char *dir;	//方向名字
};
Offsets Move[4] = { { Point(-1,0),"N"},{ Point(0,1),"E"},
					{ Point(1,0),"S"},{ Point(0,-1),"W"}, };
	//四个方位的向量

bool SeekPath(Point now, const Point dest, 
	vector<vector<int> > &Maze, vector<vector<int> > &mark, list<Point> &AccessLink)
	//当前位置 终点位置 整张地图 记录哪些点走过了的地图 结果链表用于记录每一步的坐标
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

		if (Maze[buf.pos.x][buf.pos.y] == ACC && mark[buf.pos.x][buf.pos.y] == 0)
			//如果地图上这个点可以走 && 以前没往这尝试过
		{
			mark[buf.pos.x][buf.pos.y] = 1;		//往这尝试的时候把mark地图修改一下

			if (SeekPath(buf.pos, dest, Maze, mark, AccessLink))
			{
				AccessLink.push_front(buf.pos);		//因为是在递归之后的语句所以会逆序进行
								//因此这里选择了往链表的头上插入,人工把结果再逆一遍就正了
				Maze[buf.pos.x][buf.pos.y] = 5;		//地图上显示走的路径
				return true;
			}
		}
	}

	return false;
}

void FindGap(int row, int col, const vector<vector<int> > &Maze, 
	Point &start, Point &dest)
//在地图上找出发点和终点的位置坐标
//做法是在地图的四周找唯一的两个ACC, 然后随机赋值给出发点和终点
//默认是四周有且仅有两个ACC
{
	int i, j;
	int cnt = 0;
	//上
	for (int j = 0; j < col; ++j)
	{
		if (Maze[0][j] == ACC)
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
		if (Maze[row - 1][j] == ACC)
		{
			++cnt;
			if (cnt == 1)
			{
				start = Point(row-1, j);
			}
			else if (cnt == 2)
			{
				dest = Point(row-1, j);
				return;
			}
		}
	}
	//左
	for (i = 1; i < row - 1; ++i)
	{
		if (Maze[i][0] == ACC)
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
		if (Maze[i][col - 1] == ACC)
		{
			++cnt;
			if (cnt == 1)
			{
				start = Point(i, col-1);
			}
			else if (cnt == 2)
			{
				dest = Point(i, col-1);
				return;
			}
		}
	}
}

int main(void)
{
	int row, col; 
	cout << "请输入迷宫行数和列数: ";
	cin >> row >> col;
	vector<vector<int> > Maze(row, vector<int>(col, 0));
	vector<vector<int> > mark(row, vector<int>(col, 0));

	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			mark[i][j] = 0;
			cin >> Maze[i][j];
		}
	}
	
	//寻找出发点和终点坐标
	Point start, dest;
	FindGap(row, col, Maze, start, dest);

	mark[start.x][start.y] = 1;		//出发点位置坐标
	list<Point> AccessLink;
	if (SeekPath(start, dest, Maze, mark, AccessLink))
	{
		AccessLink.push_front(start);
		Maze[start.x][start.y] = 5;
	}


	if (AccessLink.size() > 1)
	{
		Point save = AccessLink.back();
		AccessLink.pop_back();
		for (list<Point>::iterator liter = AccessLink.begin(); liter != AccessLink.end(); ++liter)
		{
			printf("(%d, %d)->", (*liter).x, (*liter).y);
		}
		printf("(%d, %d)", save.x, save.y);
	}
	else
	{
		cout << "此迷宫无解!\n";
	}



	cout << endl<< "**********************" << endl;
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
			printf("%-3d", Maze[i][j]);
		}
		cout << endl;
	}

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
			printf("%-3d", mark[i][j]);
		}
		cout << endl;
	}

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

