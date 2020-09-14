#include "Dungeon.h"
#include "Actor.h"
#include "Room.h"
#include <vector>
#include <list>
#include <cstdlib>
#include <iostream>

using namespace std;


Dungeon::Dungeon()
{
	generateGrid();
}

void Dungeon::generateGrid() 
{

	for (int i = 0; i < M_WIDTH; i++) {
		for (int k = 0; k < M_HEIGHT; k++) {
			m_grid[k][i] = '#';
		}
	}

	vector<Room*> Rooms;

	// Generate Rooms inside dungeon Randomly

	for (int i = 0; i < randInt(5, 7); i++) {	// Determine number of rooms and loop through the create them

		Rooms.push_back(generateRooms());

		for (int j = Rooms.back()->gety(); j < Rooms.back()->gety2(); j++) {

			for (int i = Rooms.back()->getx(); i < Rooms.back()->getx2(); i++) {

				m_grid[j][i] = ' ';				// Updates each positio within a room to empty

			}
		}
	}
	
	// Generate Corridors
	int z = Rooms.size() - 1;

	for (int i = 2; i >= 0; i--) {

		z = Rooms.size() - 1;

		while (z >= 0) {

			Room* temp = Rooms.at(z);

			// Checking Right

			bool corExists = false;									// I have a function that tells if there is already a corridor
																	// but the level generates better if I dont run it on left or right walls
			bool b = false;
			if (!corExists) {
				int ylow = Rooms.at(z)->gety();						// gets upper and lower bounds for the runthrough
				int yhigh = Rooms.at(z)->gety2();

				while (!b && ylow <= yhigh) {						// Iterates from lower bound to upper bound
					int x = Rooms.at(z)->getx2();
							
					while (x < M_WIDTH - 1) {						// if the check finds an open space, it can build a corridor
						if (m_grid[ylow][x] == ' ') {
							b = true;
							break;
						}
						x++;
					}

					if (b) {										// builds a corridor from the room across to the other room
						x = Rooms.at(z)->getx2();
						while (m_grid[ylow][x] != ' ' && x < M_WIDTH - 1) {
							m_grid[ylow][x] = ' ';
							x++;
						}
					}
					ylow++;
				}

			}

			//Checking Left

			bool b1 = false;										// Same as above but for left facing wall

			corExists = false;

			if (!corExists) {
				int y1low = Rooms.at(z)->gety();
				int y1high = Rooms.at(z)->gety2();
				while (!b1 && y1low <= y1high) {
					int x1 = Rooms.at(z)->getx();

					while (x1 > 0) {
						if (m_grid[y1low][x1] == ' ') {
							b1 = true;
							break;
						}
						x1--;
					}
					if (b1) {
						x1 = Rooms.at(z)->getx();
						while (m_grid[y1low][x1] != ' ' && x1 > 0) {
							m_grid[y1low][x1] = ' ';
							x1--;
						}
					}
					y1low++;
				}

			}

			//Checking Up


			corExists = false;												// Same as above but for up facing wall

			corExists = hasCorridor(temp, 2);

			bool b2 = false;

			if (!corExists) {
				int x2low = Rooms.at(z)->getx();
				int x2high = Rooms.at(z)->getx2();
				while (!b2 && x2low <= x2high) {
					int y2 = Rooms.at(z)->gety() - 1;

					while (y2 > 0) {
						if (m_grid[y2][x2low] == ' ') {
							b2 = true;
							break;
						}
						y2--;
					}
					if (b2) {
						y2 = Rooms.at(z)->gety() - 1;
						while (m_grid[y2][x2low] != ' ' && y2 > 0) {
							m_grid[y2][x2low] = ' ';
							y2--;
						}
					}
					x2low++;
				}
			}

			// Checking Down
			corExists = false;												// Same as above but for down facing wall
			for (int i = 0; i < 4; i++) {
				corExists = hasCorridor(temp, i);
			}
			bool b3 = false;
			int x3low = Rooms.at(z)->getx();
			int x3high = Rooms.at(z)->getx2();
			if (!corExists) {
				while (!b3 && x3low < x3high) {							
					int y3 = Rooms.at(z)->gety2();


					while (y3 < M_HEIGHT - 1) {
						if (m_grid[y3][x3low] == ' ') {
							b3 = true;
							break;
						}
						y3++;
					}
					if (b3) {
						y3 = Rooms.at(z)->gety2();
						while (m_grid[y3][x3low] != ' ' && y3 < M_HEIGHT - 1) {
							m_grid[y3][x3low] = ' ';
							y3++;
						}
					}
					x3low++;
				}
			}
			z--;
		}

	}

	for (auto i = Rooms.begin(); i < Rooms.end();) {
		delete* i;
		i = Rooms.erase(i);
	}
}


