#include <iostream>
#include <vector>
#include <string>
#include<cstdlib>
#include <ctime>

#include "Game.h"
#include "Heuristics.h"
#include "Node.h"
#include "Position.h"
#include "Piece.h"

#include <Python.h>

using namespace std;
Game* game = new Game();
Heuristics* h = new Heuristics(game);

/**
 * Function name: generateGameState
 *
 * Input parameters:
 * - level (int): the number of levels (rows) in the game state
 * - pos (int): the number of positions (columns) in the game state
 *
 * Return value:
 * - gameState (vector<vector<Position>>): a 2D vector of Position objects representing the initial game state
 *
 * Function description:
 * This function generates the initial game state for a game board of a given number of levels (rows) and positions (columns).
 * It does so by creating a 2D vector of Position objects and initializing each Position object with an empty Piece object.
 * The Piece object represents a game piece that can be placed on the game board later.
 * The Position objects are then stored in a vector, which is in turn stored in the 2D vector representing the game state.
 * The function returns this 2D vector as the initial game state.
 */
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

/**
 * Function name: generateConnections
 *
 * Input parameters:
 * - gameState (vector<vector<Position>>): a 2D vector of Position objects representing the game state
 *
 * Return value:
 * - final (vector<vector<Position>>): a 2D vector of Position objects representing the game state with added neighbours
 *
 * Function description:
 * This function takes a 2D vector of Position objects representing the game state and adds neighbours to each Position object
 * based on its position in the game board. Neighbours are defined as Positions that are adjacent to the current Position, either
 * horizontally, vertically, or diagonally.
 * The function iterates through each Position object in the game state and checks its position in relation to the other Positions
 * in the game board to determine its neighbours. Neighbours are then added to the current Position object using the addNeighbour()
 * method defined for the Position class.
 * The function returns the modified 2D vector of Position objects as the final game state with added neighbours.
 */
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

/**
 * Function name: validGameState
 *
 * Input parameters:
 * - gameState (vector<vector<Position>>): a 2D vector of Position objects representing the game state
 *
 * Return value:
 * - true if the game state is valid, false otherwise
 *
 * Function description:
 * This function takes a 2D vector of Position objects representing the game state and checks if each Position object has exactly
 * three neighbours. A valid game state is one in which every Position object has exactly three neighbours, meaning it is connected
 * to exactly three other Positions in the game board.
 * The function iterates through each Position object in the game state and checks its number of neighbours using the getNeighbours()
 * method defined for the Position class. If a Position object has a number of neighbours that is not equal to three, the function
 * returns false immediately, indicating that the game state is not valid.
 * If all Position objects have exactly three neighbours, the function returns true, indicating that the game state is valid.
 */
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

/**
 * Checks if a given position on a specific level of the game board is available to place a new piece.
 * @param level an integer representing the level number (0-indexed) where the new piece will be placed.
 * @param pos an integer representing the position number (0-indexed) where the new piece will be placed on the given level.
 * @param gameState a 2D vector of Position objects representing the current state of the game board.
 * @return Returns a boolean value of true or false. It returns true if the given position is empty and available to place a new piece. It returns false if the given position is already occupied by a piece.
 */
bool canPlace(int level, int pos, vector<vector<Position>> gameState) {
    if (gameState[level][pos].getPiece().getSym() != ' ') {
        return false;
    }
    return true;
}

/**
 * Places a given piece on a specific position on a specific level of the game board.
 * @param piece a reference to a Piece object that will be placed on the board.
 * @param level an integer representing the level number (0-indexed) where the piece will be placed.
 * @param pos an integer representing the position number (0-indexed) where the piece will be placed on the given level.
 * @param gameState a 2D vector of Position objects representing the current state of the game board.
 * @return Returns a 2D vector of Position objects representing the updated state of the game board after placing the given piece on the specified position and level.
 */
