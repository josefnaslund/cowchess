#include <SDL2/SDL.h>                                                           
#include <stdio.h>                                                              
#include <iostream>                                                             
#include "constants.h"                                                          
#include "GUI.h"                                                                
#include "Mouse.h"

using std::cout, std::endl;


int main( int argc, char* args[] )                                              
{                                                                               


    Board board = Board();                                                           
    Mouse myMouse = Mouse();

    // for (int i = 0; i != 8; ++i){
    //         for (int j = 0; j != 8; ++j){
    //                 cout << board.getBoard()[7-i][j].getImage() << "|";
    //         }
    //         cout << endl;
    // }

    bool quit = false;

    GUI mygui = GUI();

    if (mygui.init()){
        // SDL_Delay(5000);

        SDL_Event e;

        while(!quit){

            while (SDL_PollEvent (&e) != 0){
                if (e.type == SDL_QUIT){
                    quit = true;
                }

                // if left button push
                else if (e.type == SDL_MOUSEBUTTONDOWN){

                    // set to "not locked"
                    myMouse.setLocked(false);

                    cout << "left button press: " << e.button.x 
                        << "," << e.button.y 
                        << endl;

                    int arrX = -1, arrY = -1;

                    Piece* clickedPiece = NULL;

                    if (myMouse.getIndexPos(e.button.x, e.button.y, arrX, arrY)){
                        cout << "Main: arrpos: [" << arrY << "][" << arrX << "]\n";
                        clickedPiece = board.getPieceAt(arrX, arrY);
                    }

                    else {
                        cout << "Main - no board at pos\n";
                    }

                    // if there is a piece at clicked pos
                    if (clickedPiece && clickedPiece->isAlive()){
                        cout << "Main-  That IS a piece\n";

                        // if mouse is not locked to a pieace already - lock it
                        if (!myMouse.isLocked()){
                            myMouse.setLocked(true);
                            myMouse.setPosX(e.button.x);
                            myMouse.setPosY(e.button.y);
                        }
                    }

                    else {
                        cout << "Main- There is NO piece there\n";
                    }


                    // If fail to press at piece
                    if (!myMouse.isLocked() && !clickedPiece){
                        cout << "Main: No piece clicked\n";

                    }
                    cout << "---END MOUSEBUTTONDOWN---\n";
                }
                
                // if left button release
                else if (e.type == SDL_MOUSEBUTTONUP){

                    // if user is grabbing a piece and releasing the button
                    if (myMouse.isLocked()){
                        cout << "Button UP! maybe lets try moving piece!?\n"; 

                    }

                    // if user is 
                    else if (!myMouse.isLocked()){
                        cout << "Just a dead release button\n";
                    }

                    cout << "---END MOUSEBUTTONUP---\n";
                }


            } // end while SDL_PollEvent...

            if (mygui.isUpdated()){
                mygui.drawBoard();
                mygui.drawPieces(board.getBoard());
            }


        }                                                                       
    }
    return EXIT_SUCCESS;
}                                                                           


