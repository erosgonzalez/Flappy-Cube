
#include "PlayerCube.hpp"
#include <iostream>

PlayerCube::PlayerCube(SDL_Renderer *renderer):
renderer(renderer),
cube1(loadTexture(renderer,"Cube1.bmp")),//calls function to load texture of animation one
cube2(loadTexture(renderer,"Cube2.bmp"))//calls function to load texture of animation two
{
    velocity = 0.0;//player velocity
    y = 720 / 2 -50;//height of screen set up during application class for player x postion
    x = 1280/ 4- 50;//width of screen set up diring application class for player y position
}
PlayerCube::~PlayerCube()
{
    SDL_DestroyTexture(cube1);
    SDL_DestroyTexture(cube2);
}
void PlayerCube::draw()//draws out cube to window
{
    SDL_Rect r;
    
    r.x = x - 64;
    r.y = y - 64;
    r.w = 100;
    r.h = 100; 
    
    if (SDL_GetTicks() % 350 > 150)
        SDL_RenderCopyEx(renderer, cube1, nullptr, &r, velocity * 30, nullptr, SDL_FLIP_NONE);
    else
        SDL_RenderCopyEx(renderer, cube2, nullptr, &r, velocity * 30, nullptr, SDL_FLIP_NONE);
}
void PlayerCube::move(bool isMouseDown)//function manipulates the velocity and y postion of player
{
    if (isMouseDown)//when mouse is clicked players goes up
    {
        velocity -= 0.002;
        y += velocity;
    }
    else
    {
        velocity += 0.001;
        y += velocity;
    }
}
SDL_Texture *PlayerCube::loadTexture(SDL_Renderer *renderer, const char *fileName)//loads player texture
{
    SDL_Surface *surface = SDL_LoadBMP(fileName);
    SDL_Texture *res = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    
    return res;
}
