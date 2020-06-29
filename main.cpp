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

                // else if keyboard actions...

                else {
                    moveMade = myMouse.mouseEvents(e, board);
                        
                }


            } // end while SDL_PollEvent...

                if (moveMade){
                    mygui.update(board.getBoard());
                }

        }// end while not quit

    } // end if mygui
    return EXIT_SUCCESS;
}                                                                           


