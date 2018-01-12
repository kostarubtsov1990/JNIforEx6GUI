/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#include "../include/DefaultLogic.h"

DefaultLogic::~DefaultLogic() {
//    cout << "In DefaultLogic D'tor" << endl;
}

//C'tor. allocation and initiallization
DefaultLogic::DefaultLogic() : GameLogic::GameLogic() {
    this->xsLocations = vector<Cell>();
    this->osLocations = vector<Cell>();
    this->m = map<Cell,vector<direction> >();

    this->osLocations.push_back(Cell(3,3));
    this->osLocations.push_back(Cell(4,4));

    this->xsLocations.push_back(Cell(3,4));
    this->xsLocations.push_back(Cell(4,3));
}

void DefaultLogic::CheckPossibleMoves(Board* board,
                                      playerIdentifier xPlayerOrOplayer) {
    //clear data structures' content before each player's turn
    this->xsLocations.clear();
    this->osLocations.clear();
    this->moves.clear();
    this->m.clear();
    vector<direction> emptyCellsAroundCell;

    //insert Xs' locations to xLocations. Ys' locations to osLocation
    for (int i = 0; i < NUM_OF_ROWS; i++) {
        for (int j = 0; j < NUM_OF_COLS; j++) {
            if (board->getBoardContent()[i][j] == X) {
//                cout << "bla" << endl;
                this->xsLocations.push_back(Cell(i,j));
            }
            if (board->getBoardContent()[i][j] == O) {
                this->osLocations.push_back(Cell(i,j));
            }
        }
    }

    //xplayer
    if (xPlayerOrOplayer == xplayer) {
        for (int i = 0; i < this->osLocations.size(); i++) {
            emptyCellsAroundCell =
                    this->possibleLocAroundSpecificCell(board, osLocations[i]);
            if (!emptyCellsAroundCell.empty()) {
                this->UpdateMovesVector(board, X, emptyCellsAroundCell, osLocations[i]);
            }//else..
        }
    }
    //oplayer
    else {
        for (int i = 0; i < this->xsLocations.size(); i++) {
            emptyCellsAroundCell = this->possibleLocAroundSpecificCell(board,xsLocations[i]);
            if (!emptyCellsAroundCell.empty()) {
                this->UpdateMovesVector(board,O,emptyCellsAroundCell,xsLocations[i]);
            }
        }
    }
//    this->xsLocations.clear();
//    this->osLocations.clear();
}

/*const*/ vector<direction> DefaultLogic::possibleLocAroundSpecificCell(Board* board, const Cell &currentCell) const {
    int row = currentCell.getX();
    int col = currentCell.getY();

    vector<direction> aroundCell;

    //check index out of bound. add directions of Empty locations into "aroundCell"
    if (row > LOWER_BOUND) {
        if (board->getBoardContent()[row - 1][col] == Empty) {
            aroundCell.push_back(up);
        }
    }
    if ((row > LOWER_BOUND) && (col < UPPER_BOUND)) {
        if (board->getBoardContent()[row - 1][col + 1] == Empty) {
            aroundCell.push_back(upRight);
        }
    }
    if (col < UPPER_BOUND) {
        if (board->getBoardContent()[row][col + 1] == Empty) {
            aroundCell.push_back(Right);
        }
    }
    if ((row < UPPER_BOUND) && (col < UPPER_BOUND)) {
        if (board->getBoardContent()[row + 1][col + 1] == Empty) {
            aroundCell.push_back(rightDown);
        }
    }
    if (row < UPPER_BOUND) {
        if (board->getBoardContent()[row + 1][col] == Empty) {
            aroundCell.push_back(down);
        }
    }
    if (row < UPPER_BOUND && col > LOWER_BOUND) {
        if (board->getBoardContent()[row + 1][col - 1] == Empty) {
            aroundCell.push_back(downLeft);
        }
    }
    if (col > LOWER_BOUND) {
        if (board->getBoardContent()[row][col - 1] == Empty) {
            aroundCell.push_back(Left);
        }
    }
    if (row > LOWER_BOUND && col > LOWER_BOUND) {
        if (board->getBoardContent()[row - 1][col - 1] == Empty) {
            aroundCell.push_back(upLeft);
        }
    }
    //return directions of empty cells around current cell.
    return aroundCell;
}

