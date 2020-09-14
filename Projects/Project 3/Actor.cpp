#include "Actor.h"
#include "Dungeon.h"
#include "utilities.h"
#include "GameObject.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

void Actor::setDungeonPointer(Dungeon& d) {
	m_d = &d;
}

int Actor::movePlayer(char c, vector<Actor*>& monst, vector<GameObject*>& object, string& hurtMonst) {
	int attackMonst = 0;
	
	// Will move according to player character input //

	switch (c) {
	case ARROW_LEFT:
		if (doPlayerAction(xCoord() - 1, yCoord(), attackMonst, monst, object, hurtMonst))
			break;
		setx(xCoord() - 1);
		break;
	case ARROW_DOWN:
		if (doPlayerAction(xCoord(), yCoord() + 1, attackMonst, monst, object, hurtMonst))
			break;
		sety(yCoord() + 1);
		break;
	case ARROW_UP:
		if (doPlayerAction(xCoord(), yCoord() - 1, attackMonst, monst, object, hurtMonst))
			break;
		sety(yCoord() - 1);
		break;
	case ARROW_RIGHT:
		if (doPlayerAction(xCoord() + 1, yCoord(), attackMonst, monst, object, hurtMonst))
			break;
		setx(xCoord() + 1);
		break;
	}

	// returns status of player attack (hit, missed, etc.) //

	return attackMonst;
}

void Actor::dropWeapon(vector<Actor*>& monst, vector<GameObject*> &object, int j) {

	int scrollType = -1;
	GameObject* temp = nullptr;

	// Will determine whether or not the monster drops a weapon, and what type //

	switch (monst.at(j)->getSym()) {
	case 'B':
		if (trueWithProbability(.1)) {
			temp = new MagicAxe(monst.at(j)->xCoord(), monst.at(j)->yCoord());
			object.push_back(temp);
			break;
		}
		break;
	case 'S':
		if (trueWithProbability(.33)) {
			temp = new MagicFangs(monst.at(j)->xCoord(), monst.at(j)->yCoord());
			object.push_back(temp);
			break;
		}
		break;
	case 'D':
		scrollType = randInt(0, 4);
		temp = new Scroll(monst.at(j)->xCoord(), monst.at(j)->yCoord(), scrollType);
		object.push_back(temp);
		break;
	case 'G':
		if (trueWithProbability(.33)) {
			int weap = randInt(0, 1);
			if (weap == 1) {
				temp = new MagicAxe(monst.at(j)->xCoord(), monst.at(j)->yCoord());
				object.push_back(temp);
			}
			else {
				temp = new MagicFangs(monst.at(j)->xCoord(), monst.at(j)->yCoord());
				object.push_back(temp);
			}
			break;
		}
		break;
	default:
		break;
	}
}

int Actor::moveMonster(char c, Actor* player) {

	int attackPlayer = 0;

	// Will move monster according to the character the game has decided for it //

	switch (c) {
	case ARROW_LEFT:
		if (doMonsterAction(xCoord() - 1, yCoord(), m_d, attackPlayer, player))
			break;
		setx(xCoord() - 1);
		break;

	case ARROW_DOWN:
		if (doMonsterAction(xCoord(), yCoord() + 1, m_d, attackPlayer, player))
			break;
		sety(yCoord() + 1);
		break;

	case ARROW_UP:
		if (doMonsterAction(xCoord(), yCoord() - 1, m_d, attackPlayer, player))
			break;
		sety(yCoord() - 1);
		break;

	case ARROW_RIGHT:
		if (doMonsterAction(xCoord() + 1, yCoord(), m_d, attackPlayer, player))
			break;
		setx(xCoord() + 1);
		break;
	}
	return attackPlayer;
}

int Actor::movesTo(int sc, int sr, int ec, int er)
{

	// Counts moves from current monster to player //

	int xMove = abs(sc - ec);
	int yMove = abs(sr - er);

	return xMove + yMove;
}

