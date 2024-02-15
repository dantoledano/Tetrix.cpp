#include "board.h"
#include "point.h"
#include "general.h"
#include "gameConfig.h"
using namespace std;

class Shape;

void Board::setMatrixAt(size_t row, size_t col, char value) {
    matrix[row][col] = value;
}


char Board::getMatrixAt(size_t row, size_t col) const {
    return matrix[row][col];
}


char Board::getKeysAt(size_t index) const {
    return keys[index];
}


Board::Board(int xPos, int score) : xPos(xPos), score(score)
{ // initializing the board to be empty.
    for (int i = 0; i < GameConfig::GAME_HEIGHT; ++i) {
        for (int j = 0; j < GameConfig::GAME_WIDTH; ++j) {
            matrix[i][j] = GameConfig::SPACE;
        }
    }
}


void Board::resetBoard()
{ // empty the board.
    for (int i = 0; i < GameConfig::GAME_HEIGHT; ++i) {
        for (int j = 0; j < GameConfig::GAME_WIDTH; ++j) {
            matrix[i][j] = GameConfig::SPACE;
        }
    }
}


//void Board::setKeys(char leftKey, char rightKey, char rotateKey, char crotateKey, char dropKey)
//{
//    this->keys[0] = leftKey;
//    this->keys[1] = rightKey;
//    this->keys[2] = rotateKey;
//    this->keys[3] = crotateKey;
//    this->keys[4] = dropKey;
//}


void Board::drawBorder() const
{
    for (int col = xPos; col < GameConfig::GAME_WIDTH + xPos; col++)
    {
        gotoxy(col, GameConfig::MIN_Y - 1);
        cout << "-";

        gotoxy(col, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y);
        cout << "-";
    }

    for (int row = GameConfig::MIN_Y - 1; row <= GameConfig::GAME_HEIGHT + GameConfig::MIN_Y; row++)
    {
        gotoxy(xPos - 1, row);
        cout << "|";

        gotoxy(GameConfig::GAME_WIDTH + xPos, row);
        cout << "|";
    }
}



void Board::eraseLine(int indexLine) {
    for (int i = indexLine; i > 0; i--) {
        for (int col = 0; col < GameConfig::GAME_WIDTH; col++) {
            matrix[i][col] = matrix[i - 1][col];
        }
    }
    for (int col = 0; col < GameConfig::GAME_WIDTH; col++) {
        matrix[0][col] = GameConfig::SPACE;
    }
}


bool Board::isFullLine(int line) const {
    for (int i = 0; i < GameConfig::GAME_WIDTH; i++) {
        if (matrix[line][i] == GameConfig::SPACE)
            return false;
    }
    return true;
}


int Board::clearFullLines() {
    int combo = 0;
    for (int i = 0; i < GameConfig::GAME_HEIGHT; i++) {
        if (isFullLine(i)) {
            eraseLine(i);
            DrawBoard();
            combo++;
        }
    }
    return combo;
}

void Board::organizeBoard()
{
    for (int i = GameConfig::GAME_HEIGHT - 2; i >= 0; i--) {
        for (int j = GameConfig::GAME_WIDTH - 1; j >= 0; j--) {
            int count = 0;
            while ((matrix[i + count][j] == GameConfig::BLOCK) && (matrix[i + 1 + count][j] == GameConfig::SPACE)) {
                matrix[i + count][j] = GameConfig::SPACE;
                matrix[i + 1 + count][j] = GameConfig::BLOCK;
                count++;
                if (i + 1 + count > GameConfig::GAME_HEIGHT - 1)
                    break;  // end of board
            }
        }
    }
}


void Board::DrawCubeInBoard(int x, int y, char ch) {
    gotoxy(x + xPos, y + GameConfig::MIN_Y);
    cout << ch;
}


void Board::DrawBoard() {
    for (int i = GameConfig::GAME_HEIGHT - 1; i >= 0; i--) {
        for (int j = 0; j < GameConfig::GAME_WIDTH; j++) {
            if (matrix[i][j] == GameConfig::BLOCK) {
                DrawCubeInBoard(j, i, GameConfig::BLOCK);
            }
            else {
                DrawCubeInBoard(j, i, ' ');
            }
        }
    }
}


bool Board::explod(int activeX, int activeY) {
    int startY, endY;
    int startX, endX;
    bool hasErasedBlocks = false;

    activeY < 4 ? startY = 0 : startY = activeY - 4;
    activeY > 13 ? endY = 17 : endY = activeY + 4;
    activeX < 4 ? startX = 0 : startX = activeX - 4;
    activeX > 7 ? endX = 11 : endX = activeX + 4;

    for (int i = startY; i <= endY; i++) {
        for (int j = startX; j <= endX; j++) {
            if (matrix[i][j] == GameConfig::BLOCK)
                hasErasedBlocks = true;
            matrix[i][j] = GameConfig::SPACE;
        }
    }
    return hasErasedBlocks;
}

