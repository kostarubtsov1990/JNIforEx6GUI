/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#ifndef EX2_CELL_H
#define EX2_CELL_H

#include <iostream>
using namespace std;

/*
 *Cell is a class that represents current location on the board
 * according to (x,y) coordinates. In addition, the moves vector
 * and the map are data structures that holds the cells that
 * represent the possible moves of the cuurent player.
 */
class Cell {
private:
    int xCord;
    int yCord;

public:
    Cell();
    Cell(int x, int y);
    int getX() const;
    int getY() const;
    void printFormatOfCell() const;
    bool operator == (const Cell &cell) const;
    //needed for the map data structure
    friend bool operator < (const Cell& firstCell, const Cell& secondCell);
};
#endif //EX2_CELL_H
