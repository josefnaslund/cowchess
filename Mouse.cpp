#include <iostream>
#include "Mouse.h"
#include "constants.h"

using std::cout, std::endl;

Mouse::Mouse(){
    posX = 0;
    posY = 0;
}

void Mouse::setPosX(int _x){
    posX = _x;
    cout << "posX set to: " << posX << endl;
}

void Mouse::setPosY(int _y){
    posY = _y;
    cout << "posY set to: " << posY << endl;
}


bool Mouse::getIndexPos(const int& guiX, const int& guiY, int& arrX, int& arrY){

    if (guiX <= LEFT_MARGIN || guiX >= LEFT_MARGIN + 8 * SQUARE_SIZE ||
            guiY <= TOP_MARGIN || guiY >= TOP_MARGIN + 8 * SQUARE_SIZE){
        cout << "Mouse- Outside of square: " << guiX << "," << guiY << "\n";
        cout << "Mouse- Returning null\n";
        return false;
    }

    cout << "Mouse - Piece at pos: " << guiX << "," << guiY << " : ";


    // chess position x
    arrX = (guiX - LEFT_MARGIN) / 50;
    cout << (char)(65 + arrX);

    // chess position y
    arrY = (7 - (guiY - TOP_MARGIN) / 50);
        
    cout << arrY + 1 << endl;

    cout << "Mouse- END of getIndexPos\n";

    return true;

}
