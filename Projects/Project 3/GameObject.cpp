#include "GameObject.h"
#include "utilities.h"
#include <iostream>

using namespace std;

void GameObject::setDungeonPointer(Dungeon& d) {
	m_d = &d;
}

string Scroll::setScrollName(int n)
{
	switch (n) {
	case 0:
		setObjectTagLine("Your armor glows blue.");
		return "Scroll of improve armor";
		break;
	case 1:
		setObjectTagLine("Your muscles bulge.");
		return "Scroll of strength";
		break;
	case 2:
		setObjectTagLine("You feel your heart beating stronger.");
		return "Scroll of enhance health";
		break;
	case 3:
		setObjectTagLine("You feel like less of a klutz.");
		return "Scroll of enhance dexterity";
		break;
	case 4:
		setObjectTagLine("You feel your body wrenched in space and time.");
		return "Scroll of teleportation";
		break;
	default:
		return "You should not get here";
	}
}