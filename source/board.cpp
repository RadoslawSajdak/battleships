#include "board.h"
Board::Board()
{
	
	m_previous_value = ' ';	
	m_ships_left = 14;

#if DEBUG_LEVEL < 2
	m_ships_put = false;
#else 
	m_ships_put = true;
#endif

	/* Fill up array with ships as it's len*/
	m_ships.push_back(4);
	m_ships.push_back(3);
	m_ships.push_back(2);
	m_ships.push_back(2);
	for (int i = 0; i < 3; i++) m_ships.push_back(1);

	/* Make an empty board */
	vector < char > cols;
	for (int i = 0; i < 9; i++)
	{
		cols.push_back(' ');
	}
	for (int i = 0; i < 9; i++)
	{
		m_table.push_back(cols);
	}	

	clear_table(&m_table);			// This function is needed to protect us from out of range
	m_shoots = m_table;
}

Board::~Board()
{
	;
}
/* Simple fill up all board with zero values */
void Board::clear_table(vector <vector < char > > * table)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			table->at(i).at(j) = ' ';
		}
	}
	table->at(8).at(8) = '?'; // initialize cursor
	draw_table(*table);
}
void Board::clear_table()
{
	clear_table(&m_table);
}

void Board::draw_table(vector <vector < char > > table)
{
	/* Making A-I columns*/
	system("CLS");
	cout << "   ";
	for (int i = 0; i < table.size(); i++) cout << char('A' + i) << "   ";
	cout << endl;
	/* Fill up board with actual data*/
	for (int i = 0; i < table.size(); i++)
	{
		cout << i << ": "; // Print row numbers
		for (int j = 0; j < table.at(i).size(); j++)
		{
			cout << table.at(i).at(j) << " | ";
		}
		cout << endl;
		for (int j = 0; j < table.at(i).size() * 2 + 1;  j++) cout << "--";
		cout << endl;
	}
	/* Simple instruction of use */
	cout << "Move - arrows \n";
	cout << "Confirm - enter \n";
	cout << "Rotate ship - space \n";
	if (m_ships_put) cout << "Save Game - s \n";
	cout << "Exit - esc\n";
}

void Board::cursor( int * p_row,  char * p_cols)
{
	vector<char>::iterator old;
	int row = *p_row;
	char cols = *p_cols;
	/* Finding old position of cursor and remove it*/
	for (int i = 0; i < m_shoots.size(); i++)
	{
		old = find(m_shoots.at(i).begin(), m_shoots.at(i).end(), '?');
		if (old == m_shoots.at(i).end()) continue;
		else
		{
			break;
		}
	}

	*old = m_previous_value;
	/* Carousel for cursor */

	if (row > 8) row = 0;
	if (row < 0) row = 8;
	if (cols > 'i') cols = 'a';
	if (cols < 'a') cols = 'i';

	int temp_cols = 0;
	if (int(cols) > 96 && int(cols) < 106) temp_cols = cols - 97;
	else if (int(cols) > 64 && int(cols) < 74) temp_cols = cols - 65;
	else exit(EXIT_FAILURE);

	*p_row = row;
	*p_cols = cols;

	m_previous_value = m_shoots.at(row).at(temp_cols);
 	m_shoots.at(row).at(temp_cols) = '?'; 
	
	draw_table(m_shoots);

} 

