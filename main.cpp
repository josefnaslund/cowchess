#include <SDL2/SDL.h>                                                           
#include <stdio.h>                                                              
#include <iostream>                                                             
#include "constants.h"                                                          
#include "GUI.h"                                                                
#include "Mouse.h"

using std::cout, std::endl, std::cerr;


int main( int argc, char* args[] )                                              
{                                                                               

    Board board = Board();                                                           
    Mouse myMouse = Mouse();

    bool quit = false;

    GUI mygui = GUI();

    if (mygui.init()){
        SDL_Delay(100);

        SDL_Event e;

        bool moveMade;

        mygui.update(board.getBoard());

        while(!quit){
            moveMade = false;


            while (SDL_PollEvent (&e) != 0){
                if (e.type == SDL_QUIT){
                    quit = true;
                }

                // to prevent mouse buttons other than left to interfere
                else if (!moveMade && e.button.button != SDL_BUTTON_LEFT){
                    ; // do nothing
                }

                // if left button push
                else if (!moveMade && e.type == SDL_MOUSEBUTTONDOWN){

                    // set to "not locked"
                    myMouse.setLocked(false);

                    int arrX = -1, arrY = -1;

                    Piece* clickedPiece = NULL;

                    if (myMouse.getIndexPos(e.button.x, e.button.y, arrX, arrY)){
                        cout << "Main: arrpos: [" << arrY << "][" << arrX << "]\n";
                        clickedPiece = board.getPieceAt(arrX, arrY);
                    }


                    // if there is a piece at clicked pos
                    if (clickedPiece && clickedPiece->isAlive()){

                        myMouse.setLocked(true);
                        if (arrX == -1 || arrY == -1)
                            cerr << "__This should not happen __" << arrX << " " << arrY << "\n";
                        myMouse.setPosX(arrX);
                        myMouse.setPosY(arrY);
                    }

                }

                // if left button release
                else if (e.type == SDL_MOUSEBUTTONUP){
                    // SDL_Delay(300);

                    // if user is grabbing a piece and releasing the button
                    if (myMouse.isLocked()){

                        int arrX = -1, arrY = -1;
                        if (myMouse.getIndexPos(e.button.x, e.button.y, arrX, arrY)){
                            if (arrX != myMouse.getPosX() || arrY != myMouse.getPosY()){

                                if ( board.movePiece( myMouse.getPosX(),
                                            myMouse.getPosY(),
                                            arrX,
                                            arrY))
                                {
                                    moveMade = true;

                                }
                            }
                        }

                    }

                    // DEBUG print board
                    cout << endl;
                    for (int i = 0; i != 8; ++i){
                        for (int j = 0; j != 8; ++j){
                            if (board.getBoard()[7-i][j]->isWhite() && board.getBoard()[7-i][j]->isAlive())
                                cout << "1";
                            else if (!board.getBoard()[7-i][j]->isWhite() && board.getBoard()[7-i][j]->isAlive())
                                cout << "i";

                            else
                                cout << "0";
                        }
                        cout << endl;
                    }

                }




            } // end while SDL_PollEvent...

                if (moveMade){
                    mygui.update(board.getBoard());
                }


                // redraw board, pieces, etc
                


            // SDL_Delay(300);



        }// end while not quit

    } // end if mygui
    return EXIT_SUCCESS;
}                                                                           


