#ifndef PROJECT1_POSITION_H
#define PROJECT1_POSITION_H

#include "Piece.h"
#include <vector>

using namespace std;

class Position {
private:
    int level;
    int pos;
    Piece piece;
    vector<Position> neighbours;
public:
    Position(int l, int p);

    void setPos(int p);
    void setLevel(int l);
    int getPos() const;
    int getLevel() const;

    void setPiece(Piece piece1);
    Piece getPiece();

    void setNeighbours(vector<Position> v);
    vector<Position> getNeighbours();
    void addNeighbour(const Position& p);
};


#endif //PROJECT1_POSITION_H
