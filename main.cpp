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

    player1_screen();
    Board player,cpu;
    player.put_ships();
    player2_screen();
    cpu.put_ships();
    /* Main program*/
    while (1) {
        /* Using keyboard to interact with app */
        char key = _getch();
        int key_val = key;
        switch (key_val) {
        case KEY_UP:
            X-=1;
            cpu.cursor(&X, &Y);
            break;
        case KEY_DOWN:
            X+= 1;
            cpu.cursor(&X, &Y);
            break;
        case KEY_LEFT:
            Y-= 1;
            cpu.cursor(&X, &Y);
            break;
        case KEY_RIGHT:
            Y+= 1;
            cpu.cursor(&X, &Y);
            break;
        case KEY_ENTER:
            cpu.shoot(&X, &Y,cpu);
            break;
        case KEY_ESCAPE:
            exit(EXIT_SUCCESS);
            break;
        } 
        //cpu.cursor(X, Y);
        //cpu.draw_table();
    }
}