int Actor::chooseDirection(int sc, int sr, int ec, int er, int smellDist, Actor* player)
{
	int val = 0;
	int findDirection = -1;

	// Use this to determine whether we use our path determining code for Goblin or for other monsters //

	if (getSym() == 'G' && movesTo(xCoord(), yCoord(), player->xCoord(),player->yCoord()) <= smellDist) {

		// Creates a "cleaned" grid that only places a '#' for all spots a mosnter cannot move to
		// and a '@' for the player

		char testGrid[18][70];

		for (int x = 0; x < 70; x++) {
			for (int y = 0; y < 18; y++) {
				if (dung()->checkSpace(x, y) == '#' ||
					dung()->checkSpace(x, y) == 'G' ||
					dung()->checkSpace(x, y) == 'D' ||
					dung()->checkSpace(x, y) == 'B' ||
					dung()->checkSpace(x, y) == 'S')
					testGrid[y][x] = '#';
				else if (dung()->checkSpace(x, y) == '@')
					testGrid[y][x] = '@';
				else
					testGrid[y][x] = ' ';
			}
		}

		// Ensures the players start spot is empty or else the checkpath function fails at the start //

		testGrid[yCoord()][xCoord()] = ' ';

		// declare variables needed for recursive search

		int min = -1;
		int bestFinal = -1;

		// Checkpath Function will return the direction the Goblin should go to follow the shortest path //

		checkPath(testGrid, yCoord(), xCoord(), min, smellDist, smellDist, -1, bestFinal);

		switch (bestFinal) {
		case 0:
			val = moveMonster(ARROW_RIGHT, player);
			break;
		case 1:
			val = moveMonster(ARROW_LEFT, player);
			break;
		case 2:
			val = moveMonster(ARROW_DOWN, player);
			break;
		case 3:
			val = moveMonster(ARROW_UP, player);
			break;
		default:
			break;
		}

		return val;
	}
	else {

		// MOVEMENT FOR "DUMB" MONSTERS // 

		int totalMove = movesTo(sc, sr, ec, er);

		if (totalMove <= smellDist) {
			if (movesTo(sc + 1, sr, ec, er) <= totalMove)
				findDirection = 0;
			if (movesTo(sc - 1, sr, ec, er) < totalMove)
				findDirection = 1;
			if (movesTo(sc, sr + 1, ec, er) < totalMove)
				findDirection = 2;
			if (movesTo(sc, sr - 1, ec, er) < totalMove)
				findDirection = 3;

		}

		// MOVE THE MONSTERS in chosen Directions //

		switch (findDirection) {
		case 0:
			val = moveMonster(ARROW_RIGHT, player);
			break;
		case 1:
			val = moveMonster(ARROW_LEFT, player);
			break;
		case 2:
			val = moveMonster(ARROW_DOWN, player);
			break;
		case 3:
			val = moveMonster(ARROW_UP, player);
			break;
		default:
			break;
		}

		return val;
	}
}

int Actor::attack(Actor* damaged, Actor* attacker)
{
	// Keeps track of the type of attack done (Hit, miss, poison, etc)

	int attackType = 0;

	// Sees if attack was successful //

	if (randInt(1, getAtkPoints()) >= randInt(1, damaged->getDefPoints())) {
		attackType = 1;

		// Will attempt to poison if attacker is Snakewoman or Player with Magic Fangs //

		if (attacker->getName() == "SnakeWoman" || attacker->getAtkPoints() == attacker->getDexterity() + 3) {
			if (trueWithProbability(.2)) {
				attackType = 3;
				int newSleepTime = randInt(2,6);
				if (damaged->getSleepTime() < newSleepTime)
					damaged->setSleepTime(newSleepTime);
			}
		}

		// Determines damage done to the attacked actor

		int damagePoints = randInt(0, (attacker->getStrength() + attacker->getWeapDamAmt()) - 1);
		damaged->setHitPoints(damaged->getHitPoints() - damagePoints); 

		return attackType;
	}
	else
		return 2;
}

bool Actor::doPlayerAction(int x, int y, int &attackMonst, vector<Actor*>& monst, vector<GameObject*>& object, string& hurtMonst) {
	if (m_d->checkSpace(x,y) == '#')
		return true;
	// CASE OF MONSTER ATTACKING PLAYER
	if (m_d->checkSpace(xCoord() - 1, yCoord()) == '@')
		return true;
	// CASE OF PLAYER ATTACKING MONSTER
	if (m_d->checkSpace(x,y) == 'B' ||
		m_d->checkSpace(x,y) == 'D' ||
		m_d->checkSpace(x,y) == 'S' ||
		m_d->checkSpace(x,y) == 'G')
	{

		int j = monst.size() - 1;
		while (j >= 0) {
			int x1 = monst.at(j)->xCoord();
			int y1 = monst.at(j)->yCoord();

			// IF THE COORDINATES LINE UP WITH A MONSTERS COORIDNATES //

			if (x1 == x && y1 == y) {
				hurtMonst = monst.at(j)->getName();
				
				// Attack monster //

				attackMonst = attack(monst.at(j), this);
				if (attackMonst == 2) return attackMonst;

				// Determining if item drops on monster death //

				if (monst.at(j)->getHitPoints() <= 0) {
					attackMonst = 4;
					int n = object.size();
					bool b = true;

					// Checks if an object is already on the position //

					for (int w = 0; w < n; w++) {
						if (monst.at(j)->xCoord() == object.at(w)->xCoord() && monst.at(j)->yCoord() == object.at(w)->yCoord()) {
							b = false;
						}
					}
					if (b) {
						dropWeapon(monst, object, j);
					}

					// Delete monster from the level and from the monster vector //

					vector<Actor*>::iterator q = monst.begin() + j;
					vector<Actor*>::iterator p = monst.end() - 1;
					iter_swap(p, q);
					vector<Actor*>::iterator y = monst.end() - 1;
					Actor* temp1 = *y;
					temp1->dung()->updateGrid(temp1->xCoord(), temp1->yCoord(), ' ');
					monst.pop_back();
					temp1->setDungeonPointerNull();
					delete temp1;
				}
			}
			j--;
		}
		return true;
	}
	return false;
}

