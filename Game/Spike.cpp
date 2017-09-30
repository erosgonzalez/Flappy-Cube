#include "Spike.hpp"
#include <stdexcept>

Spike::Spike(SDL_Renderer *renderer, SDL_Texture *texture, float y, bool isUp): renderer(renderer), texture(texture),
y(y), isUp(isUp)
{
    x = 1280 + 128;
}
void Spike::spikeMovement()//speed at which spikes move
{
    x -= .25;
}
void Spike::draw()//draws spike to window
{
    if (!isUp)
    {
        SDL_Rect r;
        
        r.x = x - 128;
        r.y = y;
        r.w = 256;
        r.h = 720;
        
        SDL_RenderCopyEx(renderer, texture, nullptr, &r, 0, nullptr, SDL_FLIP_NONE);
    }
    else
    { 
        SDL_Rect r;
        
        r.x = x - 128;
        r.y = y - 720;
        r.w = 256;
        r.h = 720;
        
        SDL_RenderCopyEx(renderer, texture, nullptr, &r, 0, nullptr, SDL_FLIP_VERTICAL);
    }
}
SDL_Texture *Spike::loadTexture(SDL_Renderer *renderer, const char *fileName)//loads texture for spike
{
    SDL_Surface *surface = SDL_LoadBMP(fileName);
    SDL_Texture *res = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    
    return res;
}
