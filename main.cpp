// Battleships.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <board.h>
#include <conio.h>
#ifndef _WINDOWS_
#include <Windows.h> // just for sleep
#endif
#include <Interface.h>
#include <fstream>

char mode = 0;
using namespace std;


void save(Board player_1, Board player_2);          // Declaration of function to save game data
void load(Board* player_1, Board* player_2);        // Declaration of function to load game data

int main()
{
    /* Initialize block*/
    welcome_screen();
    Sleep(2000);
    start_options();
    /* Wait for choose game mode and verify input */
    while (mode > '2' || mode < '1')
    {
        cin >> mode;
        if (mode != '1' && mode != '2') cout << "Wrong data input! Try again!";
    }
    cout << "PRESS ANY KEY TO START!" << endl;

    _getch();           // Wait for interaction
    int X = 0;          // 0-8 as rows in my coordinates system
    char Y = 'a';       // a-i as columns
    int queue = 0;      // store infos about current player
    bool next_player = false, winner = false;

    
    Board player_1,player_2;
    if (mode == '2')   load(&player_1, &player_2);
    if (mode == '1')
    {
        ofstream f;
        f.open("Saves.txt", std::ofstream::trunc);      // Clear file with saved data
        f.close();

        player1_screen();
        player_1.put_ships();
        player2_screen();
        player_2.put_ships();
    }
    
    /* Main program*/

    while (1)
    {
        Board temp_object;
        temp_object.clear_table();
        /* Using keyboard to interact with app */
        if (queue % 2 == 0)
        {
            player1_screen();
            temp_object = player_1;
        }
        else if (queue % 2 == 1)
        {
            player2_screen();
            temp_object = player_2;
        }
        next_player = false;
        temp_object.cursor(&X, &Y);
        while (1) {
            char key = _getch();
            int key_val = key;
            switch (key_val) {
            case KEY_UP:
                X -= 1;
                temp_object.cursor(&X, &Y);
                break;
            case KEY_DOWN:
                X += 1;
                temp_object.cursor(&X, &Y);
                break;
            case KEY_LEFT:
                Y -= 1;
                temp_object.cursor(&X, &Y);
                break;
            case KEY_RIGHT:
                Y += 1;
                temp_object.cursor(&X, &Y);
                break;
            case KEY_ENTER:
                if (queue % 2 == 0) temp_object.shoot(&X, &Y, player_2);
                else temp_object.shoot(&X, &Y, player_1);
                /* Overwrite protection */
                if (temp_object.get_prev_val() != 'c' && temp_object.get_prev_val() != 'x')
                {
                    queue += 1;
                    next_player = true;
                    Sleep(2000);
                }
                break;
            case KEY_SAVE:
                save(player_1, player_2);
                break;
            case KEY_ESCAPE:
                exit(EXIT_SUCCESS);
                break;
            }

            if (next_player)
            {
                /* If no one won, continue game*/
                if (temp_object.get_ships_left() == 0) winner = true;
                /* Save data from turn before changing player */
                if ((queue - 1) % 2 == 0) player_1 = temp_object;
                else player_2 = temp_object;
                break;
            }
        }
        if (winner)
        {
            winner_screen();
            if ((queue - 1) % 2 == 0) player1_screen();
            else player2_screen();
        }
    }
}

void save(Board player_1, Board player_2)
{
    string data_to_save;
    ofstream save_file;
    /* We need to provide constant len of data. Eg. if ships left is 7, saved data is 07*/
    if (player_1.get_ships_left() > 9 && player_2.get_ships_left() > 9)
        data_to_save = player_1.get_table() + player_1.get_shoots() + to_string(player_1.get_ships_left()) + player_2.get_table() + player_2.get_shoots() + to_string(player_1.get_ships_left());
    if (player_1.get_ships_left() <= 9 && player_2.get_ships_left() <= 9)
        data_to_save = player_1.get_table() + player_1.get_shoots() + "0" + to_string(player_1.get_ships_left()) + player_2.get_table() + player_2.get_shoots() + "0" + to_string(player_1.get_ships_left());
    else if (player_1.get_ships_left() <= 9)
        data_to_save = player_1.get_table() + player_1.get_shoots() + "0" + to_string(player_1.get_ships_left()) + player_2.get_table() + player_2.get_shoots() + to_string(player_2.get_ships_left());
    else if (player_2.get_ships_left() <= 9)
        data_to_save = player_1.get_table() + player_1.get_shoots() + to_string(player_1.get_ships_left()) + player_2.get_table() + player_2.get_shoots() + "0" + to_string(player_1.get_ships_left());
    save_file.open("Saves.txt", std::ofstream::trunc);          // Overwrite old data
    save_file << data_to_save;
    save_file.close();
    cout << "Saved game!!" << endl;
}

void load(Board* player_1, Board* player_2)
{
    string load_data, player_data1, player_data2;
    ifstream load_file;

    load_file.open("Saves.txt");
    getline(load_file, load_data);
    load_file.close();

    /* Decode file */
    if (load_data.size() > 10)
    {
        int loaded_len = 0;
        for (int i = 0; i < 164; i++)
        {
            player_data1 += load_data[loaded_len];
            loaded_len++;
        }

        for (int j = 0; j < 164; j++)
        {
            player_data2 += load_data[loaded_len];;
            loaded_len++;
        }

        /* Write data to players */
        player_1->load_boards(player_data1);
        player_2->load_boards(player_data2);
    }
    /* Loading empty file will cause a new game*/
    else
    {
        cout << "There's no save data! Starting a new game!" << endl;
        mode = '1';
        Sleep(2000);
    }
}