Room* Dungeon::generateRooms() {

	Room* temp;

	for (;;) {

		// Create our upper left coordinates // 

		int x = randInt(1, 61);
		int y = randInt(1, 13);

		// decide the width and height of walls //

		temp = new Room(x, y, x + randInt(9, 15), y + randInt(5, 9));
		
		bool b = true;

		for (int j = y; j < temp->gety2(); j++) {

			// Checks if the room goes off of the screen //

			if (j == 0 || j >= 17) {
				b = false;
				break;
			}

			for (int k = x; k < temp->getx2(); k++) {

				if (k == 0 || k >= 69) {
					b = false;
					break;
				}

				// Check if another room overlaps with current room or edges align // 

				if (m_grid[j][k] == ' ' ||
					m_grid[j + 1][k] == ' ' ||
					m_grid[j - 1][k] == ' ' ||
					m_grid[j][k + 1] == ' ' ||
					m_grid[j][k - 1] == ' ')
					b = false;

			}
		}

		// If the room overlaps, delete it and restart the process //

		if (b == false) {
			delete temp;
			continue;
		}
		break;
	}
	return temp;
}

bool Dungeon::hasCorridor(Room* room, int side)
{
	bool hasCorridor = false;
	int nLow = 0;
	int nHigh = 0;
	int check = 0;

	// DEFINING VARIABLES DEPENDING ON WHAT WALL WE ARE CHECKING //

	switch (side) {
	case 0:
		nLow = room->gety();
		nHigh = room->gety2();
		check = room->getx2() + 1;
		break;
	case 1:
		nLow = room->gety();
		nHigh = room->gety2();
		check = room->getx() - 1;
		break;
	case 2:
		nLow = room->getx();
		nHigh = room->getx2();
		check = room->gety() - 1;
		break;
	case 3:
		nLow = room->getx();
		nHigh = room->getx2();
		check = room->gety2() + 1;
		break;
	}

	// Checks each wall if a corridor is leading into it //

	switch (side) {
	case 0:
	case 1:
		if (check >= 69 || check <= 0)
			break;
		while (nLow <= nHigh) {
			if (m_grid[nLow][check] == ' ')
				hasCorridor = true;
			nLow++;
		}
		break;
	case 2:
	case 3:
		if (check >= 17 || check <= 0)
			break;
		while (nLow <= nHigh) {
			if (m_grid[check][nLow] == ' ')
				hasCorridor = true;
			nLow++;
		}
	}

	return hasCorridor;
}

void Dungeon::updateGrid(int x, int y, char c)
{
	m_grid[y][x] = c;
}

void Dungeon::displayGrid() {
	clearScreen();
	for (int i = 0; i < M_HEIGHT; i++) {
		for (int k = 0; k < M_WIDTH; k++) {
		
				cout << m_grid[i][k];
		}
		cout << endl;
	}
}

char Dungeon::checkSpace(int x, int y) const
{
	char c = m_grid[y][x];
	return c;
}

void Stairway::setDungeonPointer(Dungeon& d) {
	m_d = &d;
}