/////////////////////////////////////////////////////////////////////


int Board::evaluateScore(const Shape& s) {
    if (s.getId() == GameConfig::BOMB) {
        Board tempBoard = *this;
        bool shouldOrganize = tempBoard.explod(s.getBodyAt(0).getX() - 1, s.getBodyAt(0).getY() - 1);
        if (shouldOrganize)
            tempBoard.organizeBoard();
        tempBoard.clearFullLines();
        int hightOfBoard = tempBoard.getHightOfBoard();
        int gapScore = countGaps() * (-10);
        return ((-1) * hightOfBoard) + gapScore;
    }
    else {
        int linesClearedScore = checkLines(s) * 100;
        int heightScore = s.getSumOfHeights() * 10;
        int gapScore = countGaps() * (-10);
        return  linesClearedScore + heightScore + gapScore;
    }
}


int Board::getHightOfBoard() {
    int sum = 0;
    for (int i = 0; i < GameConfig::GAME_HEIGHT; ++i) {
        for (int j = 0; j < GameConfig::GAME_WIDTH; ++j) {
            if (matrix[i][j] == GameConfig::BLOCK)
                sum += i;
        }
    }
    return sum;
}


int Board::checkLines(const Shape& s) {
    int lines = 0;
    for (int i = 0; i < Shape::NUM_CUBES; i++) {
        if (isFullLine(s.getHeightOfCube(i))) {
            lines++;
        }
    }
    return lines;
}


void Board::findBestMove(Shape& shape, int& chosenRotation, int& chosenPosition) {
    int bestScore, score;
    int numOfRotations = 0, xPosition = 0;
    Shape startLocation = shape;
    for (int rotation = 0; rotation < 4; ++rotation) {
        for (int position = 0; position < GameConfig::GAME_WIDTH; ++position) {
            this->applyMove(shape, rotation, position);
            score = this->evaluateScore(shape);
            shape.updateMatrix(*this, false);
            if (rotation == 0 && position == 0)
                bestScore = score;
            else if (score > bestScore) {
                bestScore = score;
                numOfRotations = rotation;
                xPosition = position;
            }
            shape = startLocation;
        }
        if (shape.getID() == GameConfig::BOMB)
            break; // for a bomb, one loop is enough because rotation is not necessary
    }
    chosenRotation = numOfRotations;
    chosenPosition = xPosition;
}


int Board::getHolesScore() {
    int holesScore = 0;
    for (int j = 0; j < GameConfig::GAME_WIDTH; ++j) {
        bool foundBlock = false;
        for (int i = 0; i < GameConfig::GAME_HEIGHT; ++i) {
            if (matrix[i][j] == '#') {
                foundBlock = true;
            }
            else if (foundBlock && matrix[i][j] == ' ') {
                // Increment holes score for each empty space below a block
                holesScore += 1;
            }
        }
    }
    return holesScore;
}



void Board::applyMove(Shape& shape, int rotation, int position) {
    for (int i = 0; i < rotation; ++i) {
        shape.rotateClockwise(*this);
    }
    int numOfSteps = position - shape.getFirstX();
    // Move the shape to the new position
    while (numOfSteps != 0) {
        if (numOfSteps < 0) {
            shape.moveShapeToTheLeft(*this);
            numOfSteps++;
        }
        else if (numOfSteps > 0) {
            shape.moveShapeToTheRight(*this);
            numOfSteps--;
        }
    }
    // Check if the shape has reached the bottom and move down accordingly
    while (!shape.hasReachedBottom() && !shape.hasReachedToAnotherShape(*this)) {
        shape.moveShapeDown(*this);
    }
    shape.updateMatrix(*this, true);
}


int Board::countGaps() {
    int gap_count = 0;
    for (int col = 0; col < GameConfig::GAME_WIDTH; ++col) {
        bool is_gap = false;
        int row = GameConfig::GAME_HEIGHT - 1;
        while (row >= 0) {
            // Check for an empty cell
            if (matrix[row][col] == ' ') {
                is_gap = true;
            }
            // Check for a filled cell after an empty cell
            else if (matrix[row][col] == '#' && is_gap) {
                ++gap_count;
                is_gap = false;
            }
            --row;
        }
    }
    return gap_count;
}













