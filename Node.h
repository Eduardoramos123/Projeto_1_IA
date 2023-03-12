#ifndef PROJECT1_NODE_H
#define PROJECT1_NODE_H

#include "Piece.h"
#include "Position.h"
#include <vector>

class Node {
private:
    vector<vector<Position>> gameState;
    vector<Piece> ai_pieces;
    vector<Piece> player_pieces;
    int eval;
    Node* pai;
public:
    Node(vector<Piece> ai, vector<Piece> player, vector<vector<Position>> game);

    void setGameState(vector<vector<Position>> game);
    vector<vector<Position>> getGameState();
    void setAI(vector<Piece> ai);
    vector<Piece> getAI();
    void setPlayer(vector<Piece> player);
    vector<Piece> getPlayer();
    void setEval(int e);
    int getEval();
    void setPai(Node* node);
    Node* getPai();
};


#endif //PROJECT1_NODE_H
