// Game.h
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

const int boardHeight = 18;
const int boardWidth = 12;

class Game {
public:
   // char board[boardHeight][boardWidth];
    
    void gotoxy(short x, short y);
    void drawBoard(int p);
};
