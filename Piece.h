#ifndef PIECE_H
#define PIECE_H

#include <string>

using std::string;

class Piece {
    private:
        bool alive;
        bool white;
        string img;

    public:
        Piece();
        Piece(bool white);

        bool isWhite() const {return white;}
        bool isAlive() const {return alive;}
        string getImage() const {return img;}
        void killPiece(){alive = false;}
};

#endif
