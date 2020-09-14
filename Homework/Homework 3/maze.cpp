/*#include <iostream>
using namespace std;*/

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	if (sr == er && sc == ec)
		return true;
	
	maze[sr][sc] = 'C';

	if (maze[sr + 1][sc] != 'X' && maze[sr + 1][sc] != 'C') {
		bool b = pathExists(maze, sr + 1, sc, er, ec);
		if (b) return true;
	}
	if (maze[sr][sc-1] != 'X' && maze[sr][sc-1] != 'C') {
		bool b = pathExists(maze, sr, sc-1, er, ec);
		if (b) return true;
	}
	if (maze[sr - 1][sc] != 'X' && maze[sr - 1][sc] != 'C') {
		bool b = pathExists(maze, sr - 1, sc, er, ec);
		if (b) return true;
	}
	if (maze[sr][sc + 1] != 'X' && maze[sr][sc + 1] != 'C') {
		bool b = pathExists(maze, sr, sc + 1, er, ec);
		if (b) return true;
	}

return false;
}

/*
int main()
{
	char maze[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X' },
		{ 'X','.','X','.','.','X','.','.','.','X' },
		{ 'X','.','X','X','.','X','X','.','.','X' },
		{ 'X','X','X','.','.','.','.','X','.','X' },
		{ 'X','.','X','X','X','.','X','X','X','X' },
		{ 'X','.','X','.','.','.','X','.','.','X' },
		{ 'X','.','.','.','X','.','X','.','.','X' },
		{ 'X','X','X','X','X','.','X','.','X','X' },
		{ 'X','.','.','.','.','.','.','.','.','X' },
		{ 'X','X','X','X','X','X','X','X','X','X' }
	};

	if (pathExists(maze, 2, 2, 8, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}*/