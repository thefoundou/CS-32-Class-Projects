#include <iostream>
#include <stack>

using namespace std;

//class Coord;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

int main()
{
	char maze[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X' },
		{ 'X','.','X','.','.','X','.','.','.','X' },
		{ 'X','.','X','X','.','X','X','.','.','X' },
		{ 'X','.','X','.','.','.','.','X','.','X' },
		{ 'X','.','X','X','X','.','X','X','X','X' },
		{ 'X','.','X','.','.','.','X','.','.','X' },
		{ 'X','.','X','.','X','.','X','.','.','X' },
		{ 'X','.','X','X','X','.','X','.','X','X' },
		{ 'X','.','.','.','.','.','.','.','.','X' },
		{ 'X','X','X','X','X','X','X','X','X','X' }
	};

	if (pathExists(maze, 1, 1, 8, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}


class Coord
{
public:
	Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
	int r() const { return m_row; }
	int c() const { return m_col; }
private:
	int m_row;
	int m_col;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
	// Return true if there is a path from (sr,sc) to (er,ec)
	// through the maze; return false otherwise

	stack<Coord> coordStack;

	Coord a(sr, sc);
	coordStack.push(a);
	Coord end(er, ec);

	maze[sr][sc] = 'C';

	while (!coordStack.empty()) {
		Coord b = coordStack.top();
		coordStack.pop();

		if (b.r() == end.r() && b.c() == end.c())
			return true;
		if (maze[b.r() + 1][b.c()] != 'X' && maze[b.r() + 1][b.c()] != 'C') {
			Coord c(b.r() + 1, b.c());
			coordStack.push(c);
			maze[b.r() + 1][b.c()] = 'C';
		}
		if (maze[b.r()][b.c() - 1] != 'X' && maze[b.r()][b.c() - 1] != 'C') {
			Coord c(b.r(), b.c() - 1);
			coordStack.push(c);
			maze[b.r()][b.c() - 1] = 'C';
		}
		if (maze[b.r() - 1][b.c()] != 'X' && maze[b.r() - 1][b.c()] != 'C') {
			Coord c(b.r() - 1, b.c());
			coordStack.push(c);
			maze[b.r() - 1][b.c()] = 'C';
		}
		if (maze[b.r()][b.c() + 1] != 'X' && maze[b.r()][b.c() + 1] != 'C') {
			Coord c(b.r(), b.c() + 1);
			coordStack.push(c);
			maze[b.r()][b.c() + 1] = 'C';
		}
	}

	return false;
}

