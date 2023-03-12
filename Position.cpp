#include "Position.h"

Position::Position(int l, int p) {
    level = l;
    pos = p;
    neighbours = {};
    piece = Piece();
}

void Position::setPos(int p) {
    pos = p;
}

void Position::setLevel(int l) {
    level = l;
}

int Position::getPos() const {
    return pos;
}

int Position::getLevel() const {
    return level;
}

void Position::setPiece(Piece piece1) {
    piece = piece1;
}

Piece Position::getPiece() {
    return piece;
}

void Position::setNeighbours(vector<Position> v) {
    neighbours = v;
}

vector<Position> Position::getNeighbours() {
    return neighbours;
}

void Position::addNeighbour(const Position& p) {
    neighbours.push_back(p);
}