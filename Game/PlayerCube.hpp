//Player class
#ifndef PlayerCube_hpp
#define PlayerCube_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

class PlayerCube{
public:
    PlayerCube(SDL_Renderer *renderer);//loads player texture
    ~PlayerCube();
    void move(bool isMouseDown);//player movement
    void draw();//draws out cube to window
    SDL_Texture *loadTexture(SDL_Renderer *, const char *fileName);
    
    //accessors
    float getY() {return y;}
    float getX() {return x;}

private:
    SDL_Renderer *renderer;
    SDL_Texture *cube1;//animation one
    SDL_Texture *cube2;//animation two
    
    float velocity;
    float y;
    float x;

    
};

#endif /* PlayerCube_hpp */

