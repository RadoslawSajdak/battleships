// Battleships.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <board.h>
#include <conio.h>
#include <Windows.h> // just for sleep
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int main()
{
    std::cout << "Hello World!\n";
    int X = 0;
    char Y = 'a';
    Board cpu;
    cpu.put_ships();
    while (1) {
        char key = _getch();
        int key_val = key;
        switch (key_val) {
        case KEY_UP:
            X--;
            break;
        case KEY_DOWN:
            X++;
            break;
        case KEY_LEFT:
            Y--;
            break;
        case KEY_RIGHT:
            Y++;
            break;
        } 
        if (X > 8) X = 0;
        if (X < 0) X = 8;
        if (Y > 'i') Y = 'a';
        if (Y < 'a') Y = 'i';
        cpu.cursor(X, Y);
        cpu.draw_table();
    }
}
