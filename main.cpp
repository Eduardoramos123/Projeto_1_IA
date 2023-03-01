#include <iostream>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <stack>

using namespace std;

class Piece {
private:
    int id;
    char sym;
    int pos;
    int level;
public:
    Piece(int i, char s);
    void setId(int i);
    void setSym(char s);
    void setCoords(int p, int l);
    int getId() const;
    char getSym() const;
    int getPos() const;
    int getLevel() const;
};

Piece::Piece(int i, char s) {
    id = i;
    sym = s;
    pos = -1;
    level = -1;
}

void Piece::setId(int i) {
    id = i;
}

void Piece::setSym(char s) {
    sym = s;
}

void Piece::setCoords(int p, int l) {
    pos = p;
    level = l;
}

int Piece::getId() const {
    return id;
}

char Piece::getSym() const {
    return sym;
}

int Piece::getPos() const {
    return pos;
}

int Piece::getLevel() const {
    return level;
}

class Position {

};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
