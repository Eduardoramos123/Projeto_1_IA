#include "Piece.h"

Piece::Piece(int i, char s) {
    id = i;
    sym = s;
}

void Piece::setId(int i) {
    id = i;
}

void Piece::setSym(char s) {
    sym = s;
}

void Piece::setCoords(int l, int p) {
    level = l;
    pos = p;
}

char Piece::getSym() const {
    return sym;
}

int Piece::getId() const {
    return id;
}

int Piece::getPos() const {
    return pos;
}

int Piece::getLevel() const {
    return level;
}

Piece::Piece() {
    id = 0;
    sym = ' ';
}