vector<vector<Position>> place(Piece& piece, int level, int pos, vector<vector<Position>> gameState) {
    vector<vector<Position>> final = gameState;

    piece.setCoords(level, pos);
    final[level][pos].setPiece(piece);
    return final;
}

/**
 * Gets a 2D vector of characters representing the symbols of the pieces on the game board.
 * @param gameState a 2D vector of Position objects representing the current state of the game board.
 * @return Returns a 2D vector of characters representing the symbols of the pieces on the game board. If a position on the game board is empty, the corresponding character in the vector will be a space (' ').
 */

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

/**
 * Executes the placing phase of the game for the player. Allows the player to place their pieces on the bottom level of the game board, while placing the corresponding adversary pieces on the top level.
 * @param player_pieces a vector of Piece objects representing the player's pieces.
 * @param adv_pieces a vector of Piece objects representing the adversary's pieces.
 * @param gameState a 2D vector of Position objects representing the current state of the game board.
 * @return Returns a 2D vector of Position objects representing the updated state of the game board after the player has placed all their pieces and the adversary has placed their corresponding pieces.
 */
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

/**
*This function randomly places the player's and the opponent's pieces on the game board during the placing phase of a game.
*@param player_pieces A vector containing the player's pieces.
*@param adv_pieces A vector containing the opponent's pieces.
*@param gameState A 2D vector representing the current state of the game board.
*@return A 2D vector representing the updated state of the game board after the player's and opponent's pieces have been randomly placed.
*/
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

/**
*This function converts a 2D vector representing the current state of the game board into a 1D vector of characters.
*@param gameState A 2D vector representing the current state of the game board.
*@return A 1D vector of characters representing the state of the game board.
*/
vector<char> convertGameSate(vector<vector<Position>> gameState) {
    vector<char> res;

    for (int i = 0; i < gameState.size(); i++) {
        for (int j = 0; j < gameState[i].size(); j++) {
            res.push_back(gameState[i][j].getPiece().getSym());
        }
    }
    return res;
}

/**
*This function checks if a given game state represented as a 2D vector has been visited before.
*@param visited A 2D vector of characters representing the previously visited game states.
*@param gameState A 2D vector representing the current state of the game board.
*/
bool isVisited(vector<vector<char>> visited, vector<vector<Position>> gameState) {
    vector<char> charState = convertGameSate(gameState);

    for (int i = 0; i < visited.size(); i++) {
        if (visited[i] == charState) {
            return true;
        }
    }

    return false;
}

/**
 * Minimax algorithm with alpha-beta pruning.
 *
 * @param node The current node being evaluated.
 * @param depth The current depth of the search tree.
 * @param maxDepth The maximum depth to be searched.
 * @param AI A boolean flag indicating whether the current player is AI or not.
 * @param alpha The best value that the maximizing player currently has available.
 * @param beta The best value that the minimizing player currently has available.
 * @param visited A vector of previously visited game states.
 *
 * @return The best move to be taken at the current node.
 */
