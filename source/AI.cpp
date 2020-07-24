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

    // *alfa = -9999;
    // *beta = 9999;
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
                return 999.0 + depth; // high number for checkmate
            }

            // this will run for 'absolute side' when risk for stalemate
            // cout << "1.2: 0.0 " << (char)('a' + gbPtr->getLastMove().getOldX()) << 
            //     (1+gbPtr->getLastMove().getOldY()) << " to " <<
            //     (char)(gbPtr->getLastMove().getNewX() + 'a') << (1 + gbPtr->getLastMove().getNewY()) << "\n";

            return 0.0; // 0.0 will look good if AI player is behind in material, bad if ahead
        }
        else {
            // AI will avoid checkmate
            if (gbPtr->getLastMove().isCheck()){
                // cout << "1.3: -999\n";
                return -999.0;
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

        return val;
    }



    if (moveSide != absoluteSide){
        // continue search for other sides moves
        vector<pair<AIMove, double>> possibleMoves = collectMoves(!moveSide, gbPtr);

        // if there are moves, should always be possible moves at this point
        if (!possibleMoves.empty()){

            double value = -9999.0; // 'infinite' negative

            // for every pair of moves/doubles, called by reference
            for (auto& p : possibleMoves){
                value = std::max(searchNetto(p.first, depth - 1, gbPtr, !moveSide, absoluteSide, alfa, beta), value);
                *alfa = std::max(*alfa, value);

                // cout << "moveSide=" << moveSide << " absoluteSide=" << absoluteSide << " a=" << *alfa << " b=" << *beta << " val=" << value << endl;
                if (alfa >= beta){
                    cout << "\t\t\t****beta cut-off*********\n";
                    break;

                }

                p.second = value;
            }

            // AI will assume other player makes his best
            return (*std::max_element(possibleMoves.begin(), possibleMoves.end(), 
                        [](const pair<AIMove, double>& a, const pair<AIMove, double>&b){
                        return a.second < b.second;
                        })).second;
        }




    }

    // moveSide == absoluteSide
    else { 
        // continue search for other sides moves
        vector<pair<AIMove, double>> possibleMoves = collectMoves(!moveSide, gbPtr);
        double value = 9999.0;


        // if there are moves, should always be possible moves at this point
        if (!possibleMoves.empty()){

            // for every pair of moves/doubles, called by reference
            for (auto& p : possibleMoves){
                value = std::min(searchNetto(p.first, depth - 1, gbPtr, !moveSide, absoluteSide, alfa, beta), value);
                *beta = std::min(value, *beta);
                // cout << "moveSide=" << moveSide << " absoluteSide=" << absoluteSide << " a=" << *alfa << " b=" << *beta << " val=" << value << endl;
                if (beta <= alfa){
                    cout << "\t\t\t*****alfa cut-off*******\n";
                    break;
                }

                p.second = value;
            }
        }
        // AI will pick his best move
        return (*std::min_element(possibleMoves.begin(), possibleMoves.end(), 
                    [](const pair<AIMove, double>& a, const pair<AIMove, double>&b){
                    return a.second < b.second;
                    })).second;
    }
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

    // evaluate all on lower ply
    for (auto it = allMoves.begin(); it != allMoves.end(); ++it){
        (*it).second = searchNetto((*it).first, tempPly, gameBoard, color, color, alfaPtr, betaPtr);
    }


    if (!allMoves.empty()){

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
        while ( (tempBestMoves.size() < 40) && (difference < 4) ){
            for (auto it = allMoves.begin(); it != allMoves.end(); ++it){
                if ((*it).second * (1 - difference) >= highest){ 
                    tempBestMoves.push_back(*it);
                    allMoves.erase(it);
                    break;
                }
            }
            difference += 0.01;
        }
        cout << "\ntempBestMoves.size()=" << tempBestMoves.size() << endl;
        cout << "///////////////\n";
        cout << "Found " << tempBestMoves.size() << " best moves from total " << allMoves.size() << ".\n";
        for (auto& p : tempBestMoves){
            cout << (char)('a' + p.first.getOldX()) << 1 + p.first.getOldY() << " to " << (char)('a' + p.first.getNewX()) << 1 + p.first.getNewY() << " Value: " << p.second << endl;
        }
        
        if (tempBestMoves.size() > 1){
            cout << "Now running at " << maxPly << " ply.\n";
            for (auto& p : tempBestMoves){
                p.second = searchNetto(p.first, maxPly, gameBoard, color, color, alfaPtr, betaPtr);
                cout << (char)('a' + p.first.getOldX()) << p.first.getOldY() + 1 << " to " << (char)('a' + p.first.getNewX()) << 1 + p.first.getNewY() << " Value=" <<  p.second << endl;
            }
        }


        hiIndex = std::max_element(tempBestMoves.begin(), tempBestMoves.end(), 
                [](const pair<AIMove, double>& a, const pair<AIMove, double>& b){
                return a.second < b.second;
                }) - tempBestMoves.begin();

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
