#ifndef HISTORY_H
#define HISTORY_H

#include "globals.h"

using namespace std;


class History
{
public:
	History(int nRows, int nCols);
	bool	record(int r, int c);
	void	display() const;

private:
	int		m_row;
	int		m_col;
	int		m_grid[MAXROWS][MAXCOLS];
	char	m_grid1[MAXROWS][MAXCOLS];
};

#endif // !HISTORY_H