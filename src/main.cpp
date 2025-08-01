#include "display.hpp"
#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <arm_neon.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <stdint.h>
#include <stdio.h>

bool is_running = false;

void setup(void)
{
  color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * WINDOW_WIDTH * WINDOW_HEIGHT);

  color_buffer_texture = SDL_CreateTexture(
      renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void process_input(void)
{
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type)
  {
  case SDL_QUIT:
    is_running = false;
    break;
  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_ESCAPE)
      is_running = false;
    break;
  }
}

void update(void)
{
}

void render(void)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // clear_color_buffer(0xFFFFF00);

  draw_grid(10, 0xFF333333);
  draw_rectangle(400, 600, 200, 400, 0xFFFF0000);

  render_color_buffer();
  clear_color_buffer_SIMD(color_buffer, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFF000000);

  SDL_RenderPresent(renderer);
}

int main(void)
{
  is_running = initialize_window();

  setup();

  while (is_running)
  {
    process_input();
    update();
    render();
  }

  return 0;
}
