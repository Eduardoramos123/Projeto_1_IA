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
private:
    int pos;
    int level;
    Piece* piece;
    vector<Position*> neighbours;
public:
    Position(int p, int l);
    void setPos(int p);
    void setLevel(int l);
    int getPos() const;
    int getLevel() const;
    void setPiece(Piece* piece1);
    Piece* getPiece();
    void setNeighbours(vector<Position*> v);
    vector<Position*> getNeighbours();
    void addNeighbour(Position* p);
};

Position::Position(int p, int l) {
    pos = p;
    level = l;
    piece = nullptr;
    neighbours = {};
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

void Position::setPiece(Piece *piece1) {
    piece = piece1;
}

Piece *Position::getPiece() {
    return piece;
}

void Position::setNeighbours(vector<Position *> v) {
    neighbours = v;
}

vector<Position *> Position::getNeighbours() {
    return neighbours;
}

void Position::addNeighbour(Position *p) {
    neighbours.push_back(p);
}

vector<vector<Position* >> generateGameState(int level, int pos) {
    vector<vector<Position* >> gameState;

    for (int i = 0; i < level; i++) {
        vector<Position*> v;
        for (int j = 0; j < pos; j++) {
            Position* p = new Position(i, j);
            v.push_back(p);
        }
        gameState.push_back(v);
    }

    return gameState;
}

vector<vector<Position* >> generateConnections(vector<vector<Position* >> gameState) {
    vector<vector<Position* >> final = gameState;

    for (int i = 0; i < gameState.size(); i++) {
        for (int j = 0; j < gameState[i].size(); j++) {
            if (i == gameState.size() - 1) {
                if (j == 0) {
                    final[i][j]->addNeighbour(final[i][j + 1]);
                    final[i][j]->addNeighbour(final[i][gameState[i].size() - 1]);
                }
                else if (j == (gameState[i].size() - 1)) {
                    final[i][j]->addNeighbour(final[i][0]);
                    final[i][j]->addNeighbour(final[i][j - 1]);
                }
                else {
                    final[i][j]->addNeighbour(final[i][j + 1]);
                    final[i][j]->addNeighbour(final[i][j - 1]);
                }
            }
            else if (i == 0) {
                final[i][j]->addNeighbour(final[i + 1][j]);
                final[i + 1][j]->addNeighbour(final[i][j]);
                if (j == 0) {
                    final[i][j]->addNeighbour(final[i][j + 1]);
                    final[i][j]->addNeighbour(final[i][gameState[i].size() - 1]);
                }
                else if (j == (gameState[i].size() - 1)) {
                    final[i][j]->addNeighbour(final[i][0]);
                    final[i][j]->addNeighbour(final[i][j - 1]);
                }
                else {
                    final[i][j]->addNeighbour(final[i][j + 1]);
                    final[i][j]->addNeighbour(final[i][j - 1]);
                }
            }
            else if (i % 2 == 0) {
                final[i][j]->addNeighbour(final[i + 1][j]);
                final[i + 1][j]->addNeighbour(final[i][j]);
            }
            else if (i % 2 != 0) {
                if (j == 0) {
                    final[i][j]->addNeighbour(final[i + 1][j + 1]);
                    final[i][j]->addNeighbour(final[i + 1][gameState[i].size() - 1]);

                    final[i + 1][j + 1]->addNeighbour(final[i][j]);
                    final[i + 1][gameState[i].size() - 1]->addNeighbour(final[i][j]);
                }
                else if (j == (gameState[i].size() - 1)) {
                    final[i][j]->addNeighbour(final[i + 1][0]);
                    final[i][j]->addNeighbour(final[i + 1][j - 1]);

                    final[i + 1][0]->addNeighbour(final[i][j]);
                    final[i + 1][j - 1]->addNeighbour(final[i][j]);
                }
                else {
                    final[i][j]->addNeighbour(final[i + 1][j + 1]);
                    final[i][j]->addNeighbour(final[i + 1][j - 1]);

                    final[i + 1][j + 1]->addNeighbour(final[i][j]);
                    final[i + 1][j - 1]->addNeighbour(final[i][j]);
                }
            }
        }
    }
    return final;
}

bool validGameState(vector<vector<Position*>> gameState) {
    for (int i = 0; i < gameState.size(); i++) {
        for (int j = 0; j < gameState[i].size(); j++) {
            if (gameState[i][j]->getNeighbours().size() != 3) {
                return false;
            }
        }
    }
    return true;
}

bool canMove(int pos1, int level1, int pos2, int level2, vector<vector<Position*>> gameState) {
    Position* initial = gameState[level1][pos1];
    vector<Position*> neighbours = initial->getNeighbours();

    for (int i = 0; i < neighbours.size(); i++) {
        int check_pos = neighbours[i]->getPos();
        int check_level = neighbours[i]->getLevel();

        if (check_level == level2 && check_pos == pos2 && gameState[check_level][check_pos]->getPiece() == nullptr) {
            return true;
        }
    }
    return false;
}

bool isStuck(vector<vector<Position*>> gameState, Piece* piece) {
    Position* initial = gameState[piece->getLevel()][piece->getPos()];
    vector<Position*> neighbours = initial->getNeighbours();

    for (int i = 0; i < neighbours.size(); i++) {
        int check_pos = neighbours[i]->getPos();
        int check_level = neighbours[i]->getLevel();
        if (canMove(piece->getPos(), piece->getLevel(), check_pos, check_level, gameState)) {
            return false;
        }
    }
    return true;
}

vector<vector<Position*>> move(Piece* piece, int level, int pos, vector<vector<Position*>> gameState) {
    vector<vector<Position*>> final = gameState;

    final[piece->getLevel()][piece->getPos()]->setPiece(nullptr);
    piece->setCoords(pos, level);
    final[level][pos]->setPiece(piece);

    return final;
}

bool canPlace(int level, int pos, vector<vector<Position*>> gameState) {
    if (gameState[level][pos]->getPiece() != nullptr) {
        return false;
    }

    return true;
}

vector<vector<Position*>> place(Piece* piece, int level, int pos, vector<vector<Position*>> gameState) {
    vector<vector<Position*>> final = gameState;

    piece->setCoords(pos, level);
    final[level][pos]->setPiece(piece);
    return final;
}

vector<vector<char>> getSymbols(vector<vector<Position*>> gameState) {
    vector<vector<char>> final;

    for (int i = 0; i < gameState.size(); i++) {
        vector<char> v;

        for (int j = 0; j < gameState[i].size(); j++) {
            if (gameState[i][j]->getPiece() == nullptr) {
                v.push_back(' ');
            }
            else {
                v.push_back(gameState[i][j]->getPiece()->getSym());
            }
        }
        final.push_back(v);
    }
    return final;
}

int main() {
    vector<vector<Position*>> gameState = generateGameState(4, 5);
    gameState = generateConnections(gameState);

    if (validGameState(gameState)) {
        cout << "Its working!!!" << endl;
    }
    else {
        cout << "Not working" << endl;
    }

    Piece* piece_test = new Piece(1, 'x');
    vector<vector<char>> symbols = getSymbols(gameState);

    for (int i = 0; i < symbols.size(); i++) {
        for (int j = 0; j < symbols[i].size(); j++) {
            cout << "[" << symbols[i][j] << "] ";
        }
        cout << endl;
    }

    cout << "----------------------" << endl;

    gameState = place(piece_test, 3, 3, gameState);
    symbols = getSymbols(gameState);

    for (int i = 0; i < symbols.size(); i++) {
        for (int j = 0; j < symbols[i].size(); j++) {
            cout << "[" << symbols[i][j] << "] ";
        }
        cout << endl;
    }

    cout << "----------------------" << endl;

    if (!canPlace(3, 3, gameState)) {
        cout << "working" << endl;
    }
    else {
        cout << "not working" << endl;
    }

    cout << "----------------------" << endl;
    if (canMove(3, 3, 2, 3, gameState)) {
        cout << "working" << endl;
    }
    else {
        cout << "not Working" << endl;
    }
    cout << "----------------------" << endl;

    gameState = move(piece_test, 3, 2, gameState);
    symbols = getSymbols(gameState);

    for (int i = 0; i < symbols.size(); i++) {
        for (int j = 0; j < symbols[i].size(); j++) {
            cout << "[" << symbols[i][j] << "] ";
        }
        cout << endl;
    }

    cout << "----------------------" << endl;
    if (!canMove(3, 2, 3, 0, gameState)) {
        cout << "working" << endl;
    }
    else {
        cout << "not Working" << endl;
    }


    return 0;
}
