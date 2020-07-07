#ifndef AI_H
#define AI_H

#include <vector>
#include "Move.h"
#include "Piece.h"
#include "Board.h"

using std::vector;

class AI {
    private:
        bool color;
        Piece*** board;
        Board* gameBoard;
        vector<Move> moves;
        bool collectMoves();
        void sortMoves();
        int countBestMoves();
        int randomInt(int max);

    public:
        AI(bool _color, Board* _gameBoard);
        bool getColor() const { return color; }
        Move pickMove();



        
};

#endif
