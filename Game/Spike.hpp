//Spike class
//Spike class allows for the game to load spike and has spike functionality.

#ifndef Spike_hpp
#define Spike_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

class Spike{
public:
    Spike(SDL_Renderer *renderer, SDL_Texture *texture, float y, bool isUp);
    void spikeMovement();//speed at which spikes move
    void draw();//draws spike to window
    static SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *fileName);//loads spike texture
    
    //accessors
    float getX() const {return x;}
    float getY() const {return y;}
    bool getIsUp() const {return isUp;}

private:
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    
    //spike x,y position, and whether it is on the bottom axis of the windo or top axis
    float x;
    float y;
    bool isUp;
};
 
#endif /* Spike_hpp */