void Board::put_ships()
{

	int X = 0, Y = 0;			// Position of ship cursor on the board
	int pos_a = 0, pos_b = 0;	// Positions of shooting cursor on the board
	bool vertical = true;		// Orientation of current ship
	bool error = false;			// Provide information about crossing ships
	vector <vector <char>> cp_board; // Temporary board
	cp_board = m_table;
	int ship_iterator = 0;		// How many ships we put

	/* Main putting loop */
	draw_table(m_table);
	while (1) {
		
		char key = _getch();
		int key_val = key;
		switch (key_val) {
			/* Moving ships on the board*/
			/* In every simple case we've out of range protection so user can't put any ship
				Outside of the board*/
		case KEY_UP:
			if(X > 0) X--;
			for (int i = 0; i < m_ships.at(ship_iterator); i++)
			{
				if (vertical) {
					m_table.at(X).at((Y + i) % 9) = 'o';
					m_table.at((X + 1) % 9).at((Y + i) % 9) = cp_board.at((X + 1) % 9).at((Y + i) % 9);
				}
				else
				{
					m_table.at((X + i) % 9).at(Y) = 'o';
					m_table.at((X + i + 1) % 9).at(Y) = cp_board.at((X + i + 1) % 9).at(Y);
				}
			}
			break;
		case KEY_DOWN:
			if((X < 8 && vertical) || X <= (8 - m_ships.at(ship_iterator))) X++;
			for (int i = 0; i < m_ships.at(ship_iterator); i++)
			{
				if (vertical) {
					m_table.at(X).at((Y + i) % 9) = 'o';
					m_table.at((X - 1) % 9).at((Y + i) % 9) = cp_board.at((X - 1) % 9).at((Y + i) % 9);
				}
				else
				{
					m_table.at((X + i) % 9).at(Y) = 'o';
				}
					m_table.at((X - 1) % 9).at(Y) = cp_board.at((X - 1) % 9).at(Y);
			}
			break;
		case KEY_LEFT:
				if( Y > 0) Y--;
				if (vertical) {
					for (int i = 0; i < m_ships.at(ship_iterator); i++)
						m_table.at(X).at((Y + i) % 9) = 'o';
					m_table.at(X).at((Y + m_ships.at(ship_iterator)) % 9) = cp_board.at(X).at((Y + m_ships.at(ship_iterator)) % 9);
				}
				else
				{
					for (int i = 0; i < m_ships.at(ship_iterator); i++) {
						m_table.at((X + i) % 9).at(Y) = 'o';
						m_table.at((X+i)%9).at(Y + 1) = cp_board.at((X + i) % 9).at(Y + 1);
					}
				}
			break;
		case KEY_RIGHT:
			if (Y < (9 - m_ships.at(ship_iterator)) && vertical)
			{
				Y++;
				for (int i = 0; i < m_ships.at(ship_iterator); i++)
					if (vertical) {
						m_table.at(X).at((Y + i) % 9) = 'o';
					}
				m_table.at(X).at((Y - 1) % 9) = cp_board.at(X).at((Y - 1) % 9);
			}
			if (!vertical && Y < 8)
			{
				Y++;
				for (int i = 0; i < m_ships.at(ship_iterator); i++)
				{
					m_table.at((X+i)%9).at(Y) = 'o';
					m_table.at((X+i) % 9).at(Y - 1) = cp_board.at((X + i) % 9).at(Y - 1);
				}
			}

			break;
		/* We can switch orientation of the ship */
		case KEY_SPACE:
			m_table = cp_board;
			vertical = !vertical;
			break;
		/* Putting ship and provide error control */
		case KEY_ENTER:
			error = false;
			/* Move shooting cursor to new position if we put the ship on it */
			for (int i = 0; i < cp_board.size(); i++)
			{
				for (int j = 0; j < cp_board.at(i).size(); j++)
				{
					if (cp_board.at(i).at(j) == '?') {
						pos_a = i;
						pos_b = j;
					}
				}
			}
			if(m_table.at(pos_a).at(pos_b) != '?') 
				for(int i = 0; i < m_table.size(); i++)
					if (m_table.at(0).at(i) == ' ')
					{
						m_table.at(0).at(i) = '?';
						break;
					}
			/* Scan board and look if we crossed ships. If we, it will clear all board and restart putting*/
			if(vertical)
			{
				for (int j = 0; j < m_ships.at(ship_iterator); j++)
				{
					if (cp_board.at(X).at(Y+j) == 'o')
					{
						cout << "\n>>> You can\'t cross ships! Try again! <<< \n";
						Sleep(2000);
						clear_table(&m_table);
						cp_board = m_table;
						error = true;
						break;
					}
				}
			}
			if (!vertical)
			{
				for (int j = 0; j < m_ships.at(ship_iterator); j++)
				{
					if (cp_board.at(X + j).at(Y) == 'o')
					{
						cout << "\n>>> You can\'t cross ships! Try again! <<< \n";
						Sleep(2000);
						clear_table(&m_table);
						cp_board = m_table;
						error = true;
						break;
					}
				}
			}
			
			
			if (error)
			{
				ship_iterator = 0;
				error = false;
				break;
			}
			else 
			{
				ship_iterator++;
				cp_board = m_table;
			}
			/* This is way to close our program */
			break;
		case KEY_ESCAPE:
			exit(EXIT_SUCCESS);
			break;
		if (X > 8) X = 0;
		if (X < 0) X = 8;
		if (Y > 'i') Y = 'a';
		if (Y < 'a') Y = 'i';
		}
		draw_table(m_table);
		if (ship_iterator == m_ships.size())
		{
			m_ships_put = true;
			break;		// Putting is done while we put all ships
		}
	}

}


