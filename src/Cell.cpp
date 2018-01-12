/*
 * Name: Kosta Rubtsov
 * Id: 319206892
 * Name: Alon Barkan
 * Id: 200958296
 */

#include "../include/Cell.h"

Cell::Cell(): xCord(0),yCord(0) {}

Cell::Cell(int x, int y) : xCord(x), yCord(y) {}

void Cell::printFormatOfCell() const {
//    cout << "in printFormatOfCell()" << endl;
 //   cout << this->getX() << endl;
    cout << "(" << this->getX() + 1 << ", " << this->getY() + 1 << ")";
}

int Cell::getX() const {
    return this->xCord;
}

int Cell::getY() const {
    return this->yCord;
}

bool operator < (const Cell& firstCell, const Cell& secondCell) {
    if (firstCell.getX() < secondCell.getX())
        return true;
    if (secondCell.getX() < firstCell.getX())
        return false;

    if (firstCell.getY() < secondCell.getY())
        return true;
    if (secondCell.getY() < firstCell.getY())
        return false;

    return false;
}

bool Cell::operator == (const Cell &cell) const {
    return (this->getY() == cell.getY()) && (this->getX() == cell.getX());
}
