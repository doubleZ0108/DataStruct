#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
using namespace std;

#define ACC 0		//ACC�������λ����ͨ·
#define OBS 1		//OBSΪ�ϰ���

struct Point
{
	int x, y;
	Point() = default;
	Point(int a,int b):x(a),y(b){}
	bool operator==(const Point &rhv);
};
struct Offsets
{
	Point pos;			//��������
	const char *dir;	//��������
};
Offsets Move[4] = { { Point(-1,0),"N"},{ Point(0,1),"E"},
					{ Point(1,0),"S"},{ Point(0,-1),"W"}, };
	//�ĸ���λ������

bool SeekPath(Point now, const Point dest, 
	vector<vector<int> > &Maze, vector<vector<int> > &mark, list<Point> &AccessLink)
	//��ǰλ�� �յ�λ�� ���ŵ�ͼ ��¼��Щ���߹��˵ĵ�ͼ ����������ڼ�¼ÿһ��������
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

		if (Maze[buf.pos.x][buf.pos.y] == ACC && mark[buf.pos.x][buf.pos.y] == 0)
			//�����ͼ������������ && ��ǰû���Ⳣ�Թ�
		{
			mark[buf.pos.x][buf.pos.y] = 1;		//���Ⳣ�Ե�ʱ���mark��ͼ�޸�һ��

			if (SeekPath(buf.pos, dest, Maze, mark, AccessLink))
			{
				AccessLink.push_front(buf.pos);		//��Ϊ���ڵݹ�֮���������Ի��������
								//�������ѡ�����������ͷ�ϲ���,�˹��ѽ������һ�������
				Maze[buf.pos.x][buf.pos.y] = 5;		//��ͼ����ʾ�ߵ�·��
				return true;
			}
		}
	}

	return false;
}

void FindGap(int row, int col, const vector<vector<int> > &Maze, 
	Point &start, Point &dest)
//�ڵ�ͼ���ҳ�������յ��λ������
//�������ڵ�ͼ��������Ψһ������ACC, Ȼ�������ֵ����������յ�
//Ĭ�����������ҽ�������ACC
{
	int i, j;
	int cnt = 0;
	//��
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
	//��
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
	//��
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
	//��
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
	cout << "�������Թ�����������: ";
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
	
	//Ѱ�ҳ�������յ�����
	Point start, dest;
	FindGap(row, col, Maze, start, dest);

	mark[start.x][start.y] = 1;		//������λ������
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
		cout << "���Թ��޽�!\n";
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

