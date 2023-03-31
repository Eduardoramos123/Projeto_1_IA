#include "Game.h"

Game::Game() {}

bool Game::canMove(int level1, int pos1, int level2, int pos2, vector<vector<Position>> gameState) {
    Position initial = gameState[level1][pos1];
    vector<Position> neighbours = initial.getNeighbours();

    for (const auto & neighbour : neighbours) {
        int check_pos = neighbour.getPos();
        int check_level = neighbour.getLevel();

        if (check_level == level2 && check_pos == pos2 && gameState[check_level][check_pos].getPiece().getSym() == ' ') {
            return true;
        }
    }
    return false;
}

vector<vector<Position>> Game::move(Piece piece, int level, int pos, vector<vector<Position>> gameState) {
    vector<vector<Position>> final = gameState;

    Piece blank = Piece();

    final[piece.getLevel()][piece.getPos()].setPiece(blank);
    piece.setCoords(level, pos);
    final[level][pos].setPiece(piece);

    return final;
}

bool Game::isStuck(vector<vector<Position>> gameState, Piece piece) {
    Position initial = gameState[piece.getLevel()][piece.getPos()];
    vector<Position> neighbours = initial.getNeighbours();

    for (const auto & neighbour : neighbours) {
        int check_pos = neighbour.getPos();
        int check_level = neighbour.getLevel();

        if (canMove(piece.getLevel(), piece.getPos(), check_level, check_pos, gameState)) {
            return false;
        }
    }
    return true;
}