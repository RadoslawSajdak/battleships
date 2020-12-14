// Battleships.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <board.h>
#include <conio.h>
#ifndef _WINDOWS_
#include <Windows.h> // just for sleep
#endif
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

void welcome_screen();

int main()
{

    /* Initialize block*/
    welcome_screen();
    _getch();           // Wait for interaction
    int X = 0;          // 0-8 as rows in my coordinates system
    char Y = 'a';       // a-i as columns

    Board player,cpu;
    player.put_ships();

    /* Main program*/
    while (1) {
        /* Using keyboard to interact with app */
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
        case KEY_ESCAPE:
            exit(EXIT_SUCCESS);
            break;
        } 
        /* Out of range protection */
        if (X > 8) X = 0;
        if (X < 0) X = 8;
        if (Y > 'i') Y = 'a';
        if (Y < 'a') Y = 'i';
        /****************************/
        cpu.cursor(X, Y);
        cpu.draw_table();
    }
}



void welcome_screen()
{
    cout << R"(
                                                                                                                    
                                                                                                                    
    ,---,.                ___      ___      ,--,                           ,---,                                    
  ,'  .'  \             ,--.'|_  ,--.'|_  ,--.'|                         ,--.' |      ,--,   ,-.----.               
,---.' .' |             |  | :,' |  | :,' |  | :                         |  |  :    ,--.'|   \    /  \              
|   |  |: |             :  : ' : :  : ' : :  : '               .--.--.   :  :  :    |  |,    |   :    |  .--.--.    
:   :  :  /  ,--.--.  .;__,'  /.;__,'  /  |  ' |      ,---.   /  /    '  :  |  |,--.`--'_    |   | .\ : /  /    '   
:   |    ;  /       \ |  |   | |  |   |   '  | |     /     \ |  :  /`./  |  :  '   |,' ,'|   .   : |: ||  :  /`./   
|   :     \.--.  .-. |:__,'| : :__,'| :   |  | :    /    /  ||  :  ;_    |  |   /' :'  | |   |   |  \ :|  :  ;_     
|   |   . | \__\/: . .  '  : |__ '  : |__ '  : |__ .    ' / | \  \    `. '  :  | | ||  | :   |   : .  | \  \    `.  
'   :  '; | ," .--.; |  |  | '.'||  | '.'||  | '.'|'   ;   /|  `----.   \|  |  ' | :'  : |__ :     |`-'  `----.   \ 
|   |  | ; /  /  ,.  |  ;  :    ;;  :    ;;  :    ;'   |  / | /  /`--'  /|  :  :_:,'|  | '.'|:   : :    /  /`--'  / 
|   :   / ;  :   .'   \ |  ,   / |  ,   / |  ,   / |   :    |'--'.     / |  | ,'    ;  :    ;|   | :   '--'.     /  
|   | ,'  |  ,     .-./  ---`-'   ---`-'   ---`-'   \   \  /   `--'---'  `--''      |  ,   / `---'.|     `--'---'   
`----'     `--`---'                                  `----'                          ---`-'    `---`                
                                                                                                                    
)" << endl;
    cout << "PRESS ANY KEY TO START!" << endl;
}