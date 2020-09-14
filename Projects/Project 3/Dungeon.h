#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include <list>
const int M_WIDTH = 70;
const int M_HEIGHT = 18;

class Player;
class Room;

class Dungeon
{
public:
	Dungeon();

	void generateGrid();
	Room* generateRooms();
	bool hasCorridor(Room* room, int side);
	void displayGrid();
	void updateGrid(int x, int y, char c);
	char checkSpace(int x, int y) const;

	~Dungeon() {  }
private:
	char m_grid[M_HEIGHT][M_WIDTH];
};

class Stairway
{
public:
	Stairway(int x, int y)
		: m_xCoord(x), m_yCoord(y) {};
	char getSym() { return m_symb; }
	void setDungeonPointer(Dungeon& d);
	int xCoord() { return m_xCoord; }
	int yCoord() { return m_yCoord; }
	virtual ~Stairway() { m_d = nullptr; }
private:
	int m_xCoord;
	int m_yCoord;
	char m_symb = '>';
	Dungeon* m_d = nullptr;
};


#endif // !DUNGEON_H
