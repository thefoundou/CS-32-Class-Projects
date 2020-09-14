#ifndef ROOM_H
#define ROOM_H

class Room
{
public:
	Room(int x, int y, int x2, int y2)
		: m_x(x), m_x2(x2), m_y(y), m_y2(y2)
	{
		m_xCenter = ((x + x2) / 2);
		m_yCenter = ((y + y2) / 2);
	};
	int getx() { return m_x; }
	int gety() { return m_y; }
	int getx2() { return m_x2; }
	int gety2() { return m_y2; }
	int getxCen() { return m_xCenter; }
	int getyCen() { return m_yCenter; }

private:

	// Each data member helps keep track of useful
	// parts of a rectangle useful to dungeon creation

	int m_x;
	int m_x2;
	int m_y;
	int m_y2;
	int m_xCenter = 0;
	int m_yCenter = 0;
};



#endif // !ROOM_H

