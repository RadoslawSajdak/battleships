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
#define KEY_SAVE 115

using namespace std;

class Board {
private:
	vector <vector < char > > m_table;		// Store ships and shoots
	vector <vector < char > > m_shoots;		// Store ships and shoots
	char m_previous_value;
	bool m_ships_put;						// I'll use it to switch between screens
	int m_ships_left;						// Summary length of ships
	vector <int> m_ships;					// Vector of available ships
	vector <int> move_cursor(void);			// Finding first empty position of cursor and move it there
	void clear_table(vector <vector < char > >*);						// Clear all board from ships and shoots.
	void draw_table(vector <vector < char > >);						// Update view of board on the screen

public:
	Board();								// Constructor and Destructor without arguments
	~Board();

	void clear_table();						// Self clear ships board
	void cursor(int * p_row, char * p_cols);// Set current position of cursor
	void put_ships();						// Used only once at the beggining of the game
	void shoot(int *, char *, Board enemy);
	void load_boards(string);				// Decode and load data to vectors
	
	/* Getters */
	string get_table();
	string get_shoots();
	int get_ships_left();
	char get_prev_val();
};