void DefaultLogic::UpdateMovesVector(Board* board, boardContent xOrOplayer,
                                     const vector<direction> &emptyCells, const Cell &cell) {

    for (int i = 0; i < emptyCells.size(); ++i) {
            vector<direction> vec;
            int row = cell.getX();
            int col = cell.getY();

            if (emptyCells[i] == up) {
                //while not empty and not xplayer (meaning we run on Xs' cells)
                while (board->getBoardContent()[row][col] != Empty &&
                        board->getBoardContent()[row][col] != xOrOplayer && row < UPPER_BOUND) {
                    row++;
                }
                //reached block from the other side
                if (board->getBoardContent()[row][col] == xOrOplayer) {
                    //update map
                    if (!this->IsLocationValid(Cell(cell.getX() - 1, cell.getY()))) {
                        moves.push_back(Cell(cell.getX() - 1, cell.getY()));

                        vec.push_back(down);
                        //key doesnt exist, so it adds the key with its value (=vec) to the map.
                        //if key already exists, it updates its value to be vec.
                        this->m[Cell(cell.getX() - 1,
                                     cell.getY())] = vec;
                    }
                    else {
                        this->m[Cell(cell.getX() - 1, cell.getY())].push_back(down);
                    }
                }
            }
            else if (emptyCells[i] == upRight) {
                while (board->getBoardContent()[row][col] != Empty && board->getBoardContent()[row][col] != xOrOplayer
                        && row < UPPER_BOUND && col > LOWER_BOUND) {
                    row++;
                    col--;
                }
                if (board->getBoardContent()[row][col] == xOrOplayer) {
                    if (!this->IsLocationValid(Cell(cell.getX()-1,cell.getY()+1))) {
                        moves.push_back(Cell(cell.getX() - 1, cell.getY() + 1));
                        vec.push_back(downLeft);
                        this->m[Cell(cell.getX() - 1, cell.getY() + 1)] = vec;
                    }
                    else {
                        this->m[Cell(cell.getX()-1,cell.getY()+1)].push_back(downLeft);
                    }
                }
            }
            else if (emptyCells[i] == Right) {
                while (board->getBoardContent()[row][col] != Empty && board->getBoardContent()[row][col] != xOrOplayer && col > LOWER_BOUND) {
                        col--;
                }
                if (board->getBoardContent()[row][col] == xOrOplayer) {
                    if (!this->IsLocationValid(Cell(cell.getX(),cell.getY()+1))) {
                        moves.push_back(Cell(cell.getX(), cell.getY() + 1));
                        vec.push_back(Left);
                        this->m[Cell(cell.getX(), cell.getY() + 1)] = vec;
                    }
                    else {
                        this->m[Cell(cell.getX(),cell.getY()+1)].push_back(Left);
                    }
                }
            }
            else if (emptyCells[i] == rightDown) {
                while (board->getBoardContent()[row][col] != Empty && board->getBoardContent()[row][col] != xOrOplayer
                        && row > LOWER_BOUND && col > LOWER_BOUND) {
                    row--;
                    col--;
                }
                if (board->getBoardContent()[row][col] == xOrOplayer) {
                    if (!this->IsLocationValid(Cell(cell.getX()+1,cell.getY()+1))) {
                        moves.push_back(Cell(cell.getX() + 1, cell.getY() + 1));
                        vec.push_back(upLeft);
                        this->m[Cell(cell.getX() + 1, cell.getY() + 1)] = vec;
                    }
                    else {
                        this->m[Cell(cell.getX()+1,cell.getY()+1)].push_back(upLeft);
                    }
                }
            }
            else if (emptyCells[i] == down) {
                while (board->getBoardContent()[row][col] != Empty && board->getBoardContent()[row][col] != xOrOplayer && row > LOWER_BOUND) {
                    row--;
                }
                if (board->getBoardContent()[row][col] == xOrOplayer) {
                    if (!this->IsLocationValid(Cell(cell.getX()+1,cell.getY()))) {
                        moves.push_back(Cell(cell.getX() + 1, cell.getY()));
                        vec.push_back(up);
                        this->m[Cell(cell.getX() + 1, cell.getY())] = vec;
                    }
                    else {
                        this->m[Cell(cell.getX()+1,cell.getY())].push_back(up);
                    }
                }
            }
            else if (emptyCells[i] == downLeft) {
                while (board->getBoardContent()[row][col] != Empty && board->getBoardContent()[row][col] != xOrOplayer
                        && row > LOWER_BOUND && col < UPPER_BOUND) {
                    row--;
                    col++;
                }
                if (board->getBoardContent()[row][col] == xOrOplayer) {
                    if (!this->IsLocationValid(Cell(cell.getX()+1,cell.getY()-1))) {
                        moves.push_back(Cell(cell.getX() + 1, cell.getY() - 1));
                        vec.push_back(upRight);
                        this->m[Cell(cell.getX() + 1, cell.getY() - 1)] = vec;
                    }
                    else {
                        this->m[Cell(cell.getX()+1,cell.getY()-1)].push_back(upRight);
                    }
                }
            }
            else if (emptyCells[i] == Left) {
                while (board->getBoardContent()[row][col] != Empty && board->getBoardContent()[row][col] != xOrOplayer && col < UPPER_BOUND) {
                    col++;
                }
                if (board->getBoardContent()[row][col] == xOrOplayer) {
                    if (!this->IsLocationValid(Cell(cell.getX(),cell.getY()-1))) {
                        moves.push_back(Cell(cell.getX(), cell.getY() - 1));
                        vec.push_back(Right);
                        this->m[Cell(cell.getX(), cell.getY() - 1)] = vec;
                    }
                    else {
                        this->m[Cell(cell.getX(),cell.getY()-1)].push_back(Right);
                    }
                }
            }
            else {//(emptyCells[i] == upLeft)
                while (board->getBoardContent()[row][col] != Empty && board->getBoardContent()[row][col] != xOrOplayer
                        && col < UPPER_BOUND && row < UPPER_BOUND) {
                    col++;
                    row++;
                }
                if (board->getBoardContent()[row][col] == xOrOplayer) {
                    if (!this->IsLocationValid(Cell(cell.getX()-1,cell.getY()-1))) {
                        moves.push_back(Cell(cell.getX() - 1, cell.getY() - 1));
                        vec.push_back(rightDown);
                        this->m[Cell(cell.getX() - 1, cell.getY() - 1)] = vec;
                    }
                    else {
                        this->m[Cell(cell.getX()-1,cell.getY()-1)].push_back(rightDown);
                    }
                }
            }
    }
}

