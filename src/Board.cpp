/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#include "../include/Board.h"

Board::~Board() {
    //cout << "Inside Board's D'tor" << endl;
   for (int i = 0; i < boardSize; i++) {
        delete this->content[i];
    }
    delete content;
}

//C'tor
Board::Board(int boardSize) {
    this->boardSize;
    this->content = new boardContent*[boardSize];
    for(int i = 0; i < boardSize; ++i)
        this->content[i] = new boardContent[boardSize];
    //initiallization
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            this->content[i][j] = Empty;
        }
    }
    this->content[3][3] = O;
    this->content[3][4] = X;
    this->content[4][3] = X;
    this->content[4][4] = O;

}


Board::Board(const Board &other, int boardSize) {
    this->boardSize = boardSize;
    this->content = new boardContent*[boardSize];
    for(int i = 0; i < boardSize; ++i)
        this->content[i] = new boardContent[boardSize];
    //Copy the data from the other object.
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            this->content[i][j] = other.getBoardContent()[i][j];
        }
    }
}

Board::Board(const string &s, int boardSize) {
    this->boardSize = boardSize;
    this->content = new boardContent*[boardSize];
    for(int i = 0; i < boardSize; ++i) {
        this->content[i] = new boardContent[boardSize];
    }

    int k = 0;
    for (int i = 0; i < boardSize; ++i) {
        int j = 0;
        while (s[k] != '\n') {

            if (s[k] == 'X') {

                this->content[i][j] = X;
            }
            else if (s[k] == 'O') {

                this->content[i][j] = O;
            }
            else {

                this->content[i][j] = Empty;

            }
            k++;
            j++;
        }
        k++;
    }
}

Board::Board(boardContent ** boardContent, int boardSize) {
    this->boardSize = boardSize;
    this->content = boardContent;
}

int Board::GetSize() {
    return boardSize;
}

void Board::printBoard() {
    //print first line of board
    for (int i = 0; i < boardSize; i++) {
        cout << " | " << i+1;
    }
    cout << " |" << endl;
    int index = 0;
    //print the content of the board in the correct format
    for (int i = 0; i < (2 * boardSize) + 1; i++) {
        //broken line
        if (i % 2 == 0) {
            printBrokenLine();
        }
            //print line of the board in the correct format
        else {
            cout << index + 1 ;
            for (int j = 0; j < boardSize; j++) {
                cout << "| " << this->calcStrValueOfBoardContent
                        (this->content[index][j]) << " ";
            }
            cout << '|' << endl;
            index++;
        }
    }
}

void Board::printBrokenLine() const {
    for (int i = 0; i < 2 + (4*boardSize); i++) {
        cout << '-';
    }
    cout << endl;
}

char Board::calcStrValueOfBoardContent(boardContent symbol) const {
    //return the correct value of the number that represents the relevant enum
    if (symbol == 0) {
        return 'X';
    }
    else if (symbol == 1) {
        return 'O';
    }
    else {
        return ' ';
    }
}

bool Board::operator==(const Board &other) const {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (this->content[i][j] != other.content[i][j]) {
                return false;
            }
        }
    }
    return true;
}

boardContent** Board::getBoardContent() const {
    return this->content;
}

