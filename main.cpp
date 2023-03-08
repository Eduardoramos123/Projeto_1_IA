#include <iostream>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <queue>
#include <stack>
#include<cstdlib>
#include <ctime>

using namespace std;

class Piece {
private:
    int id;
    char sym;
    int level;
    int pos;
public:
    Piece(int i, char s);

    Piece();

    void setId(int i);
    void setSym(char s);
    void setCoords(int l, int p);
    int getId() const;
    char getSym() const;
    int getPos() const;
    int getLevel() const;
};

Piece::Piece(int i, char s) {
    id = i;
    sym = s;
}

void Piece::setId(int i) {
    id = i;
}

void Piece::setSym(char s) {
    sym = s;
}

void Piece::setCoords(int l, int p) {
    level = l;
    pos = p;
}

char Piece::getSym() const {
    return sym;
}

int Piece::getId() const {
    return id;
}

int Piece::getPos() const {
    return pos;
}

int Piece::getLevel() const {
    return level;
}

Piece::Piece() {
    id = 0;
    sym = ' ';
}

class Position {
private:
    int level;
    int pos;
    Piece piece;
    vector<Position> neighbours;
public:
    Position(int l, int p);
    void setPos(int p);
    void setLevel(int l);
    int getPos() const;
    int getLevel() const;
    void setPiece(Piece piece1);
    Piece getPiece();
    void setNeighbours(vector<Position> v);
    vector<Position> getNeighbours();
    void addNeighbour(Position p);
};

Position::Position(int l, int p) {
    level = l;
    pos = p;
    neighbours = {};
    piece = Piece();
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

void Position::setPiece(Piece piece1) {
    piece = piece1;
}

Piece Position::getPiece() {
    return piece;
}

void Position::setNeighbours(vector<Position> v) {
    neighbours = v;
}

vector<Position> Position::getNeighbours() {
    return neighbours;
}

void Position::addNeighbour(Position p) {
    neighbours.push_back(p);
}

vector<vector<Position>> generateGameState(int level, int pos) {
    vector<vector<Position>> gameState;

    for (int i = 0; i < level; i++) {
        vector<Position> v;
        for (int j = 0; j < pos; j++) {
            Position p = Position(i, j);
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
                    final[i][j].addNeighbour(final[i + 1][gameState[i].size() - 1]);

                    final[i + 1][j + 1].addNeighbour(final[i][j]);
                    final[i + 1][gameState[i].size() - 1].addNeighbour(final[i][j]);
                }
                else if (j == (gameState[i].size() - 1)) {
                    final[i][j].addNeighbour(final[i + 1][0]);
                    final[i][j].addNeighbour(final[i + 1][j - 1]);

                    final[i + 1][0].addNeighbour(final[i][j]);
                    final[i + 1][j - 1].addNeighbour(final[i][j]);
                }
                else {
                    final[i][j].addNeighbour(final[i + 1][j + 1]);
                    final[i][j].addNeighbour(final[i + 1][j - 1]);

                    final[i + 1][j + 1].addNeighbour(final[i][j]);
                    final[i + 1][j - 1].addNeighbour(final[i][j]);
                }
            }
        }
    }
    return final;
}

bool validGameState(vector<vector<Position>> gameState) {
    for (int i = 0; i < gameState.size(); i++) {
        for (int j = 0; j < gameState[i].size(); j++) {
            if (gameState[i][j].getNeighbours().size() != 3) {
                return false;
            }
        }
    }
    return true;
}

bool canMove(int level1, int pos1, int level2, int pos2, vector<vector<Position>> gameState) {
    Position initial = gameState[level1][pos1];
    vector<Position> neighbours = initial.getNeighbours();

    for (int i = 0; i < neighbours.size(); i++) {
        int check_pos = neighbours[i].getPos();
        int check_level = neighbours[i].getLevel();

        if (check_level == level2 && check_pos == pos2 && gameState[check_level][check_pos].getPiece().getSym() == ' ') {
            return true;
        }
    }
    return false;
}