void DefaultLogic::UpdateBoard(Board *board, int row, int col, boardContent xOrO) const {

    //(row,col) is the chosen cell.
    boardContent** content = board->getBoardContent();
    vector<direction> directions;
    directions = this->GetMap()[Cell(row,col)];
    //put the symbol of the current player in the chosen position of the board
    content[row][col] = xOrO;

    //m isnt empty
    if (!directions.empty()) {
        for (int i = 0; i < directions.size() ; ++i) {
            int k = 0;
            int j = 0;
            if (directions[i] == up) {
                //run to the current direction (up in this case) till the block
                for (k = row-1; content[k][col] != xOrO; k--) {
                    //exchange symbols according to XOrO value
                    if (xOrO == X) {
                        content[k][col] = X;
                    }
                    else {
                        content[k][col] = O;
                    }
                }
            }
            if (directions[i] == upRight) {
                for (k = row-1, j = col+1; content[k][j] != xOrO; k--, j++) {
                    if (xOrO == X) {
                        content[k][j] = X;
                    }
                    else {
                        content[k][j] = O;
                    }
                }
            }
            if (directions[i] == Right) {
                for (j = col+1; content[row][j] != xOrO; j++) {
                    if (xOrO == X) {
                        content[row][j] = X;
                    }
                    else {
                        content[row][j] = O;
                    }
                }
            }
            if (directions[i] == rightDown) {
                for (k = row+1, j = col+1; content[k][j] != xOrO; k++,j++) {
                    if (xOrO == X) {
                        content[k][j] = X;
                    }
                    else {
                        content[k][j] = O;
                    }
                }
            }
            if (directions[i] == down) {
                for (k = row+1; content[k][col] != xOrO; k++) {
                    if (xOrO == X) {
                        content[k][col] = X;
                    }
                    else {
                        content[k][col] = O;
                    }
                }
            }
            if (directions[i] == downLeft) {
                for (k = row+1, j = col-1; content[k][j] != xOrO; k++,j--) {
                    if (xOrO == X) {
                        content[k][j] = X;
                    }
                    else {
                        content[k][j] = O;
                    }
                }
            }
            if (directions[i] == Left) {
                for (j = col-1;  content[row][j] != xOrO; j--) {
                    if (xOrO == X) {
                        content[row][j] = X;
                    }
                    else {
                        content[row][j] = O;
                    }
                }
            }
            if (directions[i] == upLeft) {
                for (k = row-1, j = col-1; content[k][j] != xOrO ; k--, j--) {
                    if (xOrO == X) {
                        content[k][j] = X;
                    }
                    else {
                        content[k][j] = O;
                    }
                }
            }
        }
    }
}

bool DefaultLogic::IsLocationValid(const Cell& cell) const {
    //run on the moves vector and check if the current cell is in the moves vec
    for (int i = 0; i < this->moves.size(); i++) {
        if (moves[i] == cell) {
            return true;
        }
    }
    return false;
}

bool DefaultLogic::IsGameOver(Board* board) {
    bool xPlayerMoves = true;
    bool oPlayerMoves = true;
    this->CheckPossibleMoves(board,xplayer);
    if (this->moves.empty()) {
        xPlayerMoves = false;
    }
    else {
        xPlayerMoves = true;
    }
    this->CheckPossibleMoves(board,oplayer);
    if(this->moves.empty()) {
        oPlayerMoves = false;
    }
    else {
        oPlayerMoves = true;
    }
    this->moves.clear();
    this->osLocations.clear();
    this->xsLocations.clear();
    this->m.clear();
    //true (=game over) if both players have nowhere to move
    return !(xPlayerMoves || oPlayerMoves);
}

winner DefaultLogic::DeclareWinner(Board* board) const {
    int numOfXs = 0;
    int numOfOs = 0;
    //increment X and Y counters according to the current board
    for (int i = 0; i < NUM_OF_ROWS; i++) {
        for (int j = 0; j < NUM_OF_COLS; j++) {
            if(board->getBoardContent()[i][j] == X) {
                numOfXs++;
            }
            else {//verfiy if it's necessarily either O or X
                numOfOs++;
            }
        }
    }
    if (numOfXs > numOfOs) {
        cout << "X Player Is The Winner!" << endl;
        return xWinner;
    }
    else if (numOfOs > numOfXs){
        cout << "O Player Is The Winner!" << endl;
        return oWinner;
    }
    else {
        cout << "Draw!" << endl;
        return draw;
    }
}

map<Cell,vector<direction> > DefaultLogic::GetMap() const {
    return this->m;
}