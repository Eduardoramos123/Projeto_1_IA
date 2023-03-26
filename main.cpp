#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <stack>
#include<cstdlib>
#include <ctime>

#include "Node.h"
#include "Position.h"
#include "Piece.h"

#include <Python.h>
#include <limits>
#include <sstream>


using namespace std;

vector<vector<Position>> generateGameState(int level, int pos) {
    vector<vector<Position>> gameState;

    for (int i = 0; i < level; i++) {
        vector<Position> v;
        for (int j = 0; j < pos; j++) {
            Position p = Position(i, j);
            Piece piece = Piece();
            p.setPiece(piece);
            v.push_back(p);
        }
        gameState.push_back(v);
    }

    return gameState;
}

vector<vector<Position>> generateConnections(vector<vector<Position>> gameState) {
    vector<vector<Position>> final = gameState;

    for (int i = 0; i < gameState.size(); i++) {
        for (int j = 0; j < gameState[i].size(); j++) {
            if (i == gameState.size() - 1) {
                if (j == 0) {
                    final[i][j].addNeighbour(final[i][j + 1]);
                    final[i][j].addNeighbour(final[i][gameState[i].size() - 1]);
                }
                else if (j == (gameState[i].size() - 1)) {
                    final[i][j].addNeighbour(final[i][0]);
                    final[i][j].addNeighbour(final[i][j - 1]);
                }
                else {
                    final[i][j].addNeighbour(final[i][j + 1]);
                    final[i][j].addNeighbour(final[i][j - 1]);
                }
            }
            else if (i == 0) {
                final[i][j].addNeighbour(final[i + 1][j]);
                final[i + 1][j].addNeighbour(final[i][j]);
                if (j == 0) {
                    final[i][j].addNeighbour(final[i][j + 1]);
                    final[i][j].addNeighbour(final[i][gameState[i].size() - 1]);
                }
                else if (j == (gameState[i].size() - 1)) {
                    final[i][j].addNeighbour(final[i][0]);
                    final[i][j].addNeighbour(final[i][j - 1]);
                }
                else {
                    final[i][j].addNeighbour(final[i][j + 1]);
                    final[i][j].addNeighbour(final[i][j - 1]);
                }
            }
            else if (i % 2 == 0) {
                final[i][j].addNeighbour(final[i + 1][j]);
                final[i + 1][j].addNeighbour(final[i][j]);
            }
            else if (i % 2 != 0) {
                if (j == 0) {
                    final[i][j].addNeighbour(final[i + 1][j + 1]);
                    final[i][j].addNeighbour(final[i + 1][0]);

                    final[i + 1][j + 1].addNeighbour(final[i][j]);
                    final[i + 1][0].addNeighbour(final[i][j]);
                }
                else if (j == (gameState[i].size() - 1)) {
                    final[i][j].addNeighbour(final[i + 1][0]);
                    final[i][j].addNeighbour(final[i + 1][j]);

                    final[i + 1][0].addNeighbour(final[i][j]);
                    final[i + 1][j].addNeighbour(final[i][j]);
                }
                else {
                    final[i][j].addNeighbour(final[i + 1][j + 1]);
                    final[i][j].addNeighbour(final[i + 1][j]);

                    final[i + 1][j + 1].addNeighbour(final[i][j]);
                    final[i + 1][j].addNeighbour(final[i][j]);
                }
            }
        }
    }
    return final;
}

bool validGameState(vector<vector<Position>> gameState) {
    for (auto & i : gameState) {
        for (auto & j : i) {
            if (j.getNeighbours().size() != 3) {
                return false;
            }
        }
    }
    return true;
}

