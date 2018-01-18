/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#ifndef EX2_BOARD_H
#define EX2_BOARD_H

#define NUM_OF_COLS 8
#define NUM_OF_ROWS 8
#include <iostream>
using namespace std;

//possible values on the board
enum boardContent {X, O, Empty};

/*
 * Board contains data member content which is allocated dinamically
 * and is the actual board that is printed to the screen.
 * each turn of the game, the current player choose a possible location
 * on the board and the symbols X and Y are updated according to the game rules
 */
class Board {
public:
    ~Board();
    //C'tor
    Board(int);
    Board(const string &s, int);
    Board(const Board &other, int);
    Board(boardContent**, int);
    int GetSize();
    //print the board to the screen with its content and in the correct format
    void printBoard();
    boardContent** getBoardContent() const;
    bool operator ==(const Board &other) const;

private:
    int boardSize;
    //boardContent holds the content of the board
    boardContent** content;
    //print the broken line that appears between each to lines of the board
    void printBrokenLine() const;
    //returns the string value of the relevant enum
    char calcStrValueOfBoardContent(boardContent symbol) const;
};

#endif //EX2_BOARD_H
