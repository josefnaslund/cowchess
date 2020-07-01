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

    GUI mygui = GUI(&board);

    if (mygui.init()){
        SDL_Delay(100);

        SDL_Event e;

        mygui.update();

        while(!quit){

            while (SDL_PollEvent (&e) != 0){
                if (e.type == SDL_QUIT){
                    quit = true;
                }

                // else if keyboard actions...

                else {
                    if (myMouse.mouseEvents(e, board)){
                        mygui.update();
                            
                    }
                        
                }


            } // end while SDL_PollEvent...


        }// end while not quit

    } // end if mygui
    return EXIT_SUCCESS;
}                                                                           


