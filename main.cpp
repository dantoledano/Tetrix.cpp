// main.cpp
#include "Game.h"


int main() {

    Game tetrisGame;
    for (size_t k = 0; k < 5; k++)
    {
        tetrisGame.drawBoard(10);
        tetrisGame.drawBoard(40);
        tetrisGame.gotoxy(15, k + 10);
        cout << "*";
        Sleep(700);
        system("cls");
    }
    return 0;
}





