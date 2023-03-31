#ifndef PROJETO_1_IA_HEURISTICS_H
#define PROJETO_1_IA_HEURISTICS_H

#include "Game.h"
#include "Node.h"
#include "Position.h"
#include "Piece.h"


class Heuristics {
private:
    Game* game;
public:
    Heuristics(Game* g);

    int heuristic_1_piece_near(vector<Piece> pieces, vector<vector<Position>> gameState);
    int heuristic_2_pieces_near(vector<Piece> pieces, vector<vector<Position>> gameState);
    int heuristic_3_test(vector<Piece> pieces, vector<vector<Position>> gameState);
    int heuristic_4_variety_levels(vector<Piece> pieces, vector<vector<Position>> gameState);
    int heuristic_5_neighbours(vector<Piece> pieces, vector<vector<Position>> gameState);
    int heuristic_6_hunt(vector<Piece> pieces, vector<vector<Position>> gameState);

    bool heuristic_stuck(vector<Piece> pieces, vector<vector<Position>> gameState);
    int heuristic_liberty(vector<Piece> pieces, vector<vector<Position>> gameState);
    int heuristic_vulnerable(vector<Piece> pieces, vector<vector<Position>> gameState);
    bool about_to_win(vector<Piece> pieces1, vector<Piece> pieces2, vector<vector<Position>> gameState);
    int control_center(vector<Piece> pieces, vector<vector<Position>> gameState);
    int heuristic_no_allied_pieces_near(vector<Piece> pieces, vector<vector<Position>> gameState);
    int heuristic_level_trans(vector<Piece> pieces, vector<vector<Position>> gameState);

    int aval_AI(vector<Piece> pieces1, vector<Piece> pieces2, vector<vector<Position>> gameState);
    int aval_Player(vector<Piece> pieces1, vector<Piece> pieces2, vector<vector<Position>> gameState);
};


#endif //PROJETO_1_IA_HEURISTICS_H
