/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#ifndef EX2_DEFAULTLOGIC_H
#define EX2_DEFAULTLOGIC_H

#define UPPER_BOUND 7
#define LOWER_BOUND 0

#include "GameLogic.h"
#include "map"
//#include <algorithm>

enum direction {up, upRight, Right, rightDown, down, downLeft, Left, upLeft};

/*
 * DefaultLogic is derived class of the abstract class "GameLogic".
 * it implements all the pure virtual methods defined in the base class
 * "GameLogic". this class performs the logic of the game.
 * CheckPossibleMoves calculates the possible moves of the current player
 * and saves them in the moves vector.
 * UpdateBoard is responsible to fill the chosen cell with the correct symbol.
 * IsLocationValid checks if the chosen cell belongs to the possible moves
 * of the current player.
 * IsGameOver checks whether the game is over or not according to the
 * moves vector if it's empty or not.
 */
class DefaultLogic : public GameLogic {

public:
    DefaultLogic();
    ~DefaultLogic();
    virtual void CheckPossibleMoves(Board* board, playerIdentifier xPlayerOrOplayer);
    //fill the current cell with the correct symbol and change symbols
    virtual void UpdateBoard(Board* board, int row, int col, boardContent xOrO) const;
    //check if location belongs to the possible moves of the current player
    virtual bool IsLocationValid(const Cell& cell) const;
    //check if game's over
    virtual bool IsGameOver(Board* board);
    //declare if x player one, y player one or draw.
    virtual winner DeclareWinner(Board* board) const;
    map<Cell,vector<direction> > GetMap() const;

private:
    //return vector of all directions around specific cell that are empty.
    /*const*/ vector<direction> possibleLocAroundSpecificCell(Board* board, const Cell &currentCell) const;
    map<Cell,vector<direction> > m;
    /*
     * run over the directions vector of the current cell
     * (the current cell contains either 'X' or 'O'). defines
     * vector of directions (vec). saves in (row,col) the coordinates of the
     * given cell (that contains either 'X' or 'O' as mentioned above). for the
     * current direction, if the board in location (row,col) isn't empty and isnt
     * 'X',change the indexes to the opposite direction of the currentdirection
     */
    void UpdateMovesVector(Board* board, boardContent xOrOPlayer,
                           const vector<direction> &emptyCells, const Cell &cell);
    vector<Cell> xsLocations;
    vector<Cell> osLocations;
};

#endif //EX2_DEFAULTLOGIC_H