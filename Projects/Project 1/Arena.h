#ifndef ARENA_H
#define ARENA_H

#include "History.h"
#include "globals.h"

using namespace std;


class Player;
class Vampire;


class Arena
{
public:
	// Constructor/destructor
	Arena(int nRows, int nCols);
	~Arena();
	History& history(); 

	// Accessors
	int     rows() const;
	int     cols() const;
	Player* player() const;
	int     vampireCount() const;
	int     getCellStatus(int r, int c) const;
	int     numberOfVampiresAt(int r, int c) const;
	void    display(string msg) const;

	// Mutators
	void setCellStatus(int r, int c, int status);
	bool addVampire(int r, int c);
	bool addPlayer(int r, int c);
	void moveVampires();


private:
	int      m_grid[MAXROWS][MAXCOLS];
	int      m_rows;
	int      m_cols;
	Player* m_player;
	Vampire* m_vampires[MAXVAMPIRES];
	int      m_nVampires;
	int      m_turns;
		History m_history;

	// Helper functions
	void checkPos(int r, int c, string functionName) const;
	bool isPosInBounds(int r, int c) const;
};

bool attemptMove(const Arena& a, int dir, int& r, int& c);
bool recommendMove(const Arena& a, int r, int c, int& bestDir);
int computeDanger(const Arena& a, int r, int c);

#endif // !ARENA_H

