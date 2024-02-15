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
    Board board1{ GameConfig::MIN_X1 , 0 };
    Board board2{ GameConfig::MIN_X2 , 0 };
    bool isPaused = false;
    int pace;
public:
    static constexpr int EXIT_CHOICE = 9;
    static constexpr int INSTRUCTIONS_CHOICE = 8;
    static constexpr int PAUSE_CHOICE = 2;
    static constexpr int NEW_GAME_CHOICE = 1;
    static constexpr int PACE = 300;
    Game();  // ctor - set keys, score
    bool getIsPaused() const { return this->isPaused; }
    void setIsPaused(bool isPaused) { this->isPaused = isPaused; }
    void run(int& winner);
    void printMenu();
    void printInstructionsAndKeys() const;
    void printTableLine() const;
    void performKeyPressed(char keyPressed, Shape& Leftshape, Shape& RightShape);
    char invertToLowerCase(char ch);
    void printWinner(int num) const;
    void printWinnerIs1() const;
    void printWinnerIs2() const;
    void printItsTie() const;
    void printWelcome(int& winner) const;
    void printGameOver() const;
    void printScore(Board& board1, Board& board2) const;
    void displayBoardsAndBorders();
    void receiveKeyOfPlayer1(const Shape& s1, char& keyPressed, int& numRotationPlayer1, int& xPositionPlayer1);
    void receiveKeyOfPlayer2(const Shape& s2, char& keyPressed, int& numRotationPlayer2, int& xPositionPlayer2);
    void preformUpdatesAfterLanding(Shape& s1, Shape& s2, bool& isShapeOver1, bool& isShapeOver2);

};
