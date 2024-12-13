﻿#include <iostream>

#include "../shared/Stack.h"

using namespace std;

constexpr int kNumRows = 10;
constexpr int kNumCols = 9;

char maze[kNumRows][kNumCols] =
	{
		{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', 'S', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '0', '1', '0', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '0', '1', '1', '1'},
		{'1', '1', '1', '0', '0', '0', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', 'G', '1'}, // <- 'G'를 만나면 종료
		{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
};

void PrintMaze()
{
	for (int j = 0; j < kNumRows; j++)
	{
		for (int i = 0; i < kNumCols; i++)
			cout << maze[j][i] << " ";
		cout << endl;
	}
}

struct Pos
{
	int row;
	int col;

	// 디버깅을 위한 편의 기능
	friend ostream &operator<<(ostream &os, const Pos &pos)
	{
		cout << "(" << pos.row << ", " << pos.col << ")" << flush;
		return os;
	}
};

void RecurMaze(Pos p)
{
	const char mark = maze[p.row][p.col];

	if (mark == 'G')
	{
		cout << "Found!" << endl;
		return;
	}

	// 방문했던 적이 없고 ('X'가 아니고)
	// 벽도 아닌 경우 ('1'도 아닌 경우)
	if (mark != 'X' && mark != '1')
	{
		maze[p.row][p.col] = 'X';

		RecurMaze({p.row + 1, p.col});
		RecurMaze({p.row, p.col + 1});
		RecurMaze({p.row - 1, p.col});
		RecurMaze({p.row, p.col - 1});
	}
}

// 조기 종료가 가능한 버전
int RecurMazeEarly(Pos p)
{
	const char mark = maze[p.row][p.col];

	if (mark == 'G')
	{
		cout << "Found!" << endl;
		return 1;
	}

	// 방문했던 적이 없고 ('X'가 아니고)
	// 벽도 아닌 경우 ('1'도 아닌 경우)
	if (mark != 'X' && mark != '1')
	{
		maze[p.row][p.col] = 'X';

		if(RecurMazeEarly({p.row + 1, p.col}) == 1) return 1;
		if(RecurMazeEarly({p.row, p.col + 1}) == 1) return 1;
		if(RecurMazeEarly({p.row - 1, p.col}) == 1) return 1;
		if(RecurMazeEarly({p.row, p.col - 1}) == 1) return 1;
	}
	return 0;
}

void StackMaze()
{
	Stack<Pos> s;

	Pos start = {1, 1}; // i = 1, j = 1  시작 지점
	// Pos start;
	// start.row = 1;
	// start.col = 1;

	s.Push(start); // s.Push({1, 1});

	// s.Print(); // 디버깅에 사용 가능

	while (!s.IsEmpty())
	{
		Pos p = s.Top();
		s.Pop();

		cout << p << " "; // 디버깅 출력

		const char mark = maze[p.row][p.col];

		if (mark == 'G')
		{
			cout << "Found!" << endl;
			break;
		}

		if (mark != 'X' && mark != '1')
		{
			maze[p.row][p.col] = 'X';

			s.Push({p.row + 1, p.col});
			s.Push({p.row, p.col + 1});
			s.Push({p.row - 1, p.col});
			s.Push({p.row, p.col - 1});
		}
	}
}

int main()
{
	PrintMaze();

	cout << "-----------------" << endl;
	// RecurMaze({ 1, 1 });
	// RecurMazeEarly({1, 1});
	StackMaze();

	PrintMaze();

	return 0;
}
