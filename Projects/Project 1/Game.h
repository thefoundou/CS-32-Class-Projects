#ifndef GAME_H
#define GAME_H

using namespace std;

#include "Arena.h"

class Arena;

class Game
{
public:
	// Constructor/destructor
	Game(int rows, int cols, int nVampires);
	~Game();

	// Mutators
	void play();

private:
	Arena* m_arena;

	// Helper functions
	string takePlayerTurn();
};

#endif // !GAME_H