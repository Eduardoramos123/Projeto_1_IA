#include "Game.h"

Game::Game() {}

/**
 * This function checks whether a piece can be moved from a given position to another position in a given game state.
 *
 * @param level1: An integer representing the level of the initial position of the piece.
 * @param pos1: An integer representing the position of the initial position of the piece.
 * @param level2: An integer representing the level of the destination position of the piece.
 * @param pos2: An integer representing the position of the destination position of the piece.
 * @param gameState: A vector of vector of Position objects representing the current positions of all pieces on the board.

 * @return A boolean value representing whether the piece can be moved to the destination position in the given game state.
*/
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

/**
 * This function moves a given piece to a new position on the board and returns the resulting game state.
 *
 * @param piece: A Piece object representing the piece to be moved.
 * @param level: An integer representing the level of the new position of the piece.
 * @param pos: An integer representing the position of the new position of the piece.
 * @param gameState: A vector of vector of Position objects representing the current positions of all pieces on the board.
 *
 * @return A vector of vector of Position objects representing the new positions of all pieces on the board after the given piece has been moved to the new position.
*/
vector<vector<Position>> Game::move(Piece piece, int level, int pos, vector<vector<Position>> gameState) {
    vector<vector<Position>> final = gameState;

    Piece blank = Piece();

    final[piece.getLevel()][piece.getPos()].setPiece(blank);
    piece.setCoords(level, pos);
    final[level][pos].setPiece(piece);

    return final;
}

/**
 * This function checks whether a given piece is stuck, i.e. cannot be moved to any neighboring position on the board.
 *
 * @param gameState: A vector of vector of Position objects representing the current positions of all pieces on the board.
 * @param piece: A Piece object representing the piece to be checked.
 *
 * @return A boolean value representing whether the given piece is stuck or not.
*/
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