#ifndef GAMEOBJECT_H
#define GAMEOBEJCT_H

#include "utilities.h"
#include <string>

using namespace std;

class Dungeon;

class GameObject // YOU NEED TO SET WEAPON TAGLINES TO WORK IN WITH PLAYER ATTACKS
{
public:
	GameObject(int x, int y)
		: m_symb('!'), m_xCoord(x), m_yCoord(y) {
		setSym('!');

	};
	int xCoord() {
		return m_xCoord;
	}
	int yCoord() {
		return m_yCoord;
	}

	// ALL GETTERS AND SETTERS NECESSARY

	void   setx(int x) { m_xCoord = x; }
	void   sety(int y) { m_yCoord = y; }

	void   setSym(char c) { m_symb = c; }
	char   getSym() { return m_symb; }

	void   SetDamAm(int n) { m_damAmount = n; }
	int    getDamAm() { return m_damAmount; }

	void   setDexBonus(int n) { m_dexBonus = n; }
	int    getDexBonus() { return m_dexBonus; }

	void   setObjectType(int n) { m_objectType = n; }
	int    getObjectType() { return m_objectType; }

	void   setDungeonPointer(Dungeon& d);
	void   setDungeonPointerNull() { m_d = nullptr; }

	void   setName(string n) { m_name = n; }
	string getName() { return m_name; }

	void setObjectTagLine(string n) { m_objectTagline = n; }
	string getObjectTagLine() { return m_objectTagline; }

	virtual ~GameObject() { m_d = nullptr; }

private:
	char m_symb;
	int m_objectType = 0;
	string m_name = "";
	string m_objectTagline = "";
	int m_xCoord;
	int m_yCoord;
	int m_dexBonus = 0;
	int m_damAmount = 0;
	Dungeon* m_d = nullptr;
};



class Mace : public GameObject
{
public:
	Mace(int x, int y)
		: GameObject(x, y) {
		setSym(')');
		setName("Mace");
		SetDamAm(2);
		setObjectTagLine("swings mace at ");
	};
	~Mace() { setDungeonPointerNull(); }
private:

};



class ShortSword : public GameObject
{
public:
	ShortSword(int x, int y)
		: GameObject(x, y) {
		setSym(')');
		setName("Short sword");
		SetDamAm(2);
		setObjectTagLine("slashes a short sword at ");
	};
	~ShortSword() { setDungeonPointerNull(); }
};



class LongSword : public GameObject
{
public:
	LongSword(int x, int y)
		: GameObject(x, y) {
		setSym(')');
		setName("Long sword");
		SetDamAm(4);
		setDexBonus(2);
		setObjectTagLine("swings long sword at ");
	};
	~LongSword() { setDungeonPointerNull(); }
};



class MagicAxe : public GameObject
{
public:
	MagicAxe(int x, int y)
		: GameObject(x, y) {
		setSym(')');
		setName("Magic axe");
		setDexBonus(5);
		SetDamAm(5);
		setObjectTagLine("chops magic axe at ");
	};
	~MagicAxe() { setDungeonPointerNull(); }
};

class MagicFangs : public GameObject
{
public:
	MagicFangs(int x, int y)
		: GameObject(x, y) {
		setSym(')');
		setName("Magic fangs of sleep");
		setDexBonus(3);
		SetDamAm(2);
		setObjectTagLine("strikes magic fangs at ");
	};
	~MagicFangs() { setDungeonPointerNull(); }
};

class Scroll : public GameObject
{
public:
	Scroll(int x, int y, int i = -1)
		: GameObject(x, y), m_scrollType(i) {
		setSym('?');
		if (i == -1)
			m_scrollType = randInt(0, 3);
		setName(setScrollName(m_scrollType));
		setObjectType(1);
	};
	void setScroll(int n) { m_scrollType = n; }
	int getScrollType() { return m_scrollType; }

	string setScrollName(int n);
	~Scroll() { setDungeonPointerNull(); }
	

private:
	int m_scrollType = -1;
};

class GoldenIdol : public GameObject
{
public:
	GoldenIdol(int x, int y)
		: GameObject(x, y) {
		setSym('&');
		setName("Golden Idol");
		setObjectType(2);					// NOT IMPORTANT TO HAVE, BUT WILL HAVE FOR CONSISTENCY
	};
	~GoldenIdol() { setDungeonPointerNull(); }
private:
};





#endif // 

