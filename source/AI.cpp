#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include "AI.h"

using std::cout; 
using std::endl; 
using std::cerr; 
using std::vector; 
using std::sort;
using std::pair;

AI::AI(bool _color, Board* _gameBoard) {
    color = _color;
    gameBoard = _gameBoard;
    board = gameBoard->getBoard();
    // cout << "AI constructed: " << color << endl;
    //
}


bool AI::collectMoves(){
    moves.clear();
    // cout << "AI collecting moves..." << endl;
    Piece* p = NULL;

    // search board for own players
    for (int i = 0; i != 8; ++i){
        for (int j = 0; j != 8; ++j){

            // if own player
            if (board[i][j]->isAlive() && (board[i][j]->isWhite() == color)){
                p = board[i][j];
                // search for valid moves
                for (int ii = 0; ii != 8; ++ii){
                    for (int jj = 0; jj != 8; ++jj){
                        //cout << "AI: " << i << "," << j << " " << ii << "," << jj << endl;
                        if (p->validMove(j, i, jj, ii, board, 1)){
                            // cout << "AI found a valid move\n";
                            moves.push_back(Move(j, i, jj, ii, gameBoard));
                        }
                    }
                }
            }

        }
    }

    // cout << "AI found " << moves.size() << " moves" << endl;
    return moves.size() != 0;
}

void AI::evaluateMoves(){
    evaluatedMoves.clear();
    double maxValue {-999.0};
    double collectedValue;

    // hold a copy of board
    Piece*** tempBoard = new Piece**[8];

    // remember to deallocate
    for (int i = 0; i != 8; ++i){
        tempBoard[i] = new Piece*[8];
    }

    for (auto m : moves){
        collectedValue = 0;


        // copy board
        for (int i = 0; i != 8; ++i){
            for (int j = 0; j != 8; ++j){
                tempBoard[i][j] = board[i][j];
            }
        }

        double captureSquareValue = tempBoard[m.getNewY()][m.getNewX()]->getValue();
        // cout << "Value of " << (char)('a' + m.getNewX()) << m.getNewY() + 1 << " is " << captureSquareValue << endl;

        // make the move on temp board
        tempBoard[m.getNewY()][m.getNewX()] = tempBoard[m.getOldY()][m.getOldX()];

        // erase old position, remember to deallocate
        tempBoard[m.getOldY()][m.getOldX()] = new Piece();

        double movePieceValue = tempBoard[m.getNewY()][m.getNewX()]->getValue();


        // evaluate if there are more attackers than defenders
        // attacker is 'this' side, defender is 'other' side.

        // count attackers and defenders of square
        int attackers = 0, defenders = 0;

        // collect values of attackers and defenders
        vector<double> attackerValues = {};
        vector<double> defenderValues = {};

        // for every square at board, count all alive pieces that either attack or defend square
        for (int row = 0; row !=8; ++row){
            for (int col = 0; col != 8; ++col){
                if (tempBoard[row][col]->isAlive() && 
                        tempBoard[row][col]->controlsSquare(col, row, m.getNewX(), m.getNewY(), tempBoard, 0))
                {
                    if ((tempBoard[row][col]->isWhite() == tempBoard[m.getNewY()][m.getNewX()]->isWhite())){
                        ++attackers;
                        // cout << "Attacker: " << (char)('a' + col) << row+1 << " attacks " << (char)('a' + m.getNewX()) << (m.getNewY() + 1) << endl;
                        attackerValues.push_back(tempBoard[row][col]->getValue());

                    }

                    else {
                        ++defenders;
                        // cout << "Defender: " << (char)('a' + col) << row+1 << " defends " << (char)('a' + m.getNewX()) << (m.getNewY() + 1) << endl;
                        defenderValues.push_back(tempBoard[row][col]->getValue());
                    }

                }



            }
        }


        // sort values of attacker/defender
        // UNUSED
        //
        sort(attackerValues.begin(), attackerValues.end(), 
                []( const double& a, const double &b) -> bool
                {
                return a > b;
                }
            );

        sort(defenderValues.begin(), defenderValues.end(), 
                []( const double& a, const double &b) -> bool
                {
                return a > b;
                }
            );



        // cout << "Total Defenders of square: " << defenders << endl;
        // cout << "values: ";
        // for (auto i : defenderValues) cout << i << " ";
        // cout << endl;
        // cout << "Total Attackers of square: " << attackers << endl;
        // cout << "values: ";
        // for (auto i : attackerValues) cout << i << " ";
        // cout << endl;

        if (!defenders){
            collectedValue += captureSquareValue * 2;
        }
        else if (attackers > defenders){
            collectedValue += captureSquareValue * 1.5;
        }

        // to prevent nothing happening
        // else if (attackers){
        //     collectedValue += captureSquareValue;
        // }

        else {
            collectedValue += captureSquareValue * 1.1 - movePieceValue;
        }


        if (collectedValue >= maxValue){
            maxValue = collectedValue;
            evaluatedMoves.push_back(pair(m, collectedValue));
        }

        delete tempBoard[m.getOldY()][m.getOldX()];
    }


    // dealocate tempBoard
    for (int i = 0; i != 8; ++i){
        delete[] tempBoard[i];
    }

    delete[] tempBoard;
}

void AI::sortMoves(){



    sort(evaluatedMoves.begin(), evaluatedMoves.end(), 
            []( const pair<Move, double> &a, const pair<Move, double> &b) -> bool
            {
            return a.second > b.second;
            }
        );
    // cout << "AI sorted, highest value: " << moves[0].getCaptureValue() << 
    //    ", lowest: " << moves[moves.size() - 1].getCaptureValue() << endl;
    // for (auto m : moves){
    //         cout << m.getCaptureValue() << endl;
    // }

}

int AI::countBestMoves(){
    // count index of last highest value
    double max = -999.0;
    int countMax = 0;

    for (auto p : evaluatedMoves){
        if (p.second == max){

            ++countMax;
        }

        else if (p.second > max){
            countMax = 1;
            max = p.second;
        }

        else {
            break;
        }
    }
    // cout << "AI counter: " << countMax << " best moves" << endl;

    return countMax;
}

int AI::randomInt(int max){
    std::uniform_int_distribution<int> u(0, max);
    std::default_random_engine e;
    e.seed(time(0));

    // throw away some for greater randomness
    for (int i = 0; i != 5; ++i){
        u(e);
    }

    return u(e);



}


Move AI::pickMove(){
    Move m;

    // call help funcions
    if (collectMoves()){
        evaluateMoves();
        sortMoves();
        int maxIndex = countBestMoves() - 1;

        // cout << "Size: " << evaluatedMoves.size() << endl;

        // for (auto p : evaluatedMoves){
        // cout << "\nConsidering...\n";
        // cout << p.first.getPiece()->getType() << " to " << (char)('a' + p.first.getNewX()) << p.first.getNewY() + 1 << " Value: " << p.second << endl;
        // }
        // cout << "end considering\n";

        // pseude random pick one of highest
        m = evaluatedMoves[randomInt(maxIndex)].first;
        // cout << "AI sending move: " << m.getPiece()->getType() << " to " << (char)('a' + m.getNewX()) << "," << m.getNewY() + 1 << "." << endl;
    }

    else {
        m = Move();

    }


    return m;
}
