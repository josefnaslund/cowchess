#include <cmath>
#include "Pawn.h"
#include "LastMove.h"
#include "pawn_w.xpm"
#include "pawn_b.xpm"


using std::abs;
using std::cout;
using std::endl;

Pawn::Pawn(bool color, Board* _gameBoard){

    alive = true;
    white = color;
    type = 'p';
    value = 1.0;


    if (color){
        img = pawn_w_xpm;
    }

    else {
        img = pawn_b_xpm;
    }

    gameBoard = _gameBoard;

}

bool Pawn::validMove(const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck){
    bool valid = true;
    //cout << "Pawn: abs( " << oldY << " - " << newY << ") is " << abs(oldX-oldY) << endl;

    // do not move to same pos, or to same row
    if (oldY == newY){
        valid = false;
    }

    // don't move more than two steps forwad
    else if ( (abs(oldY-newY) > 2)){
        valid = false;
        // std::cout << "Pawn: never more than two steps forward: " << abs(oldX-newX) << ", " << abs(oldY-newY) << std::endl;
    }

    // only two steps forward when pawn is at row 2 or row 7
    else if ( (abs(oldY-newY) == 2) &&
            !(oldY == 1 || oldY == 6)
            ){
        // cout << "Pawn: can only move one step from this pos.\n";
        valid = false;
    }

    // newer more than one step sideways
    else if ( (abs(oldX-newX) > 1) ){
        // cout << "Newer more than one step sideways\n";
        valid = false;
    }

    // white don't jump over pieces
    else if ( (abs(oldY-newY) == 2) && (oldX == newX) && (b[oldY][oldX]->isWhite() && b[2][oldX]->isAlive()) ){
        // cout << "Pawn: white p. cannot jump over piece\n";
        valid = false;
    }
    // black  don't jump over pieces
    else if ( (abs(oldY-newY) == 2) && (oldX == newX) && !b[oldY][oldX]->isWhite() && b[5][oldX]->isAlive()) {
        // cout << "Pawn: black p. cannot jump over piece\n";
        valid = false;
    }


    // don't move straight to the side
    else if ( (oldY == newY) && (abs(oldX-newX) > 0)){
        valid = false;
        // std::cout << "Pawn: never move sideways: " << abs(oldX-newX) << ", " << abs(oldY-newY) << std::endl;
    }

    // don't take piece straight forward
    else if (
            (oldX == newX) && b[newY][newX]->isAlive())
    {
        valid = false;
        // cout << "Pawn: Don't take piece straight forward\n";
    }




    // don't go sideways two steps forward
    else if ( (oldX != newX) && ( abs(oldY - newY) == 2)){
        valid = false;
        // cout << "Pawn: don't go sideways two steps forward\n";
    }


    // test if new pos contains piece of same color
    else if (
            b[newY][newX]->isAlive() &&
            (b[oldY][oldX]->isWhite() == b[newY][newX]->isWhite())
            )
    {
        valid = false;
    }

    // white only move upwards
    else if (
            b[oldY][oldX]->isWhite() &&
            (newY < oldY)
            )
    {
        valid = false;
        // cout << "Pawn is white - can't move down\n";
    }

    // black only move downwards
    else if (
            !b[oldY][oldX]->isWhite() &&
            (newY > oldY)
            )
    {
        valid = false;
        // cout << "Pawn is black - can't move up\n";
    }



    // test for check
    else if (testCheck && isChecked(oldX, oldY, newX, newY)){
        // std::cout << "King is checked\n";
        valid = false;
    }

    // don't go sideways if not take
    else if ( (oldX != newX) && !(b[newY][newX]->isAlive()) ){
        valid = false;

        // test 'en passant'
        const LastMove& lm = gameBoard->getLastMove();
        // last piece is pawn...
        if (lm.getType() == 'p'){
            // cout << "\nType is 'p'\n";
            // cout << "LAST MOVE: " << lm << endl;
            // cout << (abs(lm.getOldY() - lm.getNewY()) == 2) << endl;
            // cout << ((oldY == lm.getNewY())) << endl;
            // cout << ((abs(lm.getNewY() - oldY) == 1)) << endl;
            // cout << (newX == lm.getNewX()) << endl;


            if ( // ...that pawn moved 2 squares forward...
                    abs(lm.getOldY() - lm.getNewY()) == 2 &&

                    // ...and it is on same row as this one...
                    (oldY == lm.getNewY()) &&

                    // ... they are next to each other (columns)
                    (abs(lm.getNewX() - oldX) == 1) &&

                    // ... and they would have been on same cols
                    newX == lm.getNewX()
               ) 
            { 
                valid = true; 
            }

            else {
                valid = false;
            }
        }

        else {
            valid = false;
            // cout << "Pawn: can't move sideways without take\n";
        }
    }    
    return valid;
}


