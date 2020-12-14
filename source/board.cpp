#include "board.h"
Board::Board()
{
	
	m_previous_value = ' ';
	m_ships_left = 14;

	/* Array with size of ships*/
	m_ships.push_back(4);
	m_ships.push_back(3);
	m_ships.push_back(2);
	m_ships.push_back(2);
	for (int i = 0; i < 3; i++) m_ships.push_back(1);

	vector < char > cols;
	for (int i = 0; i < 9; i++)
	{
		cols.push_back(' ');
	}
	for (int i = 0; i < 9; i++)
	{
		m_table.push_back(cols);
	}

	clear_table();
	
}

Board::~Board()
{
	;
}

void Board::clear_table()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			m_table.at(i).at(j) = ' ';
		}
	}
	m_table.at(8).at(8) = '?'; // initialize cursor
	draw_table();
}

void Board::draw_table()
{
	/* Making A-I columns*/
	system("CLS");
	cout << "   ";
	for (int i = 0; i < m_table.size(); i++) cout << char('A' + i) << "   ";
	cout << endl;
	/* Fill up board with actual data*/
	for (int i = 0; i < m_table.size(); i++)
	{
		cout << i << ": "; // Print row numbers
		for (int j = 0; j < m_table.at(i).size(); j++)
		{
			cout << m_table.at(i).at(j) << " | ";
		}
		cout << endl;
		for (int j = 0; j < m_table.at(i).size() * 2 + 1;  j++) cout << "--";
		cout << endl;
	}

	cout << "Move - arrows \nConfirm - Enter \nRotate ship - space \nExit - exc" << endl;
}

void Board::cursor( int row,  char cols)
{
	vector<char>::iterator old;

	/* Finding old position of cursor and remove it*/
	for (int i = 0; i < m_table.size(); i++)
	{
		old = find(m_table.at(i).begin(), m_table.at(i).end(), '?');
		if (old == m_table.at(i).end()) continue;
		else
		{
			break;
		}
	}

	*old = m_previous_value;

	int temp_cols = 0;
	if (int(cols) > 96 && int(cols) < 106) temp_cols = cols - 97;
	else if (int(cols) > 64 && int(cols) < 74) temp_cols = cols - 65;
	else exit(EXIT_FAILURE);

	m_previous_value = m_table.at(row).at(temp_cols);
 	m_table.at(row).at(temp_cols) = '?'; 
	
} 

void Board::put_ships()
{

	int X = 0, Y = 0;
	int pos_a = 0, pos_b = 0;
	bool vertical = true, error = false;
	vector <vector <char>> cp_board;
	cp_board = m_table;
	int ship_iterator = 0;
	while (1) {
		
		char key = _getch();
		int key_val = key;
		switch (key_val) {
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
			if( Y < 9 - m_ships.at(ship_iterator) ) Y++;
			for (int i = 0; i < m_ships.at(ship_iterator); i++) 
				if (vertical) {
					m_table.at(X).at((Y + i) % 9) = 'o';
				}
			m_table.at(X).at((Y-1)%9) = cp_board.at(X).at((Y-1)   % 9);
			if (!vertical)
			{
				for (int i = 0; i < m_ships.at(ship_iterator); i++)
				{
					m_table.at((X + i)%9).at(Y) = 'o';
					m_table.at((X + i) % 9).at(Y - 1) = cp_board.at((X + i) % 9).at(Y - 1);
				}
			}

			break;
		case KEY_SPACE:
			m_table = cp_board;
			vertical = !vertical;
			break;
		case KEY_ENTER:
			error = false;
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
			if(vertical)
			{
				for (int j = 0; j < m_ships.at(ship_iterator); j++)
				{
					if (cp_board.at(X).at(Y+j) == 'o')
					{
						cout << "\n>>> You can\'t cross ships! Try again! <<< \n";
						Sleep(2000);
						clear_table();
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
						clear_table();
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
			
			break;
		case KEY_ESCAPE:
			exit(EXIT_SUCCESS);
			break;
		}
		draw_table();
		if (ship_iterator == m_ships.size()) break;
	}

}
