//The main cpp file creates an Application object.
//It calls the main game loop for animations, controls,
//obstacles, music, in application class.
//
//The game is a combination of Flappy Bird and The Impossible Game.
//The aspect of avoiding pipes, like in flapy bird, is used.
//The aspect of using music as a way for the level to run is used, like in The Impossible Game.
//The level is generated based off the BPM of background music.
#include <SDL2/SDL.h>
#include "application.hpp"

int main(int arg, const char **argv)
{
    Application app; //default constructor intializes SDL Window and SDL Audio
    
    app.run();
     
    return 0;
}