bool Pawn::controlsSquare (const int& oldX, const int& oldY, const int& newX, const int& newY, Piece*** b, bool testCheck){
    bool valid = true;
    //cout << "Pawn: abs( " << oldY << " - " << newY << ") is " << abs(oldX-oldY) << endl;

    // do not move to same pos, or to same row
    if (oldY == newY){
        valid = false;
    }

    // don't move more than two steps forwad
    else if ( (abs(oldY-newY) > 2)){
        valid = false;
        // std::cout << "Pawn: never more than two steps forward: " << abs(oldX-newX) << ", " << abs(oldY-newY) << std::endl;
    }

    // only two steps forward when pawn is at row 2 or row 7
    else if ( (abs(oldY-newY) == 2) &&
            !(oldY == 1 || oldY == 6)
            ){
        // cout << "Pawn: can only move one step from this pos.\n";
        valid = false;
    }

    // newer more than one step sideways
    else if ( (abs(oldX-newX) > 1) ){
        // cout << "Newer more than one step sideways\n";
        valid = false;
    }

    // white don't jump over pieces
    else if ( (abs(oldY-newY) == 2) && (oldX == newX) && (b[oldY][oldX]->isWhite() && b[2][oldX]->isAlive()) ){
        // cout << "Pawn: white p. cannot jump over piece\n";
        valid = false;
    }
    // black  don't jump over pieces
    else if ( (abs(oldY-newY) == 2) && (oldX == newX) && !b[oldY][oldX]->isWhite() && b[5][oldX]->isAlive()) {
        // cout << "Pawn: black p. cannot jump over piece\n";
        valid = false;
    }


    // don't move straight to the side
    else if ( (oldY == newY) && (abs(oldX-newX) > 0)){
        valid = false;
        // std::cout << "Pawn: never move sideways: " << abs(oldX-newX) << ", " << abs(oldY-newY) << std::endl;
    }

    // don't take piece straight forward
    else if (
            (oldX == newX) && b[newY][newX]->isAlive())
    {
        valid = false;
        // cout << "Pawn: Don't take piece straight forward\n";
    }




    // don't go sideways two steps forward
    else if ( (oldX != newX) && ( abs(oldY - newY) == 2)){
        valid = false;
        // cout << "Pawn: don't go sideways two steps forward\n";
    }


    // white only move upwards
    else if (
            b[oldY][oldX]->isWhite() &&
            (newY < oldY)
            )
    {
        valid = false;
        // cout << "Pawn is white - can't move down\n";
    }

    // black only move downwards
    else if (
            !b[oldY][oldX]->isWhite() &&
            (newY > oldY)
            )
    {
        valid = false;
        // cout << "Pawn is black - can't move up\n";
    }



    // test for check
    else if (testCheck && isChecked(oldX, oldY, newX, newY)){
        // std::cout << "King is checked\n";
        valid = false;
    }

    // don't go sideways if not take
    else if ( (oldX != newX) && !(b[newY][newX]->isAlive()) ){
        valid = false;

        // test 'en passant'
        const LastMove& lm = gameBoard->getLastMove();
        // last piece is pawn...
        if (lm.getType() == 'p'){
            // cout << "\nType is 'p'\n";
            // cout << "LAST MOVE: " << lm << endl;
            // cout << (abs(lm.getOldY() - lm.getNewY()) == 2) << endl;
            // cout << ((oldY == lm.getNewY())) << endl;
            // cout << ((abs(lm.getNewY() - oldY) == 1)) << endl;
            // cout << (newX == lm.getNewX()) << endl;


            if ( // ...that pawn moved 2 squares forward...
                    abs(lm.getOldY() - lm.getNewY()) == 2 &&

                    // ...and it is on same row as this one...
                    (oldY == lm.getNewY()) &&

                    // ... they are next to each other (columns)
                    (abs(lm.getNewX() - oldX) == 1) &&

                    // ... and they would have been on same cols
                    newX == lm.getNewX()
               ) 
            { 
                valid = true; 
            }

            else {
                valid = false;
            }
        }

        else {
            valid = false;
            // cout << "Pawn: can't move sideways without take\n";
        }
    }

    return valid;
}
