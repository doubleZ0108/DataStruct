#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>
using namespace std;

#define ACC 0		//ACC�������λ����ͨ·
#define OBS 1		//OBSΪ�ϰ���

struct Point
{
	int x, y;
	Point() = default;
	Point(int a, int b) :x(a), y(b) {}
	bool operator==(const Point &rhv);
};
struct Offsets
{
	Point pos;			//��������
	const char *dir;	//��������
};
Offsets Move[4] = { { Point(-1,0),"N" },{ Point(0,1),"E" },
{ Point(1,0),"S" },{ Point(0,-1),"W" }, };
//�ĸ���λ������

class Maze
{
private:
	int row, col;
	vector<vector<int> > Map;		//��ͼ
	vector<vector<int> > mark;		//��ǵ�ͼ, �����ж�ĳ��λ���Ƿ��Ѿ��߹�

	Point start, dest;				//�����յ�

	stack<Point> AccessStack;		//ʹ�ù���ջ�����н��и��������
public:
	Maze() = default;
	Maze(int _row, int _col);

	void InitMap();					//�����Թ���ͼ
	void FindGap();					//Ѱ�������յ�
	void showGap();					//��ʾ�����յ�

	void SeekPath();				//�޲ε�Ѱ·����
	bool SeekPath(Point now);		//�ݹ���õ�Ѱ·����

	void showRoute();				//��ʾѰ·�Ľ��
	void showMap();					//�����ͼ
};

int main(void)
{
	int row, col;
	cout << "�������Թ�����������: ";
	cin >> row >> col;
	
	/*���� row*col �ߴ�ĵ�ͼ*/
	Maze maze(row, col);

	/*�����ͼ*/
	cout << "�������Թ���ͼ: " << endl;
	maze.InitMap();

	/*Ѱ�ҳ�������յ�����*/
	maze.FindGap();

	/*������: ��ʾ������������յ�����*/
	//maze.showGap();

	/*Ѱ·�㷨*/
	maze.SeekPath();

	/*����ҵ���·�������޽���Ϣ*/
	maze.showRoute();

	/*������: ���Ѱ·��ĵ�ͼ*/
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
	//����row��col�е��Թ�
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
//�ڵ�ͼ���ҳ�������յ��λ������
//�������ڵ�ͼ��������Ψһ������ACC, Ȼ�������ֵ����������յ�
//Ĭ�����������ҽ�������ACC
{
	int i, j;
	int cnt = 0;
	//��
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
	//��
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
	//��
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
	//��
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
	mark[start.x][start.y] = 1;			//������λ������

	if (SeekPath(start))
	{
		AccessStack.push(start);		//������Թ��н�,�����ʼ��λ��ѹ��ջ��
		Map[start.x][start.y] = 5;
	}
}

bool Maze::SeekPath(Point now)
//��ǰλ�� �յ�λ�� ���ŵ�ͼ ��¼��Щ���߹��˵ĵ�ͼ ���ջ���ڼ�¼ÿһ��������
{
	Offsets buf;	//��������������ߵ��������

	if (now == dest) { return true; }	//����ҵ��յ��˾��˳��ݹ鲢����true

	for (int i = 0; i < 4; ++i)
		//4�����򶼳���һ���ܲ�����
	{
		buf.pos.x = now.x + Move[i].pos.x;
		buf.pos.y = now.y + Move[i].pos.y;
		buf.dir = Move[i].dir;

		if (buf.pos.x < 0 || buf.pos.y < 0) { continue; }	//�����̽���߳��˵�ͼ��ֱ�ӻ�����

		if (Map[buf.pos.x][buf.pos.y] == ACC && mark[buf.pos.x][buf.pos.y] == 0)
			//�����ͼ������������ && ��ǰû���Ⳣ�Թ�
		{
			mark[buf.pos.x][buf.pos.y] = 1;		//���Ⳣ�Ե�ʱ���mark��ͼ�޸�һ��

			if (SeekPath(buf.pos))
			{
				AccessStack.push(buf.pos);
				//��Ϊֻ�����һ��������,�ſ��԰�����ѹ��ջ��
				//����ʹ�ú���ȳ��Ľṹ�����н��и��������
				Map[buf.pos.x][buf.pos.y] = 5;		//��ͼ����ʾ�ߵ�·��
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
		printf("(%d, %d)\n", buf.x, buf.y);		//���һ����㲻�����ͷ
	}
	else
	{
		cout << "���Թ��޽�!\n";
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
