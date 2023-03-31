#include "Heuristics.h"

Heuristics::Heuristics(Game* g) {
    game = g;
}

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

bool Heuristics::heuristic_stuck(vector<Piece> pieces, vector<vector<Position>> gameState) {
    for (auto piece : pieces) {
        if (game->isStuck(gameState, piece)) {
            return true;
        }
    }
    return false;
}

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

int Heuristics::control_center(vector<Piece> pieces, vector<vector<Position>> gameState) {
    int res = 0;

    for (auto piece : pieces) {
        if (piece.getLevel() > 0 && piece.getLevel() < gameState.size() - 1) {
            res++;
        }
    }
    return res;
}

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
