#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

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
	vector <vector < char > > m_table;		// Store ships and shoots
	char m_previous_value;
	int m_ships_left;			// Summary length of ships
	vector <int> m_ships;					// Vector of available ships

public:
	Board();								// Constructor and Destructor without arguments
	~Board();
	void clear_table();						// Clear all board from ships and shoots.
	void draw_table();						// Update view of board on the screen
	void cursor(int row, char cols);		// Set current position of cursor
	void put_ships();						// Use only once at the beggining of the game
};