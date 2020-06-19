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

        SDL_Event e;

        while(!quit){

            while (SDL_PollEvent (&e) != 0){
                if (e.type == SDL_QUIT){
                    quit = true;
                }

                // if left button push
                else if (SDL_GetMouseState(NULL, NULL) == 1){
                    cout << "left button press: " << e.button.x 
                        << "," << e.button.y 
                        << endl;

                    Piece* clickedPiece = board.getPieceAt(e.button.x, e.button.y);

                    if (clickedPiece && clickedPiece->isAlive()){
                            cout << "Main-  That is a piece\n";
                    }
                    else {
                        cout << "Main- There is no piece there\n";
                    }
                   

                    if (!myMouse.isLocked() && !clickedPiece){
                        cout << "Main: No piece clicked\n";
                            myMouse.setLocked(false);
                    }

                        
                }

            }


            if (mygui.isUpdated()){
                mygui.drawBoard();
                mygui.drawPieces(board.getBoard());
            }


        }                                                                       
    }
    return EXIT_SUCCESS;
}                                                                           


