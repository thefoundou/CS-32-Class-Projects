#include <iostream>
#include "History.h"

using namespace std;

History::History(int nRows, int nCols) // MAKE SURE THIS DOES NOT INITIALIZE THINGS WRONG
{
	m_row = nRows;
	m_col = nCols;

	// Initialize the array which counts number of viles //
	int r, c;
	for (r = 1; r <= m_row; r++)
		for (c = 1; c <= m_col; c++)
			m_grid[r-1][c-1] = 0;

	// Initialize the array that displays this count to player //
	int r1, c1;
	for (r1 = 1; r1 <= m_row; r1++)
		for (c1 = 1; c1 <= m_col; c1++)
			m_grid1[r1-1][c1-1] = '.';
}

bool History::record(int r, int c)
{
	if (r < 1 || r > m_row || c < 1 || c > m_col)
	{
		return false;
	}
	
	m_grid[r - 1][c - 1]++; //Increment count on this spot

	// Recording first vial on spot

	if (m_grid[r - 1][c - 1] == 1) {
		m_grid1[r - 1][c - 1] = 'A';
		return true;
	}

	// Recording 26 or more vials on spot

	else if (m_grid[r - 1][c - 1] == 26) {
		m_grid1[r - 1][c - 1] = 'Z';
		return true;
	}

	// Incrementing from cases between 'A' and 'Z'

	else {
		m_grid1[r - 1][c - 1]++;
		return true;
	}
}

void History::display() const
{
	int r, c;

	clearScreen();
	for (r = 1; r <= m_row; r++)
	{
		for (c = 1; c <= m_col; c++)
			cout << m_grid1[r - 1][c - 1];
		cout << endl;
	}
	cout << endl;

}