vector<int> Board::move_cursor(void)
{
	//vector<int> temp_return = { 0,0 };
	for (int i = 0; i < m_shoots.size(); i++)
	{
		for (int j = 0; j < m_shoots.size(); j++)
			if (m_shoots.at(i).at(j) == ' ')
			{
				m_shoots.at(i).at(j) = '?';
				return{ i,j };
			}
	}
	/* After fill up all board */
	cout << " >>> Your game is done! <<<" << endl << endl;
	exit(1);
}
void Board::shoot(int *p_X, char *p_Y, Board enemy)
{
	int X = *p_X;
	int Y = *p_Y;
	vector<int> temp_return = { 0,0 };
	if (m_previous_value != 'c' && m_previous_value != 'x')
	{
		temp_return = move_cursor();
		if (enemy.m_table.at(X).at(Y - 'a') == 'o') 
		{
			m_shoots.at(X).at(Y - 'a') = 'x';
			m_ships_left -= 1;
		}
		else m_shoots.at(X).at(Y - 'a') = 'c';
	}
	*p_X = temp_return.at(0);
	*p_Y = temp_return.at(1) + 'a';
	draw_table(m_shoots);
}

int Board::get_ships_val()
{
	return m_ships_left;
}

string Board::get_table()
{
	string temp_table;
	for (int i = 0; i < m_table.size(); i++)
	{
		for (int j = 0; j < m_table.size(); j++)
		{
			temp_table += m_table.at(i).at(j);
		}
	}
	return temp_table;
}
string Board::get_shoots()
{
	string temp_table;
	for (int i = 0; i < m_shoots.size(); i++)
	{
		for (int j = 0; j < m_shoots.size(); j++)
		{
			temp_table += m_shoots.at(i).at(j);
		}
	}
	return temp_table;
}

void Board::load_boards(string loaded)
{
	m_ships_put = true;
	int loaded_len = 0;
	string ships_val_s;
	for (int i = 0; i < m_table.size(); i++)
	{
		for (int j = 0; j < m_table.size(); j++)
		{
			m_table.at(i).at(j) = loaded[loaded_len];
			loaded_len++;
		}
	}
	cout << "Loaded: " << loaded_len << endl;
	for (int i = 0; i < m_shoots.size(); i++)
	{
		for (int j = 0; j < m_shoots.size(); j++)
		{
			m_shoots.at(i).at(j) = loaded[loaded_len];
			loaded_len++;
		}
	}
	cout << "Loaded: " << loaded_len << endl;
	ships_val_s += loaded[loaded_len++];
	ships_val_s += loaded[loaded_len];
	m_ships_left = stoi(ships_val_s);
	cout << "Ships left" << m_ships_left << endl;
}

int Board::get_ships_left()
{
	return m_ships_left;
}
char Board::get_prev_val()
{
	return m_previous_value;
}