bool canMove(int level1, int pos1, int level2, int pos2, vector<vector<Position>> gameState) {
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

bool isStuck(vector<vector<Position>> gameState, Piece piece) {
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

vector<vector<Position>> move(Piece piece, int level, int pos, vector<vector<Position>> gameState) {
    vector<vector<Position>> final = gameState;

    Piece blank = Piece();

    final[piece.getLevel()][piece.getPos()].setPiece(blank);
    piece.setCoords(level, pos);
    final[level][pos].setPiece(piece);

    return final;
}

bool canPlace(int level, int pos, vector<vector<Position>> gameState) {
    if (gameState[level][pos].getPiece().getSym() != ' ') {
        return false;
    }
    return true;
}

vector<vector<Position>> place(Piece& piece, int level, int pos, vector<vector<Position>> gameState) {
    vector<vector<Position>> final = gameState;

    piece.setCoords(level, pos);
    final[level][pos].setPiece(piece);
    return final;
}

vector<vector<char>> getSymbols(vector<vector<Position>> gameState) {
    vector<vector<char>> final;

    for (auto & i : gameState) {
        vector<char> v;

        for (int j = 0; j < i.size(); j++) {
            v.push_back(i[j].getPiece().getSym());
        }
        final.push_back(v);
    }
    return final;
}

void printGameState(vector<vector<Position>> gameState) {

    vector<vector<char>> symbols = getSymbols(gameState);

    cout << "-----------------[" << symbols[0][0] << "]-------------------" << endl
         << "|                                     |" << endl
         << "|    ------------[" << symbols[1][0] << "]-----------       |" << endl
         << "|    |                        |       |" << endl
         << "[" << symbols[0][4] << "]  |    --[" << symbols[2][0] << "]------[" << symbols[2][1] << "]--    |       [" << symbols[0][1] << "]" << endl
         << "|    |    |              |    |       |" << endl
         << "|    [" << symbols[1][4] << "]  |    [" << symbols[3][0] << "]--[" << symbols[3][1] << "]  |    [" << symbols[1][1] << "]     |" << endl
         << "|    |    |    [" << symbols[3][4] << "]  [" << symbols[3][2] << "]  |    |       |" << endl
         << "|    |    [" << symbols[2][4] << "]  ---[" << symbols[3][3] << "]--  [" << symbols[2][2] << "]  |       |" << endl
         << "|    |    |              |    |       |" << endl
         << "|    |    -------[" << symbols[2][3] << "]------    |       |" << endl
         << "|    |                        |       |" << endl
         << "|    ----[" << symbols[1][3] << "]------------[" << symbols[1][2] << "]----       |" << endl
         << "|                                     |" << endl
         << "-------[" << symbols[0][3] << "]-------------------[" << symbols[0][2] <<"]-------" << endl;
}

vector<vector<Position>> playerPlacingPhase(vector<Piece>& player_pieces, vector<Piece>& adv_pieces, vector<vector<Position>> gameState) {

    vector<vector<Position>> final = gameState;

    int inc;

    if (gameState[0].size() % 2 != 0) {
        inc = 1 + (gameState[0].size() / 2);
    }
    else {
        inc = (gameState[0].size() / 2);
    }


    for (int i = 0; i < player_pieces.size(); i++) {
        bool flag = true;

        while (flag) {

            cout << "Place Piece number " << player_pieces[i].getId() << endl;
            int pos;
            cout << "Pos: ";
            cin >> pos;

            if (canPlace(0, pos, final)) {
                flag = false;

                int n_pos = (inc + pos) % gameState[0].size();

                final = place(player_pieces[i], 0, pos, final);
                final = place(adv_pieces[i], gameState.size() - 1, n_pos, final);
            }
        }
    }

    return final;
}

vector<vector<Position>> randomPlacingPhase(vector<Piece>& player_pieces, vector<Piece>& adv_pieces, vector<vector<Position>> gameState) {
    vector<vector<Position>> final = gameState;
    int inc;

    if (gameState[0].size() % 2 != 0) {
        inc = 1 + (gameState[0].size() / 2);
    }
    else {
        inc = (gameState[0].size() / 2);
    }

    for (int i = 0; i < player_pieces.size(); i++) {
        bool flag = true;
        srand(time(0));


        while (flag) {

            int pos;


            pos = rand() % final[0].size();

            if (canPlace(0, pos, final)) {
                flag = false;

                int n_pos = (inc + pos) % gameState[0].size();

                final = place(player_pieces[i], 0, pos, final);
                final = place(adv_pieces[i], gameState.size() - 1, n_pos, final);
            }
        }
    }

    return final;
}

int heuristic_1_piece_near(vector<Piece> pieces, vector<vector<Position>> gameState) {
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

int heuristic_2_pieces_near(vector<Piece> pieces, vector<vector<Position>> gameState) {
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

int heuristic_3_test(vector<Piece> pieces, vector<vector<Position>> gameState) {
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

int heuristic_4_variety_levels(vector<Piece> pieces, vector<vector<Position>> gameState) {
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

int heuristic_5_neighbours(vector<Piece> pieces, vector<vector<Position>> gameState) {
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

int heuristic_6_hunt(vector<Piece> pieces, vector<vector<Position>> gameState) {
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

bool heuristic_stuck(vector<Piece> pieces, vector<vector<Position>> gameState) {
    for (auto piece : pieces) {
        if (isStuck(gameState, piece)) {
            return true;
        }
    }
    return false;
}

int heuristic_liberty(vector<Piece> pieces, vector<vector<Position>> gameState) {
    int res = 0;
    int i = 0;

    for (auto piece : pieces) {
        Position position = gameState[piece.getLevel()][piece.getPos()];
        vector<Position> neighbours = position.getNeighbours();
        for (auto & neighbour : neighbours) {
            if (neighbour.getPiece().getSym() == ' ') {
                vector<vector<Position>> check = gameState;
                vector<Piece> p = pieces;
                check = move(p[i], neighbour.getLevel(), neighbour.getPos(), check);
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

int heuristic_vulnerable(vector<Piece> pieces, vector<vector<Position>> gameState) {
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

bool about_to_win(vector<Piece> pieces1, vector<Piece> pieces2, vector<vector<Position>> gameState) {
    for (auto i : pieces2) {
        vector<Position> neighbours = gameState[i.getLevel()][i.getPos()].getNeighbours();

        for (auto neighbour : neighbours) {
            vector<vector<Position>> tester = gameState;

            if (!canMove(i.getLevel(), i.getPos(), neighbour.getLevel(), neighbour.getPos(), tester)) {
                continue;
            }

            tester = move(i, neighbour.getLevel(), neighbour.getPos(), tester);


            if (heuristic_stuck(pieces1, tester)) {
                return true;
            }
        }
    }

    return false;
}

int control_center(vector<Piece> pieces, vector<vector<Position>> gameState) {
    int res = 0;

    for (auto piece : pieces) {
        if (piece.getLevel() > 0 && piece.getLevel() < gameState.size() - 1) {
            res++;
        }
    }
    return res;
}

int heuristic_no_allied_pieces_near(vector<Piece> pieces, vector<vector<Position>> gameState) {
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

int heuristic_level_trans(vector<Piece> pieces, vector<vector<Position>> gameState) {
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

int aval_AI(vector<Piece> pieces1, vector<Piece> pieces2, vector<vector<Position>> gameState) {
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

int aval_Player(vector<Piece> pieces1, vector<Piece> pieces2, vector<vector<Position>> gameState) {
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

vector<char> convertGameSate(vector<vector<Position>> gameState) {
    vector<char> res;

    for (int i = 0; i < gameState.size(); i++) {
        for (int j = 0; j < gameState[i].size(); j++) {
            res.push_back(gameState[i][j].getPiece().getSym());
        }
    }
    return res;
}

bool isVisited(vector<vector<char>> visited, vector<vector<Position>> gameState) {
    vector<char> charState = convertGameSate(gameState);

    for (int i = 0; i < visited.size(); i++) {
        if (visited[i] == charState) {
            return true;
        }
    }

    return false;
}

Node* minimax(Node* node, int depth, int maxDepth, bool AI, int alpha, int beta, vector<vector<char>> visited) {
    if (depth == maxDepth || heuristic_stuck(node->getAI(), node->getGameState()) || heuristic_stuck(node->getPlayer(), node->getGameState())) {
        return node;
    }

    if (AI) {
        Node* best = new Node({}, {}, {});
        best->setEval(-1000000);
        Node* new_node;
        vector<vector<Position>> gameState = node->getGameState();
        vector<Piece> pieces1 = node->getAI();

        for (int i = 0; i < pieces1.size(); i++) {
            vector<Position> neighbours = gameState[pieces1[i].getLevel()][pieces1[i].getPos()].getNeighbours();

            for (const auto & neighbour : neighbours) {
                Piece p = pieces1[i];
                vector<vector<Position>> tester = gameState;

                if (!canMove(p.getLevel(), p.getPos(), neighbour.getLevel(), neighbour.getPos(), tester)) {
                    continue;
                }

                tester = move(p, neighbour.getLevel(), neighbour.getPos(), tester);

                if (isVisited(visited, tester)) {
                    continue;
                }
                visited.push_back(convertGameSate(tester));

                vector<Piece> piece_tester = pieces1;
                piece_tester[i].setCoords(neighbour.getLevel(), neighbour.getPos());

                new_node = new Node(piece_tester, node->getPlayer(), tester);
                new_node->setPai(node);

                Node* challenger = minimax(new_node, depth+1, maxDepth, false, alpha, beta, visited);
                challenger->setEval(aval_AI(challenger->getAI(), challenger->getPlayer(), challenger->getGameState()));
                if (challenger->getEval() > best->getEval()) {
                    best = challenger;
                    best->setPai(new_node);
                }
                if (best->getEval() > alpha) {
                    alpha = best->getEval();
                }

                if (beta <= alpha) {
                    break;
                }

            }

            if (beta <= alpha) {
                break;
            }

        }
        return best->getPai();
    }
    else {
        Node* best = new Node({}, {}, {});
        best->setEval(1000000);
        Node* new_node;
        vector<vector<Position>> gameState = node->getGameState();
        vector<Piece> pieces2 = node->getPlayer();

        for (int i = 0; i < pieces2.size(); i++) {
            vector<Position> neighbours = gameState[pieces2[i].getLevel()][pieces2[i].getPos()].getNeighbours();

            for (const auto & neighbour : neighbours) {
                Piece p = pieces2[i];
                vector<vector<Position>> tester = gameState;

                if (!canMove(p.getLevel(), p.getPos(), neighbour.getLevel(), neighbour.getPos(), tester)) {
                    continue;
                }

                tester = move(p, neighbour.getLevel(), neighbour.getPos(), tester);

                if (isVisited(visited, tester)) {
                    continue;
                }
                visited.push_back(convertGameSate(tester));

                vector<Piece> piece_tester = pieces2;
                piece_tester[i].setCoords(neighbour.getLevel(), neighbour.getPos());

                new_node = new Node(node->getAI(), piece_tester, tester);
                new_node->setPai(node);

                Node* challenger = minimax(new_node, depth+1, maxDepth, true, alpha, beta, visited);
                challenger->setEval(aval_Player(challenger->getPlayer(), challenger->getAI(), challenger->getGameState()));
                if (challenger->getEval() < best->getEval()) {
                    best = challenger;
                    best->setPai(new_node);
                }
                if (best->getEval() < beta) {
                    beta = best->getEval();
                }

                if (beta <= alpha) {
                    break;
                }

            }

            if (beta <= alpha) {
                break;
            }

        }
        return best->getPai();

    }

}

int switch_difficulty(int difficulty) {
    switch(difficulty) {
        case 1:
            return 2;
        case 2:
            return 3;
        case 3:
            return 4;
        default:
            return -1;
    }
}

vector<vector<Position>> choose_piece_to_move(int turn, int& level, int& pos, vector<vector<Position>> gameState) {
    char p;
    if (turn)
        p = 'x';
    else
        p = 'o';

    int lin, col;

    // Ask the user to enter the row and column of the piece to move
    while(true) {
        cout << "Player " << turn << ", enter the row and column of the piece you want to move (lin and col -> [0.." << gameState.size()-1 << "] e.g. 1 2):";
        cin >> lin >> col;

        // If no piece was found, ask the user to try again
        if(gameState[lin][col].getPiece().getSym() != p) {
            cout << "Piece not found. Please try again." << endl << endl;
            continue;
        }

        cout << "To which position? (lin and col -> [0.." << gameState.size()-1 << "] e.g. 1 2):";
        cin >> level >> pos;

        if(canMove(lin, col, level, pos, gameState))
            break;
    }

    return move(gameState[lin][col].getPiece(), level, pos, gameState);
}

void p_vs_p_gameloop(Node* node) {
    printGameState(node->getGameState());
    int turn = 1;

    while (true) {
        if (turn) {
            cout << endl << "Player 1"<<endl;

            // player move
            int level, pos;
            vector<vector<Position>> newGameState = choose_piece_to_move(turn, level, pos, node->getGameState());
            node->setGameState(newGameState);

            vector<Piece> newPieces;
            for(Piece p: node->getAI()) {
                if(node->getGameState()[p.getLevel()][p.getPos()].getPiece().getSym() != p.getSym()) {
                    p.setCoords(level, pos);
                }
                newPieces.push_back(p);
            }
            node->setAI(newPieces);

            printGameState(node->getGameState());

            if (heuristic_stuck(node->getAI(), node->getGameState())) {
                cout << "Player 2 WON!" << endl;
                break;
            }
            if (heuristic_stuck(node->getPlayer(), node->getGameState())) {
                cout << "Player 1 WON!" << endl;
                break;
            }

            turn = 0;
        }
        else {
            cout << endl << "Player 2"<<endl;

            // player move
            int level, pos;
            vector<vector<Position>> newGameState = choose_piece_to_move(turn, level, pos, node->getGameState());
            node->setGameState(newGameState);

            vector<Piece> newPieces;
            for(Piece p: node->getPlayer()) {
                if(node->getGameState()[p.getLevel()][p.getPos()].getPiece().getSym() != p.getSym()) {
                    p.setCoords(level, pos);
                }
                newPieces.push_back(p);
            }
            node->setPlayer(newPieces);

            printGameState(node->getGameState());
            // Call the draw_board function
            //PyObject* result = PyObject_CallObject(draw_board_func, NULL);

            if (heuristic_stuck(node->getAI(), node->getGameState())) {
                cout << "Player 2 WON!" << endl;
                break;
            }
            if (heuristic_stuck(node->getPlayer(), node->getGameState())) {
                cout << "Player 1 WON!" << endl;
                break;
            }

            turn = 1;
        }
    }
}

void p_vs_bot_gameloop(Node* node, int depth, int turn) {
    printGameState(node->getGameState());
    int player_turn = turn;

    vector<vector<char>> v;

    while (true) {
        if (turn) {
            cout << endl << "Player" << endl;

            // player move
            int level, pos;

            vector<vector<Position>> newGameState = choose_piece_to_move(player_turn, level, pos, node->getGameState());

            node->setGameState(newGameState);

            vector<Piece> newPieces;
            for(Piece p: node->getAI()) {
                if(node->getGameState()[p.getLevel()][p.getPos()].getPiece().getSym() != p.getSym()) {
                    p.setCoords(level, pos);
                }
                newPieces.push_back(p);
            }

            if(player_turn)
                node->setAI(newPieces);
            else
                node->setPlayer(newPieces);

            v.push_back(convertGameSate(node->getGameState()));


            printGameState(node->getGameState());

            if (heuristic_stuck(node->getAI(), node->getGameState())) {
                cout << "Computer WON!" << endl;
                break;
            }
            if (heuristic_stuck(node->getPlayer(), node->getGameState())) {
                cout << "Player WON!" << endl;
                break;
            }

            turn = 0;
        }
        else {
            cout << endl << "Computer" << endl;

            if (player_turn)
                node = minimax(node, 0, depth, false, -1000000, 1000000, v);
            else
                node = minimax(node, 0, depth, true, -1000000, 1000000, v);

            v.push_back(convertGameSate(node->getGameState()));

            //printGameState(node->getGameState());


            if (heuristic_stuck(node->getAI(), node->getGameState())) {
                cout << "Computer WON!" << endl;
                break;
            }
            if (heuristic_stuck(node->getPlayer(), node->getGameState())) {
                cout << "Player WON!" << endl;
                break;
            }

            turn = 1;
        }
    }
}

void bot_vs_bot_gameloop(Node* node, int depth_1, int depth_2) {
    printGameState(node->getGameState());

    vector<vector<char>> v;

    while (true) {

        cout << endl << "Computer 1" << endl;
        cout << "v size: " << v.size() << endl;

        node = minimax(node, 0, depth_1, true, -1000000, 1000000, v);
        v.push_back(convertGameSate(node->getGameState()));

        node->setEval(aval_AI(node->getAI(), node->getPlayer(), node->getGameState()));
        cout << "Aval Player 1: " << node->getEval() << endl;

        printGameState(node->getGameState());

        if (heuristic_stuck(node->getAI(), node->getGameState())) {
            cout << "Computer 2 WON!" << endl;
            break;
        }
        if (heuristic_stuck(node->getPlayer(), node->getGameState())) {
            cout << "Computer 1 WON!" << endl;
            break;
        }

        cout << endl << "Computer 2" << endl;

        node = minimax(node, 0, depth_2, false, -1000000, 1000000, v);
        v.push_back(convertGameSate(node->getGameState()));

        node->setEval(aval_Player(node->getPlayer(), node->getAI(), node->getGameState()));
        cout << "Aval Player 2: " << node->getEval() << endl;

        printGameState(node->getGameState());

        if (heuristic_stuck(node->getAI(), node->getGameState())) {
            cout << "Computer 2 WON!" << endl;
            break;
        }
        if (heuristic_stuck(node->getPlayer(), node->getGameState())) {
            cout << "Computer 1 WON!" << endl;
            break;
        }
    }
}

void get_game_options(int& mode, int& computer_difficulty_1, int& computer_difficulty_2) {
    while (true) {
        cout << "Please select a game mode:" << endl;
        cout << "1. Player vs Player" << endl;
        cout << "2. Player vs Computer" << endl;
        cout << "3. Computer vs Computer" << endl;
        cout << "Enter your choice (1-3):";
        cin >> mode;
        if (mode >= 1 && mode <= 3) {
            break;
        }
    }
    cout << endl << mode << endl;
    if (mode == 2 || mode == 3) {
        while (true) {
            cout << "Please select a difficulty level for the computer:" << endl;
            cout << "1. Easy" << endl;
            cout << "2. Medium" << endl;
            cout << "3. Hard" << endl;
            cout << "Enter your choice for computer 1 (1-3):";
            cin >> computer_difficulty_1;
            if (computer_difficulty_1 >= 1 && computer_difficulty_1 <= 8) {
                break;
            }
        }
    }

    if (mode == 3) {
        while (true) {
            cout << "Please select a difficulty level for the computer:" << endl;
            cout << "1. Easy" << endl;
            cout << "2. Medium" << endl;
            cout << "3. Hard" << endl;
            cout << "Enter your choice for computer 2 (1-8):";
            cin >> computer_difficulty_2;
            if (computer_difficulty_2 >= 1 && computer_difficulty_2 <= 8) {
                break;
            }
            cout << "Invalid input. Please enter a number between 1 and 3." << endl;
        }
    }

    cout << endl << "Game mode: " << mode << endl;
    if (mode == 2) {
        cout << "Computer difficulty: " << computer_difficulty_1 << endl;
    }
    if (mode == 3) {
        cout << "Computer 1 difficulty: " << computer_difficulty_1 << endl;
        cout << "Computer 2 difficulty: " << computer_difficulty_2 << endl << endl;
    }
}

int main() {

    // initialization of py_game
    Py_Initialize();
    PyObject* object = Py_BuildValue("s", "C:\\Users\\andre\\OneDrive\\Ambiente de Trabalho\\feup\\3ano\\2semestre\\IA\\project1\\py_display\\teste.py");
    FILE* file = _Py_fopen_obj(object, "r+");

    if(file){
        PyRun_SimpleFile(file, "C:\\Users\\andre\\OneDrive\\Ambiente de Trabalho\\feup\\3ano\\2semestre\\IA\\project1\\py_display\\teste.py");
        fclose(file);
    }

    PyObject* object2 = Py_BuildValue("s", "C:\\Users\\andre\\OneDrive\\Ambiente de Trabalho\\feup\\3ano\\2semestre\\IA\\project1\\py_display\\board.py");
    FILE* file2 = _Py_fopen_obj(object2, "r+");

    if(file2){
        PyRun_SimpleFile(file2, "C:\\Users\\andre\\OneDrive\\Ambiente de Trabalho\\feup\\3ano\\2semestre\\IA\\project1\\py_display\\board.py");
        fclose(file);
    }

    // Import the board module
    PyObject* board_module = PyImport_ImportModule("board");

    // Get a reference to the draw_board function
    PyObject* draw_board_func = PyObject_GetAttrString(board_module, "draw_board");

    vector<vector<Position>> gameState = generateGameState(4, 5);
    gameState = generateConnections(gameState);

    Piece piece0 = Piece(0, 'x');
    Piece piece1 = Piece(1, 'x');
    Piece piece2 = Piece(2, 'x');
    Piece piece3 = Piece(3, 'x');

    vector<Piece> player1 = {piece0, piece1, piece2, piece3};

    Piece piece4 = Piece(0, 'o');
    Piece piece5 = Piece(1, 'o');
    Piece piece6 = Piece(2, 'o');
    Piece piece7 = Piece(3, 'o');

    vector<Piece> player2 = {piece4, piece5, piece6, piece7};

    gameState = randomPlacingPhase(player1, player2, gameState);

    //cout << "check heuristic 5: " << heuristic_5_neighbours(player1, gameState) << endl;

    Node* node = new Node(player1, player2, gameState);
    node->setPai(nullptr);

    cout << "------------- Welcome to Bound! -------------" << endl;
    int mode, computer_difficulty_1 = 0, computer_difficulty_2 = 0;
    get_game_options(mode, computer_difficulty_1, computer_difficulty_2);

    switch (mode) {
        case 1:
            p_vs_p_gameloop(node);
            break;
        case 2:
            int turn;
            do {
                cout << "Do you want to play first? Enter 1 for yes, 0 for no:";
                cin >> turn;
                cout << endl;
            } while( turn != 0 && turn != 1);
            p_vs_bot_gameloop(node, computer_difficulty_1, turn);
            break;
        case 3:
            bot_vs_bot_gameloop(node, computer_difficulty_1, computer_difficulty_2);
            break;
        default:
            break;
    }


    Py_Finalize(); // clean up the Python interpreter

    return 0;
}