//Class defines the appilication which has a game object.
//The class sets up the window for the game and creates game object.

#ifndef application_hpp
#define application_hpp

#include <SDL2/SDL.h>

#include <iostream>
#include <string>
#include <stdio.h>

#include "Game.hpp" //aggregation for creating Game object.

using namespace std;

class Application{
public:
    Application(); //default constructor initializes SDL game window and audio
    int run(); //main function that creates Game object and runs game
    
private:
    SDL_Window *window; 
    SDL_Renderer *renderer;
    
    //size of window
    const int WIDTH = 1280;
    const int HEIGHT = 720;

};

#endif /* application_hpp */


