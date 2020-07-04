#ifndef AI_H
#define AI_H

#include <vector>
#include "Move.h"
#include "Piece.h"

using std::vector;

class AI {
    private:
        bool color;
        Piece*** board;
        vector<Move> moves;
        void collectMoves();
        void sortMoves();
        int countBestMoves();
        int randomInt(int max);

    public:
        AI(bool _color, Piece*** _board);
        bool getColor() const { return color; }
        Move pickMove();



        
};

#endif
