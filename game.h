#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "board.h"
#include "gameConfig.h"
#include "general.h"
using namespace std;



class Game
{
    Board board1{ GameConfig::MIN_X1 };
    Board board2{ GameConfig::MIN_X2 };
public:
    void run();
    Game();  // ctor - set keys
    void gotoxy(short x, short y);
    void drawBoard(int p);
    void printMenu();
    void printInstructionsAndKeys();
    void printTableLine();
    void checkKeyPressed(char keyPressed, Shape& Leftshape, Shape& RightShape);
    char invertToLowerCase(char ch);
    void deployShape(bool& l, bool& r, Shape& s1, Shape& s2);
    void printWinner(int num);
};
