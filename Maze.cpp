#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
using namespace std;
#define ACC 0
#define OBS 1
struct Point
{
	int x, y;
	Point() = default;
	Point(int a,int b):x(a),y(b){}
	bool operator==(const Point &rhv);
};
struct Offsets
{
	Point pos;
	const char *dir;

};
Offsets Move[8] = { { Point(-1,0),"N"},{ Point(-1,1),"NE"},{ Point(0,1),"E"},{ Point(1,1),"SE"},
					{ Point(1,0),"S"},{ Point(1,-1),"SW"},{ Point(0,-1),"W"},{ Point(-1,-1),"NW"} };

bool SeekPath(Point now, const Point dest, 
	vector<vector<int> > &Maze, vector<vector<int> > &mark, list<Point> &AccessLink)
{
	Offsets buf;

	if (now == dest) { return true; }

	for (int i = 0; i < 8; ++i)
	{
		buf.pos.x = now.x + Move[i].pos.x;
		buf.pos.y = now.y + Move[i].pos.y;
		buf.dir = Move[i].dir;

		if (Maze[buf.pos.x][buf.pos.y] == ACC && mark[buf.pos.x][buf.pos.y] == 0)
		{
			mark[buf.pos.x][buf.pos.y] = 1;

			if (SeekPath(buf.pos, dest, Maze, mark, AccessLink))
			{
				AccessLink.push_front(buf.pos);
				Maze[buf.pos.x][buf.pos.y] = 5;
				return true;
			}
		}
	}

	return false;
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

	mark[1][0] = 1;
	list<Point> AccessLink;
	if (SeekPath(Point(1, 0), Point(row - 2, col - 1), Maze, mark, AccessLink))
	{
		printf("(1, 0) dirction E\n\n");
		Maze[1][0] = 5;
	}

	for (auto liter = AccessLink.begin(); liter != AccessLink.end(); ++liter)
	{
		printf("(%d, %d)->", (*liter).x, (*liter).y);
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

