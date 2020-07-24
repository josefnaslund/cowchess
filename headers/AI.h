#ifndef AI_H
#define AI_H

#include <vector>
#include "AIMove.h"
#include "Piece.h"
#include "Board.h"


class AI {
    private:
        int maxPly;
        bool color;
        Board* gameBoard;


        // returnera alla giltiga drag för en spelare vid ett givet bräde
        std::vector<std::pair<AIMove, double>> collectMoves(bool side, Board* gb);

        // värdera positionens netto för spelaren
        double evaluatePosition(Board* gb, bool side);


        double searchNetto(AIMove move, const int& depth, Board* gb, 
                bool moveSide, bool absoluteSide, double* alfa, double* beta);

    public:
        AI(bool _color, Board* _gameBoard);
        AIMove pickMove();
        void setPly(const int& _ply) { maxPly = _ply;}
};

#endif
