/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#ifndef EX2_GAMELOGIC_H
#define EX2_GAMELOGIC_H

enum playerIdentifier {xplayer, oplayer};
enum winner {xWinner, oWinner, draw};

#include "Cell.h"
#include "Board.h"
#include <vector>


/*
 * GameLogic is abstract class that defines the behaviour of general
 * logic that board games might have (checkmoves, updateboard, location's validity,
 * check if game is over and winner declaration are all methods that general board game
 * is supposed to support in.
 * In adition moves is vector of possible moves of the current player that also
 * may be relevant to any board game and therefore i chose to define it in this class.
 */
class GameLogic {
public:
    GameLogic();
    virtual ~GameLogic();
    virtual void CheckPossibleMoves(Board* board, playerIdentifier xPlayerOrOplayer) = 0;
    virtual void UpdateBoard(Board* board, int row, int col, boardContent xOrO) const = 0;
    virtual bool IsLocationValid(const Cell& cell) const = 0;
    virtual bool IsGameOver(Board* board) = 0;
    virtual winner DeclareWinner(Board* board) const = 0;
    vector<Cell> GetMoves() const;
/*private:*/
protected:
    vector<Cell> moves;
};

#endif //EX2_GAMELOGIC_H
