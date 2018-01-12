/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#include "../include/GameLogic.h"

GameLogic::GameLogic() {
 //   this->moves = new vector<Cell>();
}

vector<Cell> GameLogic::GetMoves() const {
//    cout << "In GetMoves method." << "moves vector size is: " << this->moves.size() << endl;
    return this->moves;
}

GameLogic::~GameLogic() {
//    cout << "In GameLogic D'tor" << endl;
}
