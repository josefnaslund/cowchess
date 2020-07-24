#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <utility>
#include <string>
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

    // these values are updated from main anyhow
    if (color) 
        maxPly = 4; // white
    else
        maxPly = 4; // black
}


// collect possible moves for one side from a position
std::vector<std::pair<AIMove, double>> AI::collectMoves(bool side, Board* gb){
    Piece*** b = gb->getBoard();
    // AI put all valid moves for here before analysing their position
    vector<pair<AIMove, double>> allMoves;

    // for every square on board, check for pieces if they can move to any square on board
    for (int i = 0; i != 8; ++i){
        for (int j = 0; j != 8; ++j){
            for (int k = 0; k !=8; ++k){
                for (int l = 0; l != 8; ++l){
                    if (
                            b[i][j]->isAlive() && 
                            (b[i][j]->isWhite() == side) &&
                            b[i][j]->validMove(j, i, l, k, b, 1) &&
                            !gb->getLastMove().noMoves()
                       )
                    {
                        allMoves.push_back(std::make_pair(AIMove(j, i, l, k), 0.0));
                        // cout << "\nAI: Found move " << (char)('a' + j) <<  
                        // i + 1 << " -> " << (char)('a' + l) << k + i << " 
                        // Piece is color= " << b[j][i]->isWhite() << " type=" 
                        // << b[j][i]->getType() << endl;
                    }
                }
            }
        }
    }
    return allMoves;
}



//evaluates a position by total value of pieces
double AI::evaluatePosition(Board* gb, bool side){
    Piece*** b = gb->getBoard();
    // arr[1] will be 'this' side, arr[0] 'other'
    double arr[2] = {0.0, 0.0};
    for (int i = 0; i != 8; ++i){
        for (int j = 0; j != 8; ++j){
            if (b[i][j]->isAlive()){
                arr[b[i][j]->isWhite() == side] += b[i][j]->getValue();
            }
        }
    }
    if (gb->getLastMove().noMoves()){
        arr[1] -= 24;
    }
    // cout << "\nevaluation: arr[1]=" << arr[1] << " arr[0]=" << arr[0] << " and side=" << side << " is asking" << endl;
    return arr[1] - arr[0];
}




// recursive search until mate, stalemate or depth is 0
double AI::searchNetto(AIMove move, const int& depth, Board* gb, bool moveSide, 
        bool absoluteSide, double* alfa, double* beta){

    // make a copy of the game board and transfer the move
    Board newGameBoard = *gb; // remove one of these
    Board* gbPtr = &newGameBoard; // remove one of these
    gbPtr->setSilent();

    // since promotion is a two-way move operation
    bool testPromotion = gbPtr->movePiece(move.getOldX(), move.getOldY(), move.getNewX(), move.getNewY());
    if (!testPromotion && gbPtr->isPromotion()){
        // cout << "forcing promotion\n";
        gbPtr->setPromotionChar('q');
        gbPtr->movePiece(move.getOldX(), move.getOldY(), move.getNewX(), move.getNewY());
    }



    // End recursion if no possible moves
    // Stalemate could be beneficial if other side has more value
    if (gbPtr->getLastMove().noMoves()) {
        if (absoluteSide == moveSide){
            if (gbPtr->getLastMove().isCheck()){
                // cout << "1.1: 0 " << (char)('a' + gbPtr->getLastMove().getOldX()) << 
                //     (1 + gbPtr->getLastMove().getOldY()) << " to " <<
                //     (char)(gbPtr->getLastMove().getNewX() + 'a') << 1 + (gbPtr->getLastMove().getNewY()) << "\n";
                if (*beta > 999.0 + depth){
                    *beta = 999.0 + depth;
                    cout << "alfa=" << *alfa << " beta=" << *beta << endl;
                }
                return 999.0 + depth; // high number for checkmate
            }

            // this will run for 'absolute side' when risk for stalemate
            // cout << "1.2: 0.0 " << (char)('a' + gbPtr->getLastMove().getOldX()) << 
            //     (1+gbPtr->getLastMove().getOldY()) << " to " <<
            //     (char)(gbPtr->getLastMove().getNewX() + 'a') << (1 + gbPtr->getLastMove().getNewY()) << "\n";
            if (*beta > 0.0){
                *beta = 0.0;

                cout << "alfa=" << *alfa << " beta=" << *beta << endl;

            }
            return 0.0; // 0.0 will look good if AI player is behind in material, bad if ahead
        }
        else {
            // AI will avoid checkmate
            if (gbPtr->getLastMove().isCheck()){
                // cout << "1.3: -999\n";
                if (*alfa < -999.0){
                    *alfa = -999.0;
                    cout << "alfa=" << *alfa << " beta=" << *beta << endl;
                }
                return -999.0;
            }

            if (*alfa < 0.0){
                *alfa = 0.0;
                cout << "alfa=" << *alfa << " beta=" << *beta << endl;
            }

            // cout << "1.4: 0\n";
            return 0.0; // 0.0 will look good if AI player is behind in material, bad if ahead
        }
    }


    // to end the recursion
    if (depth == 0){
        //cout << "if moving " << (char)('a' + move.getOldX()) << 
        //    move.getOldY() + 1 <<
        //    " to " << (char)('a' + move.getNewX()) <<
        //    1 + move.getNewY() << " then ..." << endl;

        double val = evaluatePosition(gbPtr, absoluteSide);
        if (absoluteSide == moveSide){
            if (*beta > val){
                cout << "UPDATE BETA\n";
                *beta = val;
                cout << "alfa=" << *alfa << " beta=" << *beta << endl;
            }
        }
        else{
            if (*alfa < val){
                *alfa = val;
                cout << "alfa=" << *alfa << " beta=" << *beta << endl;
            }
        }
        return val;
    }

    // continue search for other sides moves

    vector<pair<AIMove, double>> possibleMoves = collectMoves(!moveSide, gbPtr);

    // if there are moves, should always be possible moves at this point
    if (!possibleMoves.empty()){

        // for every pair of moves/doubles, called by reference
        for (auto& p : possibleMoves){
            double ev = searchNetto(p.first, depth - 1, gbPtr, !moveSide, absoluteSide, alfa, beta);
            if (moveSide == absoluteSide && ev == -9999){
                return -9999;
            }

            else if (moveSide != absoluteSide && ev == 9999){
                return 9999;
            }

            if (moveSide == absoluteSide){
                if (ev > *alfa){
                    *alfa = ev;
                }
            }
            if (moveSide != absoluteSide){
                if (ev < *beta){
                    *beta = ev;
                }
            }

            if (moveSide == absoluteSide && alfa >= beta){
                cout << "\t\t***beta cutoff****\n";
                return -9999;
            }

            else if (moveSide != absoluteSide && beta <= alfa){
                cout << "\t\t****alfa cutoff****\n";
                return 9999;
            }

            p.second = ev;
        }
    }

    // AI will assume other player makes his best
    if (moveSide == absoluteSide){
        return (*std::min_element(possibleMoves.begin(), possibleMoves.end(), 
                    [](const pair<AIMove, double>& a, const pair<AIMove, double>&b){
                    return a.second < b.second;
                    })).second;
    }

    // AI will pick his best move
    return (*std::max_element(possibleMoves.begin(), possibleMoves.end(), 
                [](const pair<AIMove, double>& a, const pair<AIMove, double>&b){
                return a.second < b.second;
                })).second;
}


