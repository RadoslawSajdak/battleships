#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_SPACE 32
#define KEY_ESCAPE 27

using namespace std;

class Board {
private:
	vector <vector < char > > m_table;
	char m_previous_value;
	int m_ships_left;
	vector <int> m_ships;

public:
	Board();
	~Board();
	void draw_table();
	void cursor(int row, char cols);
	void put_ships();
};