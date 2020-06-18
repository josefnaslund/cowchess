#ifndef PIECE_H
#define PIECE_H

#include <string>

using std::string;

class Piece {
    private:
        bool exist;
        bool white;
        string img;

    public:
        Piece();
        Piece(bool white);

        bool isWhite() const {return white;}
        bool isExist() const {return exist;}
        string getImage() const {return img;}
        void killPiece(){exist = false;}
};

#endif
