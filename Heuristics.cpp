#include "Heuristics.h"

Heuristics::Heuristics(Game* g) {
    game = g;
}

/**
 * Calculates a heuristic score based on the number of game pieces that have only one neighbouring piece of the same type.
 * @param pieces: A vector of Piece objects representing the game pieces.
 * @param gameState: A vector of vector of Position objects representing the current state of the game.
 * @return An integer representing the number of game pieces that have only one neighbouring piece of the same type.
 */
int Heuristics::Heuristics::heuristic_1_piece_near(vector<Piece> pieces, vector<vector<Position>> gameState) {
    int res = 0;

    for (auto piece : pieces) {
        Position position = gameState[piece.getLevel()][piece.getPos()];
        vector<Position> neighbours = position.getNeighbours();

        int check = 0;
        for (auto & neighbour : neighbours) {
            if (neighbour.getPiece().getSym() == ' ') {
                continue;
            }
            if (neighbour.getPiece().getSym() == piece.getSym()) {
                check = 0;
                break;
            }
            check++;
        }

        if (check == 1) {
            res++;
        }
    }
    return res;
}

/**
 * Calculates a heuristic score based on the number of game pieces that have exactly two neighbouring pieces.
 * @param pieces: A vector of Piece objects representing the game pieces.
 * @param gameState: A vector of vector of Position objects representing the current state of the game.
 * @return An integer representing the number of game pieces that have exactly two neighbouring pieces.
 */
int Heuristics::heuristic_2_pieces_near(vector<Piece> pieces, vector<vector<Position>> gameState) {
    int res = 0;

    for (auto piece : pieces) {
        Position position = gameState[piece.getLevel()][piece.getPos()];
        vector<Position> neighbours = position.getNeighbours();

        int check = 0;
        for (auto & neighbour : neighbours) {
            if (neighbour.getPiece().getSym() == ' ') {
                continue;
            }
            check++;
        }

        if (check == 2) {
            res++;
        }
    }
    return res;
}

/**
 * Calculates a heuristic score based on the number of game pieces that have only one neighbouring piece of the same type and the number of game pieces that have exactly two neighbouring pieces.
 * @param pieces: A vector of Piece objects representing the game pieces.
 * @param gameState: A vector of vector of Position objects representing the current state of the game.
 * @return An integer representing the difference between five times the number of game pieces with only one neighbouring piece of the same type and three times the number of game pieces with exactly two neighbouring pieces.
 */
int Heuristics::heuristic_3_test(vector<Piece> pieces, vector<vector<Position>> gameState) {
    int res1 = 0;
    int res2 = 0;

    for (auto piece : pieces) {
        Position position = gameState[piece.getLevel()][piece.getPos()];
        vector<Position> neighbours = position.getNeighbours();

        int check1 = 0;
        int check2 = 0;
        for (auto & neighbour : neighbours) {
            if (neighbour.getPiece().getSym() == ' ') {
                continue;
            }
            if (neighbour.getPiece().getSym() == piece.getSym()) {
                check1 = -10000;
            }
            check1++;
            check2++;
        }

        if (check1 == 1) {
            res1++;
        }
        if (check2 == 2) {
            res2++;
        }
    }

    return 5 * res1 - 3 * res2;
}

/**
 * Calculates a heuristic score based on the number of game pieces that have at least one neighbouring piece of the same type and the number of game pieces that have at least one neighbouring piece of a different type.
 * @param pieces: A vector of Piece objects representing the game pieces.
 * @param gameState: A vector of vector of Position objects representing the current state of the game.
 * @return An integer representing the difference between the number of game pieces with at least one neighbouring piece of the same type and the number of game pieces with at least one neighbouring piece of a different type.
 */
int Heuristics::heuristic_4_variety_levels(vector<Piece> pieces, vector<vector<Position>> gameState) {
    int res1 = 0;
    int res2 = 0;

    for (auto piece : pieces) {
        Position position = gameState[piece.getLevel()][piece.getPos()];
        vector<Position> neighbours = position.getNeighbours();

        for (auto & neighbour : neighbours) {
            if (neighbour.getPiece().getSym() == ' ') {
                continue;
            }
            if (neighbour.getPiece().getSym() == piece.getSym()) {
                res1++;
                break;
            }
            else {
                res2++;
                break;
            }
        }
    }

    return res1 - res2;
}