bool Actor::doMonsterAction(int x, int y, Dungeon* m_d, int &attackPlayer, Actor* player) {

	// Due to code structure outside of this function, it served better to return true when the monster should not move //

	if (m_d->checkSpace(x, y) == '#')
		return true;

	// CASE OF MONSTER ATTACKING PLAYER

	if (x == player->xCoord() && y == player->yCoord()) {

		attackPlayer = (attack(player, this));

		if (player->getHitPoints() <= 0) {
			attackPlayer = 4;
		}
		return true;
	}

	if (m_d->checkSpace(x,y) == 'B' ||
		m_d->checkSpace(x,y) == 'D' ||
		m_d->checkSpace(x,y) == 'S' ||
		m_d->checkSpace(x,y) == 'G') {
		return true;
	}
	return false;
}

void Player::readScroll(Dungeon &d, string type)
{
	int n = -1;
	int x = 0;
	int y = 0;

	// Setting n according to the type of scroll //


	if (type == "Scroll of improve armor")
		n = 0;

	if (type == "Scroll of strength")
		n = 1;

	if (type == "Scroll of enhance health")
		n = 2;

	if (type == "Scroll of enhance dexterity")
		n = 3;

	if (type == "Scroll of teleportation")
		n = 4;

	// Upgrade stats //

	switch (n) {
	case 0:
		setArmor(getArmor() + randInt(1, 3));
		if (getArmor() > 99)
			setArmor(99);
		break;
	case 1:
		setStrength(getStrength() + randInt(1, 3));
		if (getStrength() > 99)
			setStrength(99);
		break;
	case 2:
		setMaxHitPoints(m_maxHitPoints + randInt(3, 8));
		if (getMaxHitPoints() > 99)
			setMaxHitPoints(99);
		break;
	case 3:
		setDexterity(getDexterity() + 1);
		if (getDexterity() > 99)
			setDexterity(99);
		break;
	case 4:
		for (;;) {

			// generate random coordinates - check if spot is valid //

			x = randInt(1, M_WIDTH - 1);
			y = randInt(1, M_HEIGHT - 1);

			if (d.checkSpace(x, y) != ' ' && d.checkSpace(x, y) != '&' &&
				d.checkSpace(x, y) != ')' && d.checkSpace(x, y) != '?' &&
				d.checkSpace(x, y) != '>')
				continue;

			break;
		}
		d.updateGrid(xCoord(), yCoord(), ' ');
		setx(x);
		sety(y);
		d.updateGrid(xCoord(), yCoord(), '@');
		break;
	default:
		break;
	}
}

void Player::setCurrentWeapon(GameObject* weap) {
	m_weapon = weap;
}

Player::~Player() {
	setDungeonPointerNull();
	m_weapon = nullptr;
}

// RECURSIVE SEARCH FUNCTION

int Actor::checkPath(char testGrid[][70], int sr, int sc, int& minDist, int maxDist, int maxCheck, int dir, int& bestFinal) {

	// All of the base negative cases that would cause the current search to "fail" //

	if (testGrid[sr][sc] == '#' || maxDist < 0 || maxDist <= minDist) return -1;

	// IF the player is found, and the path is shorter than the previous path to player //
	// change the best direction to the direction of the first step that should be      //
	// by the monster.																	//

	if (testGrid[sr][sc] == '@') {
		if (minDist < maxDist) {
			minDist = maxDist;
			bestFinal = dir;
			return minDist;
		}
	}

	// Mark the current spot as visited //

	testGrid[sr][sc] = '#';

	// recursively check each direction //

	if (maxCheck == maxDist)
		dir = 0;
	checkPath(testGrid, sr, sc + 1, minDist, maxDist - 1, maxCheck, dir, bestFinal);

	if (maxCheck == maxDist)
		dir = 1;
	checkPath(testGrid, sr, sc - 1, minDist, maxDist - 1, maxCheck, dir, bestFinal);

	if (maxCheck == maxDist)
		dir = 2;
	checkPath(testGrid, sr + 1, sc, minDist, maxDist - 1, maxCheck, dir, bestFinal);

	if (maxCheck == maxDist)
		dir = 3;
	checkPath(testGrid, sr - 1, sc, minDist, maxDist - 1, maxCheck, dir, bestFinal);

	// Unmark the spot as visited so a later search can traverse this current spot // 

	testGrid[sr][sc] = ' ';

	// Final check to return if the function was successful or not //

	if (bestFinal != -1) {
		return minDist;
	}
	return -1;
}