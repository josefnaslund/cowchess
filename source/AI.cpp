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

AI::AI(bool _color, Piece*** _board) {
    color = _color;
    board = _board;
    cout << "AI constructed: " << color << endl;
}


void AI::collectMoves(){
    moves.clear();
    cout << "AI collecting moves..." << endl;
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
                        cout << "AI: " << i << "," << j << " " << ii << "," << jj << endl;
                        if (p->validMove(j, i, jj, ii, board, 1)){
                            cout << "AI found a valid move\n";
                            moves.push_back(Move(j, i, jj, ii, board));
                        }
                    }
                }
            }

        }
    }

    cout << "AI found " << moves.size() << " moves" << endl;
}

void AI::sortMoves(){
    sort(moves.begin(), moves.end(), 
            [](const Move& a, const Move& b) -> bool
            {
            return a.getCaptureValue() > b.getCaptureValue();
            }
        );
    cout << "AI sorted, highest value: " << moves[0].getCaptureValue() << 
        ", lowest: " << moves[moves.size() - 1].getCaptureValue() << endl;
    for (auto m : moves){
            cout << m.getCaptureValue() << endl;
    }

}

int AI::countBestMoves(){
    // count index of last highest value
    int max = 0;
    int countMax = 0;

    for (auto m : moves){
        if (m.getCaptureValue() >= max){
            max = m.getCaptureValue();
            ++countMax;
        }

        else {
            break;
        }
    }
    cout << "AI counter: " << countMax << " best moves" << endl;

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

    // call help funcions
    collectMoves();
    sortMoves();
    int maxIndex = countBestMoves() - 1;

    // pseude random pick one of highest
    Move m = moves[randomInt(maxIndex)];
    cout << "AI sending move: " << m.getPiece()->getType() << " to " << (char)('a' + m.getNewX()) << "," << m.getNewY() + 1 << "." << endl;
    return m;
}
