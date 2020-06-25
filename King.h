#include "Piece.h"

class King : public Piece 
{
    public:
        King(bool color);
        bool validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b) override;
};
