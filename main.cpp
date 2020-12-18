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
using namespace std;

void save(Board player_1, Board player_2)
{
    string data_to_save;
    ofstream save_file;
    if (player_1.get_ships_left() > 9 && player_2.get_ships_left() > 9)
        data_to_save = player_1.get_table() + player_1.get_shoots() + to_string(player_1.get_ships_left()) + player_2.get_table() + player_2.get_shoots() + to_string(player_1.get_ships_left());
    if (player_1.get_ships_left() <= 9 && player_2.get_ships_left() <= 9)
        data_to_save = player_1.get_table() + player_1.get_shoots() + "0" + to_string(player_1.get_ships_left()) + player_2.get_table() + player_2.get_shoots() + "0" + to_string(player_1.get_ships_left());
    else if(player_1.get_ships_left() <= 9)
        data_to_save = player_1.get_table() + player_1.get_shoots() + "0" + to_string(player_1.get_ships_left()) + player_2.get_table() + player_2.get_shoots() + to_string(player_2.get_ships_left());
    else if(player_2.get_ships_left() <= 9)
        data_to_save = player_1.get_table() + player_1.get_shoots() + to_string(player_1.get_ships_left()) + player_2.get_table() + player_2.get_shoots() + "0" + to_string(player_1.get_ships_left());
    save_file.open("Saves.txt", std::ofstream::trunc);
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

    int loaded_len = 0;
    for (int i = 0; i < 164; i++)
    {
            player_data1 += load_data[loaded_len];
            loaded_len++;
    }
    cout << "Loaded: " << loaded_len << endl;
    for (int j = 0; j < 164; j++)
    {
            player_data2 += load_data[loaded_len];;
            loaded_len++;
    }
    cout << "Loaded: " << loaded_len << endl;

    player_1->load_boards(player_data1);
    player_2->load_boards(player_data2);
}

int main()
{
    int mode = 0;
    /* Initialize block*/
#if DEBUG_LEVEL < 1
    welcome_screen();
    Sleep(2000);
    start_options();
    while (mode > 2 || mode < 1)
    {
        cin >> mode;
        if (mode != 1 && mode != 2) cout << "Wrong data input! Try again!";
    }
    cout << "PRESS ANY KEY TO START!" << endl;
    
#endif
    _getch();           // Wait for interaction
    int X = 0;          // 0-8 as rows in my coordinates system
    char Y = 'a';       // a-i as columns
    int queue = 0;      // store infos about current player
    bool next_player = false, winner = false;

    
    Board player,cpu;
    if (mode == 1)
    {
        ofstream f;
        f.open("Saves.txt", std::ofstream::trunc);
        f.close();

        player1_screen();
        player.put_ships();
        player2_screen();
        cpu.put_ships();
    }
    else
    load(&player, &cpu);
    /* Main program*/

    while (1)
    {
        Board temp_object;
        temp_object.clear_table();
        /* Using keyboard to interact with app */
#if DEBUG_LEVEL < 2
        if (queue % 2 == 0)
        {
            player1_screen();
            temp_object = player;
        }
#endif
#if DEBUG_LEVEL < 1
        else if (queue % 2 == 1)
        {
            player2_screen();
            temp_object = cpu;
        }
#endif
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
#if DEBUG_LEVEL < 2
            case KEY_ENTER:
                if (queue % 2 == 0) temp_object.shoot(&X, &Y, cpu);
                else temp_object.shoot(&X, &Y, player);

                if (temp_object.get_prev_val() != 'c' && temp_object.get_prev_val() != 'x')
                {
                    queue += 1;
                    next_player = true;
                    Sleep(5000);
                }
                break;
#endif
            case KEY_SAVE:
                save(player, cpu);
                break;
            case KEY_ESCAPE:
                exit(EXIT_SUCCESS);
                break;
            }

            if (next_player)
            {
                if (temp_object.get_ships_val() == 0) winner = true;
                if ((queue - 1) % 2 == 0) player = temp_object;
                else cpu = temp_object;
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


