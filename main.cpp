#include <SDL2/SDL.h>                                                           
#include <SDL2/SDL_ttf.h>                                                           
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

        if (TTF_Init() < 0){
            std::cerr << "init < 0: " << SDL_GetError() << endl;
        }

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

                        if (board.testMate()){
                            cout << "************************************\n";
                            cout << "*******************CHECKMATE!!!" << endl;
                            cout << "************************************\n";
                            mygui.drawTextMate();
                        }

                        else if (board.testCheck()){
                            cout << "Check!\n";
                            mygui.drawTextCheck();
                        }

                        // else test check... then mygui.drawTextCheck().
                        // move test section from GUI::drawTextCheck() to Board


                    }

                }


            } // end while SDL_PollEvent...


        }// end while not quit

    } // end if mygui
    return EXIT_SUCCESS;
}                                                                           