Node* minimax(Node* node, int depth, int maxDepth, bool AI, int alpha, int beta, vector<vector<char>> visited) {
    if (depth == maxDepth || h->heuristic_stuck(node->getAI(), node->getGameState()) || h->heuristic_stuck(node->getPlayer(), node->getGameState())) {
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

                if (!game->canMove(p.getLevel(), p.getPos(), neighbour.getLevel(), neighbour.getPos(), tester)) {
                    continue;
                }

                tester = game->move(p, neighbour.getLevel(), neighbour.getPos(), tester);

                if (isVisited(visited, tester)) {
                    continue;
                }
                visited.push_back(convertGameSate(tester));

                vector<Piece> piece_tester = pieces1;
                piece_tester[i].setCoords(neighbour.getLevel(), neighbour.getPos());

                new_node = new Node(piece_tester, node->getPlayer(), tester);
                new_node->setPai(node);

                Node* challenger = minimax(new_node, depth+1, maxDepth, false, alpha, beta, visited);
                challenger->setEval(h->aval_AI(challenger->getAI(), challenger->getPlayer(), challenger->getGameState()));
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

                if (!game->canMove(p.getLevel(), p.getPos(), neighbour.getLevel(), neighbour.getPos(), tester)) {
                    continue;
                }

                tester = game->move(p, neighbour.getLevel(), neighbour.getPos(), tester);

                if (isVisited(visited, tester)) {
                    continue;
                }
                visited.push_back(convertGameSate(tester));

                vector<Piece> piece_tester = pieces2;
                piece_tester[i].setCoords(neighbour.getLevel(), neighbour.getPos());

                new_node = new Node(node->getAI(), piece_tester, tester);
                new_node->setPai(node);

                Node* challenger = minimax(new_node, depth+1, maxDepth, true, alpha, beta, visited);
                challenger->setEval(h->aval_Player(challenger->getPlayer(), challenger->getAI(), challenger->getGameState()));
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

/**
*Chooses the piece to move based on the current turn and user input.
*
*@param turn an integer indicating the current turn (0 for 'o' and 1 for 'x')
*@param level a reference to an integer that will be updated with the chosen level to move the piece to
*@param pos a reference to an integer that will be updated with the chosen position to move the piece to
*@param gameState a vector of vector of Position objects representing the current game state
*@param board_module a Python module containing the board functions
*@param turn_str a string indicating the current turn ('o' or 'x')
*@return a vector of vector of Position objects representing the updated game state after the piece has been moved
*/
vector<vector<Position>> choose_piece_to_move(int turn, int& level, int& pos, vector<vector<Position>> gameState, PyObject* board_module, string turn_str) {
    char p;
    if (turn)
        p = 'x';
    else
        p = 'o';

    int lin, col;

    PyObject* get_piece_func = PyObject_GetAttrString(board_module, "get_piece");
    PyObject* get_pos_func = PyObject_GetAttrString(board_module, "get_pos");
    PyObject* print_warnings = PyObject_GetAttrString(board_module, "print_warnings");
    PyObject* print_turn = PyObject_GetAttrString(board_module, "print_turn");

    vector<vector<char>> positions = getSymbols(gameState);

    // Convert the 2D vector to a Python list of lists
    PyObject* pyPositions = PyList_New(positions.size());
    for (int i = 0; i < positions.size(); i++) {
        PyObject* pyRow = PyList_New(positions[i].size());
        for (int j = 0; j < positions[i].size(); j++) {
            PyList_SetItem(pyRow, j, PyUnicode_FromFormat("%c", positions[i][j]));
        }
        PyList_SetItem(pyPositions, i, pyRow);
    }

    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, pyPositions);

    // Ask the user to enter the row and column of the piece to move
    while(true) {
        PyObject_CallObject(print_turn, Py_BuildValue("(s)", turn_str.c_str()));
        PyObject* result = PyObject_CallObject(get_piece_func, args);
        lin = PyLong_AsLong(PyList_GetItem(result, 0));
        col = PyLong_AsLong(PyList_GetItem(result, 1));

        if(lin < 0 || lin >= gameState.size() || col < 0 || col >= gameState[0].size()){
            PyObject_CallObject(print_warnings, Py_BuildValue("(s)", "Input out of bounds! (press SPACE)"));
            continue;
        }

        // If no piece was found, ask the user to try again
        if(gameState[lin][col].getPiece().getSym() != p) {
            PyObject_CallObject(print_warnings, Py_BuildValue("(s)", "Piece not found. Please try again. (press SPACE)"));
            continue;
        }

        result = PyObject_CallObject(get_pos_func, nullptr);
        level = PyLong_AsLong(PyList_GetItem(result, 0));
        pos = PyLong_AsLong(PyList_GetItem(result, 1));

        if(game->canMove(lin, col, level, pos, gameState))
            break;
    }

    return game->move(gameState[lin][col].getPiece(), level, pos, gameState);
}

/**
 * Plays a game between two human players in a loop.
 *
 * @param node Pointer to the root node of the game tree.
 * @param board_module Pointer to the Python board module.
 * @return void.
 */
void p_vs_p_gameloop(Node* node, PyObject* board_module) {
    int turn = 1;
    PyObject* print_string = PyObject_GetAttrString(board_module, "print_string");

    while (true) {
        if (turn) {
            // player move
            int level, pos;
            vector<vector<Position>> newGameState = choose_piece_to_move(turn, level, pos, node->getGameState(), board_module, "Player 1");
            node->setGameState(newGameState);

            vector<Piece> newPieces;
            for(Piece p: node->getAI()) {
                if(node->getGameState()[p.getLevel()][p.getPos()].getPiece().getSym() != p.getSym()) {
                    p.setCoords(level, pos);
                }
                newPieces.push_back(p);
            }
            node->setAI(newPieces);

            if (h->heuristic_stuck(node->getAI(), node->getGameState())) {
                PyObject_CallObject(print_string, Py_BuildValue("(s)", "Player 1 Won! (press SPACE)"));
                break;
            }
            if (h->heuristic_stuck(node->getPlayer(), node->getGameState())) {
                PyObject_CallObject(print_string, Py_BuildValue("(s)", "Player 2 Won! (press SPACE)"));
                break;
            }

            turn = 0;
        }
        else {
            // player move
            int level, pos;
            vector<vector<Position>> newGameState = choose_piece_to_move(turn, level, pos, node->getGameState(), board_module, "Player 2");
            node->setGameState(newGameState);

            vector<Piece> newPieces;
            for(Piece p: node->getPlayer()) {
                if(node->getGameState()[p.getLevel()][p.getPos()].getPiece().getSym() != p.getSym()) {
                    p.setCoords(level, pos);
                }
                newPieces.push_back(p);
            }
            node->setPlayer(newPieces);

            if (h->heuristic_stuck(node->getAI(), node->getGameState())) {
                PyObject_CallObject(print_string, Py_BuildValue("(s)", "Player 1 Won! (press SPACE)"));
                break;
            }
            if (h->heuristic_stuck(node->getPlayer(), node->getGameState())) {
                PyObject_CallObject(print_string, Py_BuildValue("(s)", "Player 2 Won! (press SPACE)"));
                break;
            }

            turn = 1;
        }
    }
}

/**
 * Runs the game loop for player versus bot mode.
 *
 * @param node: Pointer to the root node of the game tree.
 * @param depth: Maximum depth to search in the game tree.
 * @param turn: Current turn of the game (1 if it's the player's turn, 0 if it's the bot's turn).
 * @param board_module: Python module containing functions for printing the game board.
 *
 * @return: None.
 */
void p_vs_bot_gameloop(Node* node, int depth, int turn, PyObject* board_module) {
    int player_turn = turn;
    vector<vector<char>> v;

    PyObject* print_string = PyObject_GetAttrString(board_module, "print_string");
    PyObject* print_turn = PyObject_GetAttrString(board_module, "print_turn");
    PyObject* draw_board = PyObject_GetAttrString(board_module, "draw_board");

    while (true) {
        if (turn) {
            // player move
            int level, pos;

            vector<vector<Position>> newGameState = choose_piece_to_move(player_turn, level, pos, node->getGameState(), board_module, "Player");

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

            if (h->heuristic_stuck(node->getAI(), node->getGameState())) {
                PyObject_CallObject(print_string, Py_BuildValue("(s)", "Computer Won! (press SPACE)"));
                break;
            }
            if (h->heuristic_stuck(node->getPlayer(), node->getGameState())) {
                PyObject_CallObject(print_string, Py_BuildValue("(s)", "Player Won! (press SPACE)"));
                break;
            }

            turn = 0;
        }
        else {
            PyObject_CallObject(print_turn, Py_BuildValue("(s)", "Computer"));

            vector<vector<char>> positions = getSymbols(node->getGameState());

            // Convert the 2D vector to a Python list of lists
            PyObject* pyPositions = PyList_New(positions.size());
            for (int i = 0; i < positions.size(); i++) {
                PyObject* pyRow = PyList_New(positions[i].size());
                for (int j = 0; j < positions[i].size(); j++) {
                    PyList_SetItem(pyRow, j, PyUnicode_FromFormat("%c", positions[i][j]));
                }
                PyList_SetItem(pyPositions, i, pyRow);
            }

            PyObject* args = PyTuple_New(1);
            PyTuple_SetItem(args, 0, pyPositions);
            PyObject_CallObject(draw_board, args);

            if (player_turn)
                node = minimax(node, 0, depth, false, -1000000, 1000000, v);
            else
                node = minimax(node, 0, depth, true, -1000000, 1000000, v);

            v.push_back(convertGameSate(node->getGameState()));

            if (h->heuristic_stuck(node->getAI(), node->getGameState())) {
                PyObject_CallObject(print_string, Py_BuildValue("(s)", "Computer Won! (press SPACE)"));
                break;
            }
            if (h->heuristic_stuck(node->getPlayer(), node->getGameState())) {
                PyObject_CallObject(print_string, Py_BuildValue("(s)", "Player Won! (press SPACE)"));
                break;
            }

            turn = 1;
        }
    }
}

/**
*This function represents a game loop where two bots play against each other. The function takes four parameters:
*
*Node* node: A pointer to the current node in the game tree.
*int depth_1: The maximum depth of the game tree that the first bot can explore.
*int depth_2: The maximum depth of the game tree that the second bot can explore.
*PyObject* board_module: A Python module that contains functions for printing the game board and other messages.
*The function initializes a 2D vector representing the game board and calls several functions from the Python module to print the board and messages to the console. It then enters a loop where it alternates between the two bots making moves. In each iteration of the loop, the function:
*
*Calls minimax() to determine the best move for the current bot to make, based on the current state of the game.
*Adds the new state of the game to the 2D vector representing the game board.
*Checks if either bot has won or if the game has ended in a tie, and prints the appropriate message if so.
*Alternates control to the other bot, and repeats the process.
*The function has no return value.
*/
void bot_vs_bot_gameloop(Node* node, int depth_1, int depth_2, PyObject* board_module) {
    vector<vector<char>> v;

    PyObject* print_string = PyObject_GetAttrString(board_module, "print_string");
    PyObject* print_turn = PyObject_GetAttrString(board_module, "print_turn");
    PyObject* draw_board = PyObject_GetAttrString(board_module, "draw_board");

    while (true) {
        PyObject_CallObject(print_turn, Py_BuildValue("(s)", "Computer 1"));

        vector<vector<char>> positions = getSymbols(node->getGameState());

        // Convert the 2D vector to a Python list of lists
        PyObject* pyPositions = PyList_New(positions.size());
        for (int i = 0; i < positions.size(); i++) {
            PyObject* pyRow = PyList_New(positions[i].size());
            for (int j = 0; j < positions[i].size(); j++) {
                PyList_SetItem(pyRow, j, PyUnicode_FromFormat("%c", positions[i][j]));
            }
            PyList_SetItem(pyPositions, i, pyRow);
        }

        PyObject* args = PyTuple_New(1);
        PyTuple_SetItem(args, 0, pyPositions);
        PyObject_CallObject(draw_board, args);

        node = minimax(node, 0, depth_1, true, -1000000, 1000000, v);
        v.push_back(convertGameSate(node->getGameState()));

        node->setEval(h->aval_AI(node->getAI(), node->getPlayer(), node->getGameState()));

        if (h->heuristic_stuck(node->getAI(), node->getGameState())) {
            PyObject_CallObject(print_string, Py_BuildValue("(s)", "Computer 2 Won! (press SPACE)"));
            break;
        }
        if (h->heuristic_stuck(node->getPlayer(), node->getGameState())) {
            PyObject_CallObject(print_string, Py_BuildValue("(s)", "Computer 1 Won! (press SPACE)"));
            break;
        }

        PyObject_CallObject(print_turn, Py_BuildValue("(s)", "Computer 2"));

        positions = getSymbols(node->getGameState());

        // Convert the 2D vector to a Python list of lists
        pyPositions = PyList_New(positions.size());
        for (int i = 0; i < positions.size(); i++) {
            PyObject* pyRow = PyList_New(positions[i].size());
            for (int j = 0; j < positions[i].size(); j++) {
                PyList_SetItem(pyRow, j, PyUnicode_FromFormat("%c", positions[i][j]));
            }
            PyList_SetItem(pyPositions, i, pyRow);
        }

        args = PyTuple_New(1);
        PyTuple_SetItem(args, 0, pyPositions);
        PyObject_CallObject(draw_board, args);

        node = minimax(node, 0, depth_2, false, -1000000, 1000000, v);
        v.push_back(convertGameSate(node->getGameState()));

        node->setEval(h->aval_Player(node->getPlayer(), node->getAI(), node->getGameState()));

        if (h->heuristic_stuck(node->getAI(), node->getGameState())) {
            PyObject_CallObject(print_string, Py_BuildValue("(s)", "Computer 2 Won! (press SPACE)"));
            break;
        }
        if (h->heuristic_stuck(node->getPlayer(), node->getGameState())) {
            PyObject_CallObject(print_string, Py_BuildValue("(s)", "Computer 1 Won! (press SPACE)"));
            break;
        }
    }
}

int main() {

    // initialization of py_game
    Py_Initialize();
    PyObject* object = Py_BuildValue("s", R"(path\to\py_display\teste.py)");
    FILE* file = _Py_fopen_obj(object, "r+");

    if(file){
        PyRun_SimpleFile(file, "path\\to\\py_display\\teste.py");
        fclose(file);
    }

    PyObject* object2 = Py_BuildValue("s", R"(path\tog\py_display\board.py)");
    FILE* file2 = _Py_fopen_obj(object2, "r+");

    if(file2){
        PyRun_SimpleFile(file2, "path\\to\\py_display\\board.py");
        fclose(file);
    }

    // Import the board module
    PyObject* board_module = PyImport_ImportModule("board");

    // start of the c++ code
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

    Node* node = new Node(player1, player2, gameState);
    node->setPai(nullptr);

    int mode, computer_difficulty_1 = 0, computer_difficulty_2 = 0, turn;

    // Get a reference to the board.py functions
    PyObject* menu_func = PyObject_GetAttrString(board_module, "get_game_options");
    PyObject* result = PyObject_CallObject(menu_func, nullptr);
    mode = PyLong_AsLong(PyList_GetItem(result, 0));
    computer_difficulty_1 = PyLong_AsLong(PyList_GetItem(result, 1));
    if(mode == 3) {
        computer_difficulty_2 = PyLong_AsLong(PyList_GetItem(result, 2));
    }

    switch (mode) {
        case 1:
            p_vs_p_gameloop(node, board_module);
            break;
        case 2:
            turn = PyLong_AsLong(PyList_GetItem(result, 2));
            p_vs_bot_gameloop(node, computer_difficulty_1, turn, board_module);
            break;
        case 3:
            bot_vs_bot_gameloop(node, computer_difficulty_1, computer_difficulty_2, board_module);
            break;
        default:
            break;
    }

    PyObject* exit = PyObject_GetAttrString(board_module, "exit_function");
    PyObject_CallObject(exit, nullptr);

    Py_Finalize(); // clean up the Python interpreter

    return 0;
}