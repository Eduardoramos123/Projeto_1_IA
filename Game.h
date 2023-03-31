#ifndef PROJETO_1_IA_GAME_H
#define PROJETO_1_IA_GAME_H

#include "Node.h"
#include "Position.h"
#include "Piece.h"

class Game {
public:
    Game();

    bool canMove(int level1, int pos1, int level2, int pos2, vector<vector<Position>> gameState);
    vector<vector<Position>> move(Piece piece, int level, int pos, vector<vector<Position>> gameState);
    bool isStuck(vector<vector<Position>> gameState, Piece piece);
};


#endif //PROJETO_1_IA_GAME_H
