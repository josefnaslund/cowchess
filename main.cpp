#include <SDL2/SDL.h>                                                           
#include <stdio.h>                                                              
#include <iostream>                                                             
#include "constants.h"                                                          
#include "GUI.h"                                                                

using std::cout, std::endl;


int main( int argc, char* args[] )                                              
{                                                                               
    Board board = Board();                                                           

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
            }


            if (mygui.isUpdated()){
                mygui.drawBoard();
                mygui.drawPieces(board.getBoard());
            }


        }                                                                       
    }
    return EXIT_SUCCESS;
}                                                                           