bool isStuck(vector<vector<Position>> gameState, Piece piece) {
    Position initial = gameState[piece.getLevel()][piece.getPos()];
    vector<Position> neighbours = initial.getNeighbours();

    for (int i = 0; i < neighbours.size(); i++) {
        int check_pos = neighbours[i].getPos();
        int check_level = neighbours[i].getLevel();

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

    for (int i = 0; i < gameState.size(); i++) {
        vector<char> v;

        for (int j = 0; j < gameState[i].size(); j++) {
            v.push_back(gameState[i][j].getPiece().getSym());
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

    for (int i = 0; i < pieces.size(); i++) {
        Piece piece = pieces[i];

        Position position = gameState[piece.getLevel()][piece.getPos()];
        vector<Position> neighbours = position.getNeighbours();

        int check = 0;
        for (int j = 0; j < neighbours.size(); j++) {
            if (neighbours[j].getPiece().getSym() == ' ') {
                continue;
            }
            if (neighbours[j].getPiece().getSym() == piece.getSym()) {
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

    for (int i = 0; i < pieces.size(); i++) {
        Piece piece = pieces[i];

        Position position = gameState[piece.getLevel()][piece.getPos()];
        vector<Position> neighbours = position.getNeighbours();

        int check = 0;
        for (int j = 0; j < neighbours.size(); j++) {
            if (neighbours[j].getPiece().getSym() == ' ') {
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

bool heuristic_stuck(vector<Piece> pieces, vector<vector<Position>> gameState) {
    for (int i = 0; i < pieces.size(); i++) {
        Piece piece = pieces[i];

        if (isStuck(gameState, piece)) {
            return true;
        }
    }
    return false;
}

bool about_to_win(vector<Piece> pieces1, vector<Piece> pieces2, vector<vector<Position>> gameState) {
    for (int i = 0; i < pieces2.size(); i++) {
        vector<Position> neighbours = gameState[pieces2[i].getLevel()][pieces2[i].getPos()].getNeighbours();

        for (int j = 0; j < neighbours.size(); j++) {
            vector<vector<Position>> tester = gameState;

            if (!canMove(pieces2[i].getLevel(), pieces2[i].getPos(), neighbours[j].getLevel(), neighbours[j].getPos(), tester)) {
                continue;
            }

            tester = move(pieces2[i], neighbours[j].getLevel(), neighbours[j].getPos(), tester);


            if (heuristic_stuck(pieces1, tester)) {
                return true;
            }
        }
    }

    return false;
}

int control_center(vector<Piece> pieces, vector<vector<Position>> gameState) {
    int res = 0;

    for (int i = 0; i < pieces.size(); i++) {
        Piece piece = pieces[i];


        if (piece.getLevel() > 0 && piece.getLevel() < gameState.size() - 1) {
            res++;
        }
    }
    return res;
}

int aval_AI(vector<Piece> pieces1, vector<Piece> pieces2, vector<vector<Position>> gameState) {
    if (heuristic_stuck(pieces1, gameState)) {
        return -100000;
    }

    if (heuristic_stuck(pieces2, gameState)) {
        return 100000;
    }

    if (about_to_win(pieces1, pieces2, gameState)) {
        return -10000;
    }

    return heuristic_1_piece_near(pieces1, gameState) * 5 - heuristic_2_pieces_near(pieces1, gameState) * 3 + control_center(pieces1, gameState);
}

int aval_Player(vector<Piece> pieces1, vector<Piece> pieces2, vector<vector<Position>> gameState) {
    if (heuristic_stuck(pieces1, gameState)) {
        return 100000;
    }

    if (heuristic_stuck(pieces2, gameState)) {
        return -100000;
    }

    if (about_to_win(pieces1, pieces2, gameState)) {
        return 10000;
    }

    return heuristic_1_piece_near(pieces1, gameState) * -5 + heuristic_2_pieces_near(pieces1, gameState) * 3 - control_center(pieces1, gameState);
}

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

Node* minimax(Node* node, int depth, int maxDepth, bool AI, int alpha, int beta) {
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

            for (int j = 0; j < neighbours.size(); j++) {
                Piece p = pieces1[i];
                vector<vector<Position>> tester = gameState;

                if (!canMove(p.getLevel(), p.getPos(), neighbours[j].getLevel(), neighbours[j].getPos(), tester)) {
                    continue;
                }

                tester = move(p, neighbours[j].getLevel(), neighbours[j].getPos(), tester);
                vector<Piece> piece_tester = pieces1;
                piece_tester[i].setCoords(neighbours[j].getLevel(), neighbours[j].getPos());

                new_node = new Node(piece_tester, node->getPlayer(), tester);
                new_node->setPai(node);

                Node* challenger = minimax(new_node, depth+1, maxDepth, false, alpha, beta);
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

            for (int j = 0; j < neighbours.size(); j++) {
                Piece p = pieces2[i];
                vector<vector<Position>> tester = gameState;

                if (!canMove(p.getLevel(), p.getPos(), neighbours[j].getLevel(), neighbours[j].getPos(), tester)) {
                    continue;
                }

                tester = move(p, neighbours[j].getLevel(), neighbours[j].getPos(), tester);
                vector<Piece> piece_tester = pieces2;
                piece_tester[i].setCoords(neighbours[j].getLevel(), neighbours[j].getPos());

                new_node = new Node(node->getAI(), piece_tester, tester);
                new_node->setPai(node);

                Node* challenger = minimax(new_node, depth+1, maxDepth, true, alpha, beta);
                challenger->setEval(aval_Player(challenger->getAI(), challenger->getPlayer(), challenger->getGameState()));
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
        }
        return best->getPai();

    }

}

int main() {
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

    printGameState(gameState);

    cout << endl << "---------------------------------" << endl;

    //Teste de minimax
    Node* node = new Node(player1, player2, gameState);
    node->setPai(nullptr);



    while (true) {

        cout << endl << "Player 1" << endl;

        node = minimax(node, 0, 4, true, -1000000, 1000000);


        printGameState(node->getGameState());

        if (heuristic_stuck(node->getAI(), node->getGameState())) {
            cout << "Player 2 WON!" << endl;
            break;
        }
        if (heuristic_stuck(node->getPlayer(), node->getGameState())) {
            cout << "Player 1 WON!" << endl;
            break;
        }

        cout << endl << "---------------------------------" << endl;

        cout << endl << "Player 2" << endl;

        node = minimax(node, 0, 2, false, -1000000, 1000000);

        printGameState(node->getGameState());

        if (heuristic_stuck(node->getAI(), node->getGameState())) {
            cout << "Player 2 WON!" << endl;
            break;
        }
        if (heuristic_stuck(node->getPlayer(), node->getGameState())) {
            cout << "Player 1 WON!" << endl;
            break;
        }

    }

    return 0;
}
