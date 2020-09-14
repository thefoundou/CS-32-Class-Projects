// Game.cpp

#include "Game.h"
#include "utilities.h"
#include "Dungeon.h"
#include "GameObject.h"
#include "Actor.h"
#include <iostream>
#include <algorithm>
using namespace std;

// CREATE GAME OBJECT //

Game::Game(int goblinSmellDistance)
	: m_goblinSmellDist(goblinSmellDistance)
{
	m_p = new Player(0, 0);
}

void Game::play()
{
	// KEEP TRACK OF DUNGEON LEVEL //

	for (int level = 0; level < 5; level++) {

		//	 // Declare relavent Vectors //	  //

		vector<Actor*> monster;
		vector<GameObject*> object;

		if (m_inventory.empty()) {							// Creates the players starting weapon (SHORT SWORD)
			GameObject* temp = new ShortSword(0, 0);		// PUTS THE STARTING WEAPON IN THE PLAYERS INVENTORY
			temp->setSym('#');
			m_inventory.push_back(temp);
		}


		if (level == 0) {									// Assign Short Sword as player's current weapon
															// Update player stats
			m_p->setCurrentWeapon(m_inventory.back());
			m_p->setWeapDamAmt(m_p->getCurrentWeapon()->getDamAm());
			m_p->setAtkPoints(m_p->getDexterity() + m_p->getCurrentWeapon()->getDexBonus());
		}
			
		///////////// Generate dungeon level and relevant members ////////////// 

		Dungeon d;

		//	// Generate Player //	//

		// Generates Player Coordinates

		int x = 0;
		int y = 0;
		for (;;) {
			x = randInt(1, M_WIDTH - 1);										// Generate random Coords
			y = randInt(1, M_HEIGHT - 1);

			// Check if this is a valid coordinate (Hint, this section shouldnt need to be checked but better safe than sorry //

			if (d.checkSpace(x, y) != ' ' && d.checkSpace(x, y) != '&' &&		// Checks if random Coords are Valid
				d.checkSpace(x, y) != ')' && d.checkSpace(x, y) != '?' && 
				d.checkSpace(x, y) != '>')
				continue;

			break;
		}

		m_p->setx(x);
		m_p->sety(y);
		m_p->setDungeonPointer(d);
		d.updateGrid(m_p->xCoord(), m_p->yCoord(), '@');
	
		//	// Generate Monster Vector //	//

		// Determine where to place monster

		int numOfMonsters = randInt(2, 5 * (level + 1) + 1);
		for (int i = 0; i < numOfMonsters; i++) {
			x = 0;
			y = 0;
			for (;;) {
				x = randInt(1, M_WIDTH - 1);
				y = randInt(1, M_HEIGHT - 1);

				// Check if this is a valid coordinate //

				bool o = false;
				if (d.checkSpace(x, y) == '#' || d.checkSpace(x, y) == '@')
					o = true;

				int n = monster.size();
				for (int w = 0; w < n; w++) {
					if (x == monster.at(w)->xCoord() && y == monster.at(w)->yCoord()) {
						o = true;
					}
				}
				if (o) continue;
				break;
			}

			// Determining which monsters to place

			int Type = randInt(0,1);
			if (level >= 2)
				Type = randInt(0, 2);
			if (level >= 3)
				Type = randInt(0, 3);

			// Placing Monsters

			Actor* temp = nullptr;

			switch (Type) {											// Each case will create a monster and push
			case 0:													// a pointer to that monster to the Monster
				temp = new SnakeWoman(x, y);						// vector
				temp->setDungeonPointer(d);
				monster.push_back(temp);
				break;
			case 1:
				temp = new Goblins(x, y, m_goblinSmellDist);
				temp->setDungeonPointer(d);
				monster.push_back(temp);
				break;
			case 2:
				temp = new Bogeyman(x, y);
				temp->setDungeonPointer(d);
				monster.push_back(temp);
				break;
			case 3:
				temp = new Dragons(x, y);
				temp->setDungeonPointer(d);
				monster.push_back(temp);
			default:
				break;
			}
		}

		// Generate Game objects vector

		int numOfObjects = randInt(2,3);

		for (int i = 0; i < numOfObjects; i++) {
			x = 0;
			y = 0;
			bool b = false;
			while (b == false) {
				b = true;
				x = randInt(1, M_WIDTH - 1);
				y = randInt(1, M_HEIGHT - 1);

				// Check if this is a valid coordinate //

				if (d.checkSpace(x, y) != ' ' && d.checkSpace(x, y) != 'S' && 
					d.checkSpace(x, y) != 'D' && d.checkSpace(x, y) != 'B' && 
					d.checkSpace(x, y) != 'G' && d.checkSpace(x, y) != '@')
					b = false;
				if (d.checkSpace(x, y) == '&' || d.checkSpace(x, y) == ')' || 
					d.checkSpace(x, y) == '?' || d.checkSpace(x, y) == '>' || 
					d.checkSpace(x, y) == '#')
					b = false;

				int n = object.size();

				for (int w = 0; w < n; w++) {
					if (x == object.at(w)->xCoord() && y == object.at(w)->yCoord()) {
						b = false;
					}
				}
			}

			int Type = randInt(0, 3); 

			GameObject* temp = nullptr;

			switch (Type) {												// Each case will create a monster and push
			case 0:														// a pointer to that monster to the Monster
				temp = new ShortSword(x, y);							// vector
				temp->setDungeonPointer(d);
				object.push_back(temp);
				break;
			case 1:
				temp = new Mace(x, y);
				temp->setDungeonPointer(d);
				object.push_back(temp);
				break;
			case 2:
				temp = new LongSword(x, y);
				temp->setDungeonPointer(d);
				object.push_back(temp);
				break;
			case 3:
				temp = new Scroll(x, y);
				temp->setDungeonPointer(d);
				object.push_back(temp);
				break;
			}

		}

		// CREATION OF GOLDEN IDOL ON LAST FLOOR

		
		if (level == 4) {

			x = 0;
			y = 0;
			bool b = false;
			while (b == false) {
				b = true;
				x = randInt(1, M_WIDTH - 1);
				y = randInt(1, M_HEIGHT - 1);

				// Check if this is a valid coordinate //

				if (d.checkSpace(x, y) != ' ' && d.checkSpace(x, y) != 'S' && 
					d.checkSpace(x, y) != 'D' && d.checkSpace(x, y) != 'B' && 
					d.checkSpace(x, y) != 'G' && d.checkSpace(x, y) != '@')
					b = false;

				int n = object.size();

				for (int w = 0; w < n; w++) {
					if (x == object.at(w)->xCoord() && y == object.at(w)->yCoord()) {
						b = false;
					}
				}

			}

			GameObject* temp = new GoldenIdol(x, y);
			temp->setDungeonPointer(d);
			object.push_back(temp);

		}

		// Generate Stairwell and update Grid

		for (;;) {
			x = randInt(1, M_WIDTH - 1);
			y = randInt(1, M_HEIGHT - 1);

			// Check if this is a valid coordinate //

			if (d.checkSpace(x, y) != ' ' && d.checkSpace(x, y) != 'S' && 
				d.checkSpace(x, y) != 'D' && d.checkSpace(x, y) != 'B' && 
				d.checkSpace(x, y) != 'G' && d.checkSpace(x, y) != '@')
				continue;
			if (d.checkSpace(x, y) == '&' || d.checkSpace(x, y) == ')' || 
				d.checkSpace(x, y) == '?' || d.checkSpace(x, y) == '>' || 
				d.checkSpace(x, y) == '#')
				continue;

			break;
		}

		Stairway st(x, y);
		st.setDungeonPointer(d);


		//	 // UPDATE GRID TO SHOW ALL GAME OBJECTS BEFORE FIRST MOVE //	//

		numOfObjects = object.size();

		for (int i = 0; i < numOfObjects; i++) {
			d.updateGrid(object.at(i)->xCoord(), object.at(i)->yCoord(), object.at(i)->getSym());
		}


		if (level != 4) {
			d.updateGrid(st.xCoord(), st.yCoord(), '>');
		}


		for (int i = 0; i < numOfMonsters; i++) {
			d.updateGrid(monster.at(i)->xCoord(), monster.at(i)->yCoord(), monster.at(i)->getSym());
		}

		// Update the Players position last so it will be on top of all objects //

		d.updateGrid(m_p->xCoord(), m_p->yCoord(), '@');

		// Prints dungeon level and all relevant members and HUD with player statistics //
		 
		ShowGame(d, *m_p, level);

		// Variable to keep track of player input //

		char c;

		//////////////////////////////////   // TAKING TURNS BEGINS //	 ///////////////////////////////////////

		for (;;) {

			// CHANCE OF REGENERATING PLAYER HEALTH //

			if (trueWithProbability(.1) && m_p->getHitPoints() != m_p->getMaxHitPoints())
				m_p->setHitPoints(m_p->getHitPoints() + 1);

			// Chance of Dragon regaining health each round //

			for (int i = 0; i < numOfMonsters; i++) {
				if (monster.at(i)->getName() == "Dragon" && monster.at(i)->getHitPoints() < monster.at(i)->getMaxHP()) {
					if (trueWithProbability(.1))
						monster.at(i)->setHitPoints(monster.at(i)->getHitPoints() + 1);
				}
			}

			// LIST OF INTS and bool TO KEEP TRACK OF WHICH ACTIONS ARE TAKEN //

			bool wonGame = false;
			bool nextFloor = false;
			bool properRead = false;
			bool properEquip = false;
			int invAction = 0;
			int playerAttack = 0;
			int monstAttack = 0;
			int interactWithInv = 0;
			string hurtMonst = "";
			char k = 'a';
			int n = 0;

			//////////// INTERPRETS CHARACTER MOVES AND ACTS ACCORDINGLY //////////// 

			c = getCharacter();

			switch (c) {

			case 'q':
				// BREAKS OUT OF GAME AT ANY TIME //
				break;

				// USING A STAIRWELL
			case '>':
				if (level != 4) {
					if (m_p->xCoord() == st.xCoord() && m_p->yCoord() == st.yCoord())
						nextFloor = true;
				}
				break;

				
			case ARROW_DOWN:
			case ARROW_LEFT:
			case ARROW_RIGHT:
			case ARROW_UP:
				// Player will not move if alseep
				if (m_p->getSleepTime() > 0) {
					m_p->setSleepTime(m_p->getSleepTime() - 1);
					break;
				}

				// Player Move and Attack 

				else {
					d.updateGrid(m_p->xCoord(), m_p->yCoord(), ' ');
					playerAttack = m_p->movePlayer(c, monster, object, hurtMonst);
					d.updateGrid(m_p->xCoord(), m_p->yCoord(), '@');
					break;
				}

			case 'i':
				// PRINTS OUT INVENTORY

				clearScreen();
				std::cout << "Inventory:" << endl;
				printInv();
				getCharacter();
				break;

			case 'r': 
				
				// READING A SCROLL IF IT EXISTS IN INVENTORY

				if (c == 'r') {
					clearScreen();
					std::cout << "Inventory:" << endl;
					printInv();
					k = getCharacter();

					// ENSURES CHARACTER CHOSEN CORRELATES TO AN INV ITEM

					int n = k - 'a';
					int m = m_inventory.size();
					if (n < m && n >= 0)
						properRead = true;

					if (properRead) {
						int objectType = m_inventory.at(n)->getObjectType();
						if (objectType == 1) {
							m_p->readScroll(d, m_inventory.at(n)->getName());
							m_p->setAtkPoints(m_p->getDexterity() + m_p->getCurrentWeapon()->getDexBonus());
							m_p->setDefPoints(m_p->getDexterity() + m_p->getArmor());
							interactWithInv = 1;
						}

						else {
							interactWithInv = 2;
						}
					}

				}
				break;

			case 'w':
				// EQUIPPING A WEAPON FROM INVENTORY

				if (c == 'w') {
					clearScreen();
					std::cout << "Inventory:" << endl;
					printInv();
					k = getCharacter();

					// ENSURES CHARACTER CHOSEN CORRELATES TO AN INV ITEM

					int n = k - 'a';
					int m = m_inventory.size();
					if (n < m && n >= 0)
						properEquip = true;

					if (properEquip) {

						int objectType = m_inventory.at(n)->getObjectType();
						if (objectType == 0) {

							// IF THE CHARACTER CHOSEN CORRESPONDS WITH A WEAPON

							GameObject* temp = m_inventory.at(n);
							m_p->setCurrentWeapon(temp);
							m_p->setWeapDamAmt(m_p->getCurrentWeapon()->getDamAm());
							m_p->setAtkPoints(m_p->getDexterity() + m_p->getCurrentWeapon()->getDexBonus());
							interactWithInv = 3;
						}
						else {

							// IF THE CHARACTER CHOSEN DOES NOT CORRESPOND WITH A WEAPON

							interactWithInv = 4;
						}
					}
				}
				break;

			case 'c':
				// CHEATING - Boost HP to 50 and strength to 9
				m_p->setMaxHitPoints(50);
				m_p->setHitPoints(50);
				m_p->setStrength(9);
				break;

			case 'g':

				// GRABBING ITEMS FROM THE ARENA

				n = object.size() - 1;
				while (n >= 0) {
					bool b = true;
					if (object.at(n)->xCoord() == m_p->xCoord() && object.at(n)->yCoord() == m_p->yCoord()) {

						// SPECIFIC ACTION FOR PICKING UP GOLDEN IDOL AND WINNING

						if (object.at(n)->getName() == "Golden Idol") {
							wonGame = true;
						}

						// IF INVENTORY IS FULL

						if (m_inventory.size() > 25)
							invAction = 2;

						// IF INVENTORY IS NOT FULL

						else {
							b = false;
							vector<GameObject*>::iterator q = object.begin() + n;
							vector<GameObject*>::iterator p = object.end() - 1;
							iter_swap(p, q);
							vector<GameObject*>::iterator y = object.end() - 1;
							GameObject* temp = *y;
							m_inventory.push_back(temp);
							object.pop_back();

							invAction = 1;
						}

					}
					if (!b) break;
					n--;
				}
				
				break;

			default:
				break;
			}
			
			// Move Monsters
			numOfMonsters = monster.size();
			if (!monster.empty()) {
				for (int i = 0; i < numOfMonsters; i++) {
					// Monsters do not move if put to sleep by player
					if (monster.at(i)->getSleepTime() > 0) {
						monster.at(i)->setSleepTime(monster.at(i)->getSleepTime() - 1);
					}
					// Move monsters and have them attack
					else {
						// Deletes monster from current spot //
						d.updateGrid(monster.at(i)->xCoord(), monster.at(i)->yCoord(), ' ');

						// Monster action //

						monstAttack = monster.at(i)->chooseDirection(monster.at(i)->xCoord(),
							monster.at(i)->yCoord(), m_p->xCoord(), m_p->yCoord(),
							monster.at(i)->getSmell(), m_p);

						// Places monster in new spot (may be same spot) // 

						d.updateGrid(monster.at(i)->xCoord(), monster.at(i)->yCoord(), monster.at(i)->getSym());
						monster.at(i)->setAttackPlayer(monstAttack);

					}
				}
			}

			/////////// Update Objects ///////////

			numOfObjects = object.size();
			for (int i = 0; i < numOfObjects; i++) {
				bool l = false;

				// These lines of code ensure objects and stairwell will not be printed over the player or monsters //

				if (m_p->xCoord() == object.at(i)->xCoord() && m_p->yCoord() == object.at(i)->yCoord())
					l = true;

				for (int j = 0; j < numOfMonsters; j++) {
					if (monster.at(j)->xCoord() == object.at(i)->xCoord() && monster.at(j)->yCoord() == object.at(i)->yCoord())
						l = true;
				}

				if (l) continue;

				// Updated object posistion

				d.updateGrid(object.at(i)->xCoord(), object.at(i)->yCoord(), object.at(i)->getSym());
			}

			// Update Staircase
			bool l = false;
			if (m_p->xCoord() == st.xCoord() && m_p->yCoord() == st.yCoord())
				l = true;

			for (int j = 0; j < numOfMonsters; j++) {
				if (monster.at(j)->xCoord() == st.xCoord() && monster.at(j)->yCoord() == st.yCoord())
					l = true;
			}
			if (!l) {
				if (level != 4)
					d.updateGrid(st.xCoord(), st.yCoord(), st.getSym());
			}
			
			// IF THE STAIRCASE WAS USED WE MUST BREAK OUT OF THIS LEVEL LOOP // 

			if (nextFloor)
				break;

			// THE FOLLOWING SECTION IS THE GAMES "GRAPHICS" SECTION,
			// WHERE THE DISPLAY, CHARACTER HUD, AND MESSAGES ARE PRINTED

			ShowGame(d, *m_p, level);

			std::cout << endl;

			if (invAction == 2)
				std::cout << "Your knapsack is full; you can't pick that up." << endl;
			if (invAction == 1)
				std::cout << "You picked up a " << m_inventory.back()->getName() << endl;

			if (wonGame) {
				std::cout << "Congratulations, you won!" << endl;
				break;
			}

			// Printing all Statements Regarding interacting with inventory // 
			GameObject* temp = nullptr;
			n = k - 'a';
			vector<GameObject*>::iterator p = m_inventory.begin() + n;
			if (properEquip || properRead) {
				temp = *p;
			}

			switch (interactWithInv) {
			case 1:
				std::cout << "You read the scroll called " << m_inventory.at(n)->getName() << "." << endl;
				std::cout << m_inventory.at(n)->getObjectTagLine() << endl;
				p = m_inventory.erase(p);
				delete temp;
				break;
			case 2:
				std::cout << "You cannot read the " << m_inventory.at(n)->getName() << "." << endl;
				break;
			case 3:
				std::cout << "You are wielding the " << m_inventory.at(n)->getName() << "." << endl;
				break;
			case 4:
				std::cout << "You can not wield the " << m_inventory.at(n)->getName() << "." << endl;
				break;
			default:
				break;
			}

			// Printing out all statements regarding combat //

			switch (playerAttack) {
			case 1:
				std::cout << "The Player " << m_p->getCurrentWeapon()->getObjectTagLine() << hurtMonst << " and hits." << endl;
				break;
			case 2:
				std::cout << "The Player " << m_p->getCurrentWeapon()->getObjectTagLine() << hurtMonst << " and misses." << endl;
				break;
			case 3:
				std::cout << "The Player " << m_p->getCurrentWeapon()->getObjectTagLine() << hurtMonst << " and hits, putting " << hurtMonst << " to sleep." << endl;
				break;
			case 4:
				std::cout << "The Player " << m_p->getCurrentWeapon()->getObjectTagLine() << hurtMonst << " dealing the final blow." << endl;
				break;
			default:
				break;
			}

			n = 0;
			for (auto i = monster.begin(); i < monster.end(); i++) {
				Actor* temp = *i;
				if (temp->getAttackPlayer() == 1)
					std::cout << temp->getTagline() << " and hits." << endl;
				if (temp->getAttackPlayer() == 2)
					std::cout << temp->getTagline() << " and misses." << endl;
				if (temp->getAttackPlayer() == 4)
					std::cout << temp->getTagline() << " dealing the final blow." << endl;
				if (temp->getAttackPlayer() == 3)
					std::cout << temp->getTagline() << " and hits, putting Player to sleep." << endl;
				n++;
			}

			if (c == 'q')
				break;

			// Making sure the game exits when the player dies

			if (m_p->getHitPoints() <= 0) {
				c = 'q';
				break;
			}

		}

		std::cout << "Press q to quit." << endl << endl;

		for (auto i = monster.begin(); i < monster.end();) {	// Delete all monsters remaining in level
			delete* i;
			i = monster.erase(i);
		}

		for (auto i = object.begin(); i < object.end();) {		// delete all obejects remaining in level
			delete* i;
			i = object.erase(i);
		}

		// BREAKS OUT OF GAME IF Q IS CHARACTER CHOSEN
		if (c == 'q')
			break;
	}

}

void Game::HUD(Player p, int level)
{

	std::cout << "Dungeon Level: " << level << ", " <<  "Hit Points: " << p.getHitPoints() << ", Armor: " << p.getArmor()
		<< ", Strength: " << p.getStrength()  << ", Dexterity: "  << p.getDexterity() << endl;
}

void Game::ShowGame(Dungeon d, Player p, int level)
{
	d.displayGrid();
	HUD(p, level);
}

void Game::printInv()
{
	vector<GameObject*>::iterator q = m_inventory.end();
	vector<GameObject*>::iterator p = m_inventory.begin();
	int count = 0;
	while (p != q) {
		GameObject* temp = *p;
		char c = 97;
		std::cout << " " << char(c + count) << ". ";
		std::cout << temp->getName() << endl;
		count++;
		p++;
	}
}

Game::~Game() {
	delete m_p;
	for (auto i = m_inventory.begin(); i < m_inventory.end();) {
		delete* i;
		i = m_inventory.erase(i);
	}
}