#ifndef TILES_H
#define TILES_H

#include <QPixmap>
#include <optional>
#include "Characters.h"

class tiles{
    int row;
    int column;
    int landscape;
    bool isEmpty;
    friend class mapWindow;
    int type = 100;
    int occupiedByIndex = 100;
public:
    tiles() {
        isEmpty = true;
    }

    tiles(int row, int column, int landscape, bool isEmpty/*,
          std::optional<Characters> occupiedBy*/)
        : row(row), column(column), landscape(landscape), isEmpty(isEmpty)/*,
        occupiedBy(std::move(occupiedBy))*/ {}

     tiles(int q, int r) : column(q), row(r) {}

     bool operator==(const tiles &other) const {
         return column == other.column && row == other.row;
     }


};
#endif // TILES_H

