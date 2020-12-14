// Battleships.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <board.h>
#include <conio.h>
#ifndef _WINDOWS_
#include <Windows.h> // just for sleep
#endif
#include <Interface.h>
using namespace std;


int main()
{

    /* Initialize block*/
    welcome_screen();
    _getch();           // Wait for interaction
    int X = 0;          // 0-8 as rows in my coordinates system
    char Y = 'a';       // a-i as columns
    int queue = 0;      // store infos about current player
    bool next_player = false, winner = false;

    player1_screen();
    Board player,cpu;
    player.put_ships();
    player2_screen();
    cpu.put_ships();
    /* Main program*/

    while (1)
    {
        Board temp_object;
        temp_object.clear_table();
        /* Using keyboard to interact with app */
        if (queue % 2 == 0)
        {
            player1_screen();
            temp_object = player;
        }
        else
        {
            player2_screen();
            temp_object = cpu;
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
                if (queue % 2 == 0) temp_object.shoot(&X, &Y, cpu);
                else temp_object.shoot(&X, &Y, player);
                queue += 1;
                next_player = true;
                Sleep(5000);
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