/**
*This function calculates the number of positions that have more than one empty neighbour.
*
*@param pieces A vector containing all the pieces on the board.
*@param gameState A vector of vectors representing the current state of the game.
*@return An integer representing the number of positions with more than one empty neighbour.
*/
int Heuristics::heuristic_5_neighbours(vector<Piece> pieces, vector<vector<Position>> gameState) {
    vector<vector<int>> check;

    for (int i = 0; i < gameState.size(); i++) {
        vector<int> v;
        for (int j = 0; j < gameState[i].size(); j++) {
            v.push_back(0);
        }
        check.push_back(v);
    }

    for (auto piece : pieces) {
        Position position = gameState[piece.getLevel()][piece.getPos()];
        vector<Position> neighbours = position.getNeighbours();

        for (auto & neighbour : neighbours) {
            if (neighbour.getPiece().getSym() == ' ') {
                check[neighbour.getLevel()][neighbour.getPos()] = check[neighbour.getLevel()][neighbour.getPos()] + 1;
            }
        }
    }

    int res = 0;
    for (int i = 0; i < check.size(); i++) {
        for (int j = 0; j < check[i].size(); j++) {
            if (check[i][j] > 1) {
                res++;
            }
        }

    }

    return res;
}

/**
 * Calculates the "hunt" heuristic for a given board state and set of pieces.
 * The heuristic counts the number of empty neighbor positions for each piece and returns the smallest count.
 *
 * @param pieces A vector containing the pieces to be evaluated.
 * @param gameState A 2D vector representing the current state of the game board.
 * @return An integer representing the heuristic value for the given state and set of pieces.
 */
int Heuristics::heuristic_6_hunt(vector<Piece> pieces, vector<vector<Position>> gameState) {
    int res = 3;

    for (auto piece : pieces) {
        Position position = gameState[piece.getLevel()][piece.getPos()];
        vector<Position> neighbours = position.getNeighbours();

        int check = 0;
        for (auto & neighbour : neighbours) {
            if (neighbour.getPiece().getSym() == ' ') {
                check++;
            }
        }

        if (check < res) {
            res = check;
        }
    }

    return res;
}

/**
 * Checks if any of the pieces are stuck and cannot make a legal move.
 *
 * @param pieces: vector of all the pieces on the board
 * @param gameState: 2D vector representing the current state of the game
 * @return: true if any of the pieces are stuck, false otherwise
 */
bool Heuristics::heuristic_stuck(vector<Piece> pieces, vector<vector<Position>> gameState) {
    for (auto piece : pieces) {
        if (game->isStuck(gameState, piece)) {
            return true;
        }
    }
    return false;
}

/**
 * Calculates the "liberty" heuristic for a given board state.
 *
 * @param pieces      a vector of Piece objects representing the pieces on the board
 * @param gameState   a vector of vectors of Position objects representing the current state of the board
 *
 * @return            an integer representing the "liberty" heuristic value for the given board state
 */
int Heuristics::heuristic_liberty(vector<Piece> pieces, vector<vector<Position>> gameState) {
    int res = 0;
    int i = 0;

    for (auto piece : pieces) {
        Position position = gameState[piece.getLevel()][piece.getPos()];
        vector<Position> neighbours = position.getNeighbours();
        for (auto & neighbour : neighbours) {
            if (neighbour.getPiece().getSym() == ' ') {
                vector<vector<Position>> check = gameState;
                vector<Piece> p = pieces;
                check = game->move(p[i], neighbour.getLevel(), neighbour.getPos(), check);
                p[i].setCoords(neighbour.getLevel(), neighbour.getPos());
                if (!heuristic_stuck(p, check)) {
                    res++;
                }
            }
        }
        i++;
    }

    return res;
}

/**
 * heuristic_vulnerable calculates the number of pieces that have only two neighbours, which makes them vulnerable to capture
 *
 * @param pieces: vector of pieces representing the current state of the game
 * @param gameState: vector of vectors representing the positions of the pieces in the game board
 * @return: an integer representing the number of pieces that have only two neighbours
*/
int Heuristics::heuristic_vulnerable(vector<Piece> pieces, vector<vector<Position>> gameState) {
    int res = 0;

    for (auto piece : pieces) {
        Position position = gameState[piece.getLevel()][piece.getPos()];
        vector<Position> neighbours = position.getNeighbours();

        int check = 0;
        for (auto & neighbour : neighbours) {
            if (neighbour.getPiece().getSym() == ' ') {
                continue;
            }
            check++;
        }

        if (check == 2) {
            res++;
        }
    }
    return res;
}

/**
 * Check if the opponent is about to win by checking if any of their pieces
 * can make a move to an empty space that would lead them to win the game.
 *
 * @param pieces1 a vector of the current player's pieces
 * @param pieces2 a vector of the opponent's pieces
 * @param gameState a vector of vectors representing the current game state
 * @return true if the opponent is about to win, false otherwise
*/
bool Heuristics::about_to_win(vector<Piece> pieces1, vector<Piece> pieces2, vector<vector<Position>> gameState) {
    for (auto i : pieces2) {
        vector<Position> neighbours = gameState[i.getLevel()][i.getPos()].getNeighbours();

        for (auto neighbour : neighbours) {
            vector<vector<Position>> tester = gameState;

            if (!game->canMove(i.getLevel(), i.getPos(), neighbour.getLevel(), neighbour.getPos(), tester)) {
                continue;
            }

            tester = game->move(i, neighbour.getLevel(), neighbour.getPos(), tester);


            if (heuristic_stuck(pieces1, tester)) {
                return true;
            }
        }
    }

    return false;
}

