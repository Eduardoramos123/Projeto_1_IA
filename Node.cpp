#include "Node.h"

Node::Node(vector<Piece> ai, vector<Piece> player, vector<vector<Position>> game) {
    ai_pieces = ai;
    player_pieces = player;
    gameState = game;
}

void Node::setGameState(vector<vector<Position>> game) {
    gameState = game;
}

vector<vector<Position>> Node::getGameState() {
    return gameState;
}

void Node::setAI(vector<Piece> ai) {
    ai_pieces = ai;
}

vector<Piece> Node::getAI() {
    return ai_pieces;
}

void Node::setPlayer(vector<Piece> player) {
    player_pieces = player;
}

vector<Piece> Node::getPlayer() {
    return player_pieces;
}

void Node::setEval(int e) {
    eval = e;
}

int Node::getEval() {
    return eval;
}

void Node::setPai(Node *node) {
    pai = node;
}

Node *Node::getPai() {
    return pai;
}