//Main game
//Main game consist of audio analyzing, hit detection, player movement, and spike placement.
#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <aubio/aubio.h>
#include <vector>
#include <string>

#include "PlayerCube.hpp" //aggregation object type Player Cube
#include "Spike.hpp" //aggregation object type Spike

using namespace std;

class Game{
public:
    //constructor loads texture used for spikes, plays audio, and initializes variables for analyzing audio
    Game(SDL_Renderer *renderer);
    ~Game();//clears memory
    int gameplay();//functionality for game
    bool setUpPlay(bool isMouseDown); //this function sets up game spikes and has their collision detection
     
private:
    SDL_Renderer *renderer;
    SDL_Texture *spikeTexture;//spike texture
    
    PlayerCube player1;//player
    vector<Spike> spike;//spike vector
    int counter;
    
    //BPM detection variables
    uint_t sampleRate,
    bufSize,
    hopSize,
    frames,
    read;
    
    aubio_source_t *source;
    fvec_t *in,
    *out;
    aubio_tempo_t *tempo;
    Mix_Music *music;
    
};

#endif /* Game_hpp */