/**
 * Returns the number of pieces that are on levels other than the top or bottom levels, indicating control of the central area of the board.
 *
 * @param pieces: a vector of Piece objects representing the pieces of the player.
 * @param gameState: a vector of vector of Position objects representing the current state of the game board.
 * @return an integer representing the number of pieces controlled by the player in the central area of the board.
*/
int Heuristics::control_center(vector<Piece> pieces, vector<vector<Position>> gameState) {
    int res = 0;

    for (auto piece : pieces) {
        if (piece.getLevel() > 0 && piece.getLevel() < gameState.size() - 1) {
            res++;
        }
    }
    return res;
}

/**
 * Returns the number of pieces that don't have allied pieces adjacent to them.
 *
 * @param pieces     A vector of all the pieces on the board.
 * @param gameState  The current state of the game.
 * @return           The number of pieces that don't have allied pieces adjacent to them.
 */
int Heuristics::heuristic_no_allied_pieces_near(vector<Piece> pieces, vector<vector<Position>> gameState) {
    int res = 0;
    for (auto i : pieces) {
        vector<Position> neighbours = gameState[i.getLevel()][i.getPos()].getNeighbours();

        for (auto & neighbour : neighbours) {
            if (neighbour.getPiece().getSym() == pieces[0].getSym()) {
                res++;
            }
        }
    }
    return res;
}

/**
 * Calculates the heuristic value for the number of level transitions of the pieces.
 *
 * @param pieces A vector of Piece objects representing the player's pieces.
 * @param gameState A vector of vectors of Position objects representing the game board.
 * @return An integer representing the heuristic value for the number of level transitions of the pieces.
 */
int Heuristics::heuristic_level_trans(vector<Piece> pieces, vector<vector<Position>> gameState) {
    int res = 0;

    for (auto piece : pieces) {
        Position position = gameState[piece.getLevel()][piece.getPos()];
        vector<Position> neighbours = position.getNeighbours();

        int check = 0;
        for (auto & neighbour : neighbours) {
            if (neighbour.getPiece().getSym() == ' ' && neighbour.getLevel() != piece.getLevel()) {
                res++;
            }
        }
    }
    return res;
}

/**
 * This function calculates the heuristic value of a given game state for a player based on the positions of their pieces.
 *
 * @param pieces1: A vector of Piece objects representing the pieces of player 1.
 * @param pieces2: A vector of Piece objects representing the pieces of player 2.
 * @param gameState: A vector of vector of Position objects representing the current positions of all pieces on the board.
 * @return An integer value representing the heuristic value of the game state for player 1.
*/
int Heuristics::aval_AI(vector<Piece> pieces1, vector<Piece> pieces2, vector<vector<Position>> gameState) {
    int res = 0;
    if (heuristic_stuck(pieces1, gameState)) {
        return -1000;
    }

    if (heuristic_stuck(pieces2, gameState)) {
        return 1000;
    }

    if (about_to_win(pieces1, pieces2, gameState)) {
        return -1000;
    }


    if (about_to_win(pieces2, pieces1, gameState)) {
        res+= 500;
    }



    res+=  4*(heuristic_level_trans(pieces1, gameState) - heuristic_level_trans(pieces2, gameState));
    res += 8*(heuristic_liberty(pieces1, gameState) - heuristic_liberty(pieces2, gameState));
    //res += 5*heuristic_vulnerable(pieces2, gameState);
    return res;
}

/**
 * This function calculates the heuristic value of a given game state for a player based on the positions of their pieces.
 *
 * @param pieces1: A vector of Piece objects representing the pieces of player 1.
 * @param pieces2: A vector of Piece objects representing the pieces of player 2.
 * @param gameState: A vector of vector of Position objects representing the current positions of all pieces on the board.
 * @return An integer value representing the heuristic value of the game state for player 1.
*/
int Heuristics::aval_Player(vector<Piece> pieces1, vector<Piece> pieces2, vector<vector<Position>> gameState) {
    int res = 0;
    if (heuristic_stuck(pieces1, gameState)) {
        return 1000;
    }

    if (heuristic_stuck(pieces2, gameState)) {
        return -1000;
    }

    if (about_to_win(pieces1, pieces2, gameState)) {
        return 1000;
    }


    if (about_to_win(pieces2, pieces1, gameState)) {
        res+= -500;
    }



    res+= -4*(heuristic_level_trans(pieces1, gameState) - heuristic_level_trans(pieces2, gameState));
    res += -8*(heuristic_liberty(pieces1, gameState) - heuristic_liberty(pieces2, gameState));
    //res += -5*heuristic_vulnerable(pieces2, gameState);
    return res;
}
