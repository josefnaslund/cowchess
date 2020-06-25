#include "Piece.h"

class Rook : public Piece 
{
    public:
        Rook(bool color);
        bool validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b) override;
};