// pickMove
AIMove AI::pickMove(){
    // cout << "Start picking move...\n";
    int hiIndex = -1;

    double alfa = -9999, beta = 9999;
    double *alfaPtr = &alfa;  // negative 'infinity'
    double *betaPtr = &beta; // positive 'infinity'


    // collect moves
    vector<pair<AIMove, double>> allMoves = collectMoves(color, gameBoard);

    // Debugging info
    // cout << "Theese are all possible moves (not evaluated yet):\n";
    // for (auto p : allMoves){
    //     cout << (char)('a' + p.first.getOldX()) << 1 + p.first.getOldY() <<
    //     " to " <<
    //     (char)('a' + p.first.getNewX()) << 1 + p.first.getNewY() <<
    //     " value=" << std::to_string(p.second) << endl;
    // }
    // cout << endl;

    // ply 4 takes to long time on all moves
    int tempPly = (maxPly >= 4 ? 3 : maxPly);

    // evaluate first move tree
    allMoves[0].second = searchNetto(allMoves[0].first, tempPly, gameBoard, color, color, alfaPtr, betaPtr);
    cout << "\n--------------------\n";
    cout << "first:\n";
    cout << "alpha=" << alfa << endl;
    cout << "beta=" << beta << endl;

    // evaluate rest
    for (auto it = allMoves.begin() + 1; it != allMoves.end(); ++it){
        (*it).second = searchNetto((*it).first, tempPly, gameBoard, color, color, alfaPtr, betaPtr);
        cout << "alpha=" << alfa << endl;
        cout << "beta=" << beta << endl;
    }
    cout << "/////\n";


    if (!allMoves.empty()){

        alfa = -9999; 
        beta = 9999;

        // find max move value (second value of pair in vector)
        hiIndex = std::max_element(allMoves.begin(), allMoves.end(), 
                [](const pair<AIMove, double>& a, const pair<AIMove, double>& b){
                return a.second < b.second;
                }) - allMoves.begin();
        double highest = allMoves[hiIndex].second;

        // sort out the 3 (at most) best moves of the 
        // best moves, within about 5% of the top best move
        vector<pair<AIMove, double>> tempBestMoves;
        double difference = 0.0;
        while ( (tempBestMoves.size() < 3) && (difference < 0.06) ){
            for (auto& p : allMoves){
                if (p.second * (1 - difference) >= highest){ 
                    tempBestMoves.push_back(p);
                    if (tempBestMoves.size() == 5){
                        break;
                    }
                }
            }
            difference += 0.01;
        }

        // cout << "///////////////\n";
        // cout << "Found " << tempBestMoves.size() << " best moves from total " << allMoves.size() << ".\n";
        // for (auto& p : tempBestMoves){
        //     cout << "Value: " << p.second << endl;
        // }
        if (tempBestMoves.size() > 1){
            // cout << "Now running at " << maxPly << " ply.\n";
            for (auto& p : tempBestMoves){
                p.second = searchNetto(p.first, maxPly, gameBoard, color, color, alfaPtr, betaPtr);
                // cout << "Value=" <<  p.second << endl;
            }
        }


        hiIndex = std::max_element(allMoves.begin(), allMoves.end(), 
                [](const pair<AIMove, double>& a, const pair<AIMove, double>& b){
                return a.second < b.second;
                }) - allMoves.begin();

        highest = tempBestMoves[hiIndex].second;
        allMoves.clear();
        allMoves = tempBestMoves;

        // cout << "Highest: " << highest << endl;
        // cout << "||||||||||||||||\n";
    }


    // ...and randomly pick one

    if (allMoves.empty()){
        return AIMove(-1, -1, -1, -1);
    }
    // test if AI makes promotion
    AIMove theMove = allMoves[hiIndex].first;

    if (gameBoard->getBoard()[theMove.getOldY()][theMove.getOldX()]->getType() == 'p' &&
            (theMove.getNewY() == 7 || !theMove.getNewY())
       ){
        // AI makes promotion
        gameBoard->setPromotion(true);
        gameBoard->setPromotionChar('q');
    }


    return allMoves[hiIndex].first;

}
