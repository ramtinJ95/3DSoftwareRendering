#include <SDL2/SDL.h>
#include <SDL_video.h>
#include <iostream>
#include <stdio.h>

bool is_running = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool initialize_window(void){
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Error setting up SDL. \n";
    return false;
  }

  window = SDL_CreateWindow("SFML", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_BORDERLESS);
  if(!window) {
    std::cerr << "Error setting up SDL Window";
    return false;
  }
  
  renderer = SDL_CreateRenderer(window, -1, 0);
   if(!renderer) {
    std::cerr << "Error setting up SDL renderer";
    return false;
  }
  return true;
}

int main(void) {
  is_running = initialize_window();
  return 0;
}
