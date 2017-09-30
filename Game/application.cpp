
#include "application.hpp"

Application::Application()
{
    //Initialze SDL for game.
    SDL_Init(SDL_INIT_EVERYTHING);

    //Creates game window from member variables height and width.
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, NULL, &window, &renderer);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetWindowPosition(window, 65, 126);
    
    //Initializes audio for game.
    SDL_Init(SDL_INIT_AUDIO);
}
int Application::run()
{ 
    
    while (true)//main game loop
    {
        Game g(renderer);
        
        if (g.gameplay() == 0)
            break;
    }
    return 0;

}


