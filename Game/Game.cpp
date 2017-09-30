
#include "Game.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>

Game::Game(SDL_Renderer *renderer) : renderer(renderer), spikeTexture(Spike::loadTexture(renderer, "spike.bmp")), player1(renderer)
{
    srand(time(NULL));
    
    //music playlist initializing for both playing SDL_MIXER and aubio library
    const char_t *musicPlaylist[5] = {"Nujabes feat. Shing02 - Luv(sic) Part 4 - 2011.wav", "_11615.wav", "Guru  - Jazzmatazz -  Down The Backstreets.wav", "Stand Up Guru feat Damian Marley.wav", "Nujabes - Luv(Sic.) Pt. 2.wav"};
    
    int i = rand()% 5;
    
    const char_t *sourcePath = musicPlaylist[i];//aubio var
    
    //SDL Music play
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    music = Mix_LoadMUS(musicPlaylist[i]);
    Mix_PlayMusic(music, -1);
    
    //Sets up beat detection variables
    bufSize = 1024;
    hopSize = 256;
    frames = 0;
    read = 0;
    counter = 0;
    
    //the following functions are part of the aubio library
    //which allows for audio analyzing.
    //theses functions are used to detect the BPM for a given song
    
    source = new_aubio_source(sourcePath, 0, hopSize);
    
    sampleRate = aubio_source_get_samplerate(source);
    in = new_fvec(hopSize);
    out = new_fvec(1);
    
    tempo = new_aubio_tempo("default", bufSize, hopSize, sampleRate);

}
Game::~Game()//deconstructor
{
    SDL_DestroyTexture(spikeTexture);
    Mix_FreeMusic(Game::music);
    Mix_CloseAudio();
    
    del_aubio_tempo(tempo);
    del_fvec(in);
    del_fvec(out);
    del_aubio_source(source);
    aubio_cleanup();
}
bool Game::setUpPlay(bool isMouseDown) //this function sets up game spikes and has their collision detection
{
    //allows for spikes to render continuously
    if (counter++ % 2000 == 0)
    {
        aubio_source_do(source, in, &read);
        aubio_tempo_do(tempo, in, out);
        
        //this creates a random height for the spikes based off the song BPM.
        //720 being the windo height the other numbers make sure spikes are not fully off screen
        float y = rand() % (720 - 200 - 250 - 100) + aubio_tempo_get_bpm(tempo);
        
        //puts spikes in a vector. This calls the overloaded spike constructor
        spike.emplace_back(renderer, spikeTexture, y + 300, false);//spike is down
        spike.emplace_back(renderer, spikeTexture, y + 100, true);//spike is up
        
        frames += read;//audio frames
    }

    player1.move(isMouseDown);
    
    //collision set up. sets rectangel around player for detection
    SDL_Rect playerRect;
    playerRect.x = player1.getX() - 90 / 2;
    playerRect.y =player1.getY()- 80 / 2;
    playerRect.w = 90;
    playerRect.h = 80;
    
    SDL_Rect res;
    for(Spike &s: spike)//vector for loop
    {
        s.spikeMovement();//movement for spikes
        
        //rectangle set up for spikes to detect collision via SDL_IntersectRect function
        SDL_Rect spikeRect;
        spikeRect.x = s.getX() - 128 + 120;
        spikeRect.w = 20;
        spikeRect.h = 10000;
        
        if (s.getIsUp())//check spike above
        {
            spikeRect.y = s.getY() - 10000;
            if(SDL_IntersectRect(&playerRect, &spikeRect, &res))
                return false;
            
        }
        else//spike below
        {
            spikeRect.y = s.getY() + 20;
            if(SDL_IntersectRect(&playerRect, &spikeRect, &res))
                return false;
            
        }
        
        //deletes spike from vector once passed a certain point of window
        for (vector<Spike>::iterator i = spike.begin() ; i != spike.end(); ++i)
        {
            if ((*i).getX() < -128)
                i = spike.erase(i);
        }
    }

    return player1.getY() < 720;

}
int Game::gameplay()//functionality for game. Player clicks, background color
{
    unsigned int oldTick = SDL_GetTicks();//time passed in milliseconds
    bool isMouseDown = false;//if mouse is clicked
    bool done = false;
    
    //Event processing for mouse click
    while(!done)
    {
        //Mouse click detection 
        SDL_Event e;
        if (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_MOUSEBUTTONDOWN://mouse is being clicked
                    isMouseDown = true;
                    break;
                case SDL_MOUSEBUTTONUP://mouse is not being clicked
                    isMouseDown = false;
                    break;
                case SDL_QUIT://mouse click exit button
                    done = true;
                    break;
            }
        }
        
        for (int i = oldTick; i < SDL_GetTicks(); ++i)
        {
            if (!setUpPlay(isMouseDown))
                return 1;
        }
        oldTick = SDL_GetTicks();
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);//background
        SDL_RenderClear(renderer);
        player1.draw();
        
        for(Spike &s: spike)
            s.draw();
        
        SDL_RenderPresent(renderer);
    }

    return 0;
}

