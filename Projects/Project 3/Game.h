// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <vector>
#include <iostream>
#include "Actor.h"

// You may add data members and other member functions to this class.

class Dungeon;

class Game
{
public:
	Game(int goblinSmellDistance);
	void HUD(Player p, int level);
	void ShowGame(Dungeon d, Player p, int level);
	void play();
	void printInv();
	void operator delete(void* aPtr) { ::operator delete(aPtr); }
	~Game();
private:
	vector<GameObject*> m_inventory;
	int m_goblinSmellDist;
	Player* m_p = nullptr;
};

#endif // GAME_INCLUDED
