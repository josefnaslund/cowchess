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
        maxPly = 2; // white
    else
        maxPly = 2; // black
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
double AI::searchNetto(AIMove move, const int& depth, Board* gb, bool moveSide, bool absoluteSide){

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
    // todo test for checkmate, stalemate, etc. 
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

        return evaluatePosition(gbPtr, absoluteSide);
    }

    // continue search for other sides moves

    vector<pair<AIMove, double>> possibleMoves = collectMoves(!moveSide, gbPtr);

    // if there are moves, should always be possible moves at this point
    if (!possibleMoves.empty()){

        // for every pair of moves/doubles, called by reference
        for (auto& p : possibleMoves){
            double ev = searchNetto(p.first, depth - 1, gbPtr, !moveSide, absoluteSide);
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


    // evaluate moves one by one 
    for (auto& p : allMoves){
        p.second = searchNetto(p.first, maxPly, gameBoard, color, color);
    }


    if (!allMoves.empty()){
        // find max move value (second value of pair in vector)
        hiIndex = std::max_element(allMoves.begin(), allMoves.end(), 
                [](const pair<AIMove, double>& a, const pair<AIMove, double>& b){
                return a.second < b.second;
                }) - allMoves.begin();
        double highestValue = allMoves[hiIndex].second;


        hiIndex = std::max_element(allMoves.begin(), allMoves.end(), 
                [](const pair<AIMove, double>& a, const pair<AIMove, double>& b){
                return a.second < b.second;
                }) - allMoves.begin();

        highestValue = allMoves[hiIndex].second;

        // ...and randomly pick one within top range of best moves
        vector<pair<AIMove, double>> randomQualifyMoves;
        for (auto& p : allMoves){
            if (std::abs(p.second - highestValue) <= 0.05){
                randomQualifyMoves.push_back(p);
            }
        }
        AIMove theMove = randomQualifyMoves[randomInt(randomQualifyMoves.size() - 1)].first;

        // cout << "\n-----------------------\n";
        // cout << "Evaluation of moves:\n";
        // cout << "-----------------------\n";
        // for (auto p : allMoves){

        //     cout << (char)('a' + p.first.getOldX()) << 1 + p.first.getOldY() <<
        //         " to " << 
        //         (char)('a' + p.first.getNewX()) << 1 + p.first.getNewY() <<
        //         " value=" << std::to_string(p.second) << endl;
        // }
        // cout << endl;

        // test if AI makes promotion
        if (gameBoard->getBoard()[theMove.getOldY()][theMove.getOldX()]->getType() == 'p' &&
                (theMove.getNewY() == 7 || !theMove.getNewY())
           ){
            // cout << "###############\n";
            // cout << "AI PROMOTION\n";
            // cout << "###############\n";
            gameBoard->setPromotion(true);
            gameBoard->setPromotionChar('q');
        }


        return theMove;


    }

    // if (!allMoves.empty()){
    //     // find best
    //     hiIndex = std::max_element(allMoves.begin(), allMoves.end(), 
    //             [](const pair<AIMove, double>& a, const pair<AIMove, double>& b){
    //             return a.second < b.second;
    //             }) - allMoves.begin();

    //     // Debug - print all possible moves and respective value
    //     cerr << "\n##########################\n";
    //     cerr << "All moves and evaluation:\n";
    //     for (size_t i = 0; i != allMoves.size(); ++i){
    //         AIMove tempMove = allMoves[i].first;
    //         cerr << i << ". " << (char)('a' + tempMove.getOldX()) << 
    //             tempMove.getOldY() + 1 <<
    //             " to " << (char)('a' + tempMove.getNewX()) <<
    //             1 + tempMove.getNewY() << " Value=" <<
    //             std::to_string(allMoves[i].second) << endl;

    //     }
    //     cerr << "Highest value: " << allMoves[hiIndex].second << endl;
    //     cerr << "--------------------------\n";
    //     // END debug
    // }

    return AIMove(-1, -1, -1, -1);

    // cerr << "////////////\n";
    // cerr << "DEBUG\n";
    // cerr << "////////////\n";
    // cerr << "// type=" <<  gameBoard->getBoard()[theMove.getNewY()][theMove.getNewX()]->getType() << endl;
    // cerr << "// row=" << theMove.getNewY() << endl;



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
