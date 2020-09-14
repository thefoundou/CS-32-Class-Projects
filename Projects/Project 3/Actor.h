#ifndef ACTOR_H
#define ACTOR_H

#include "utilities.h"
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class Dungeon;
class GameObject;

class Actor
{
public:
	Actor(int x, int y)
		: m_xCoord(x), m_yCoord(y) {};

	int xCoord() {return m_xCoord;}
	int yCoord() {return m_yCoord;}

	void setx(int x) { m_xCoord = x; }
	void sety(int y) { m_yCoord = y; }

	void setDungeonPointer(Dungeon& d);
	void setDungeonPointerNull() { m_d = nullptr; }

	bool doPlayerAction(int x, int y, int& attackMonst, vector<Actor*>& monst, vector<GameObject*>& object, string& hurtMonst);
	bool doMonsterAction(int x, int y, Dungeon* m_d, int& attackPlayer, Actor* player);

	int movePlayer(char c, vector<Actor*> &monst, vector<GameObject*>& object, string &hurtMonst);
	int moveMonster(char c, Actor* player);

	Dungeon* dung() { return m_d; }

	int checkPath(char testGrid[][70], int sr, int sc, int& minDist, int maxDist, int maxCheck, int dir, int& bestFinal);

	int chooseDirection(int sc, int sr, int ec, int er, int smellDist, Actor* player);
	void dropWeapon(vector<Actor*>& monst, vector<GameObject*>& object, int j);

	void setAtkPoints(int n) { m_atkPoints = n; }
	int getAtkPoints() { return m_atkPoints; }

	void setDefPoints(int n) { m_defPoints = n; }
	int getDefPoints() { return m_defPoints; }

	void setWeapDamAmt(int n) { m_weaponDamAmt = n; }
	int getWeapDamAmt() {return m_weaponDamAmt; }

	int movesTo(int sc, int sr, int ec, int er);

	void setHitPoints(int val) { m_hitPoints = val; }
	void setStrength(int val) { m_strength = val; }
	void setDexterity(int val) { m_dexterity = val; }
	void setArmor(int val) { m_armor = val; }

	int getHitPoints() { return m_hitPoints; }
	int getStrength() { return m_strength; }
	int getDexterity() { return m_dexterity; }
	int getArmor() { return m_armor; }

	void setAttackPlayer(int n) { m_attackPlayer = n; }
	int getAttackPlayer() { return m_attackPlayer; }

	char getSym() { return m_symb; }
	void setSym(char d) { m_symb = d; }

	void setSmell(int n) { m_smelldist = n; }
	int getSmell() { return m_smelldist; }

	void setTagline(string n) { m_tagline = n; }
	string getTagline() { return m_tagline; }

	void setName(string n) { m_name = n; }
	string getName() { return m_name; }

	void setSleepTime(int n) { m_sleepTime = n; }
	int getSleepTime() { return m_sleepTime; }

	int attack(Actor* damaged, Actor* attacker);

	int getMaxHP() { return m_maxHitPoints; }
	void setMaxHP(int n) { m_maxHitPoints = n; }

	void operator delete(void* aPtr) { ::operator delete(aPtr); }
	virtual ~Actor() = default;

private:
	string m_name = "";
	string m_tagline = "";
	int m_weaponDamAmt = 0;
	int m_atkPoints = 0;
	int m_defPoints = 0;
	int m_smelldist = 0;
	char m_symb = ' ';
	int m_xCoord;
	int m_yCoord;
	int m_hitPoints = 0;
	int m_strength = 0;
	int m_dexterity = 0;
	int m_armor = 0;
	int m_attackPlayer = 0;
	int m_sleepTime = 0;

	int m_maxHitPoints = 0; // Only needed for Dragon

	Dungeon* m_d = nullptr;
};



class Player : public Actor 
{
public:
	Player(int x, int y) 
		: Actor(x,y) 
	{
		setHitPoints(20);
		setStrength(2);
		setArmor(2);
		setDexterity(2);
		m_maxHitPoints = 20;

		// COMBAT VALUES
		setDefPoints(getDexterity() + getArmor());

	};

	void setMaxHitPoints(int n) { m_maxHitPoints = n; }
	int getMaxHitPoints() { return m_maxHitPoints; }

	void setCurrentWeapon(GameObject* weap);
	GameObject* getCurrentWeapon() { return m_weapon; }

	void readScroll(Dungeon& d, string n);

	~Player();
	
private:
	GameObject* m_weapon = nullptr;
	int m_maxHitPoints;

};

// SINCE MONSTERS CANNOT CHANGE WEAPONS, I DECIDED TO CODE THEIR WEAPONS BONUSES
// STRAIGHT INTO THEIR STATS TO HELP AVOID ANY UNNECCESARY SETTING OF POINTERS
// AND ACCESSING STATS.

class Bogeyman : public Actor
{
public:
	Bogeyman(int x, int y)
		: Actor(x, y) 
	{
		int hitPoint = randInt(5, 10);
		int strength = randInt(2, 3);
		int dexterity = randInt(2, 3);
		
		setSmell(5);
		setSym('B');
		setHitPoints(hitPoint);
		setStrength(strength);
		setArmor(2);
		setDexterity(dexterity);
		setName("Bogeyman");
		setTagline("the Bogeyman slashes short sword at Player");

		// COMBAT VALUES
		setWeapDamAmt(2);
		setAtkPoints(getDexterity() /*short sword gives no bonus*/);
		setDefPoints(getDexterity() + getArmor());
	};
	~Bogeyman() { setDungeonPointerNull(); };
private:
};


class SnakeWoman : public Actor
{
public:
	SnakeWoman(int x, int y)
		: Actor(x, y)
	{
		int hitPoint = randInt(3, 6);

		setSmell(3);
		setSym('S');
		setHitPoints(hitPoint);
		setStrength(2);
		setArmor(3);
		setDexterity(3);
		setName("SnakeWoman");
		setTagline("the Snakewoman strikes magic fangs at Player");

		// COMBAT VALUES
		setWeapDamAmt(2);
		setAtkPoints(getDexterity() + 3 /*from weapon bonus*/);
		setDefPoints(getDexterity() + getArmor());
	};
	~SnakeWoman() { setDungeonPointerNull(); };
private:

};


class Dragons : public Actor
{
public:
	Dragons(int x, int y)
		: Actor(x, y) 
	{
		int hitPoint = randInt(20, 25);

		setSmell(1);
		setSym('D');
		setHitPoints(hitPoint);
		setMaxHP(hitPoint);
		setStrength(4);
		setArmor(4);
		setDexterity(4);
		setName("Dragon");
		setTagline("the Dragon swings long sword at Player");

		// COMBAT VALUES
		setWeapDamAmt(4);
		setAtkPoints(getDexterity() + 2 /*weapons bonus*/);
		setDefPoints(getDexterity() + getArmor());

	};
	~Dragons() { setDungeonPointerNull(); };
private:

};


class Goblins : public Actor
{
public:
	Goblins(int x, int y, int smellDist)
		: Actor(x, y) 
	{
		int hitPoint = randInt(15, 20);

		setSmell(smellDist);
		setSym('G');
		setHitPoints(hitPoint);
		setStrength(3);
		setArmor(1);
		setDexterity(1);
		setName("Goblin");
		setTagline("the Goblin slashes short sword at Player");

		// COMBAT VALUES
		setWeapDamAmt(2);
		setAtkPoints(getDexterity() /*short sword gives no bonus*/);
		setDefPoints(getDexterity() + getArmor());
	};
	~Goblins() { setDungeonPointerNull(); };
private:

};




#endif // !ACTOR_H

