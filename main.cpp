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

    bool quit = false;

    GUI mygui = GUI();

    if (mygui.init()){
        // SDL_Delay(5000);

        SDL_Event e;

        bool moveMade;

        while(!quit){
            // cout << "\t\t\t\t" << counter++ << endl;
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

                        myMouse.setLocked(true);
                        if (arrX == -1 || arrY == -1)
                            cout << "__This should not happen ___________" << arrX << " " << arrY << "\n";
                        myMouse.setPosX(arrX);
                        myMouse.setPosY(arrY);
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
                    // SDL_Delay(300);

                    // if user is grabbing a piece and releasing the button
                    if (myMouse.isLocked()){
                        cout << "Button UP! maybe lets try moving piece!?\n"; 

                        int arrX = -1, arrY = -1;
                        if (myMouse.getIndexPos(e.button.x, e.button.y, arrX, arrY)){
                            if (arrX != myMouse.getPosX() || arrY != myMouse.getPosY()){

                                cout << arrX << "," << myMouse.getPosX() << "," <<
                                    arrY << "," << myMouse.getPosY() << endl;
                                cout << "Dragged to different pos\n";

                                if ( board.movePiece( myMouse.getPosX(),
                                            myMouse.getPosY(),
                                            arrX,
                                            arrY))
                                {
                                    cout << "updating gui\n";
                                    moveMade = true;

                                }
                            }

                            else {
                                cout << "Dragged to same pos\n";
                            }


                        }

                    }

                    // if user is 
                    else if (!myMouse.isLocked()){
                        cout << "Just a dead release button\n";
                    }


                    // DEBUG print board
                    cout << endl;
                    for (int i = 0; i != 8; ++i){
                        for (int j = 0; j != 8; ++j){
                            if (board.getBoard()[7-i][j].isWhite() && board.getBoard()[7-i][j].isAlive())
                                cout << "1";
                            else if (!board.getBoard()[7-i][j].isWhite() && board.getBoard()[7-i][j].isAlive())
                                cout << "i";

                            else
                                cout << "0";
                        }
                        cout << endl;
                    }

                    cout << "---END MOUSEBUTTONUP---\n";
                }




            } // end while SDL_PollEvent...

                if (moveMade){
                    //SDL_Delay(300);
                    mygui.setUpdated(true);
                    // SDL_Delay(200);
                }

                if (mygui.isUpdated()){
                    // SDL_Delay(200);
                    cout << "**Drawing board\n";
                    mygui.drawBoard();
                    cout << "**Drawing pieces\n";
                    mygui.drawPieces(board.getBoard());
                    // SDL_Delay(200);
                    mygui.setUpdated(false);
                }


            // SDL_Delay(300);



        }// end while not quit

    } // end if mygui
    return EXIT_SUCCESS;
}                                                                           


