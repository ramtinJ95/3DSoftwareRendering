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
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
uint32_t *color_buffer = NULL;
int window_width = 1920;
int window_height = 1080;
SDL_Texture *color_buffer_texture = NULL;

bool initialize_window(void)
{
  if (SDL_Init(SDL_INIT_EVERYTHING != 0))
  {
    fprintf(stderr, "Error initializing SDL.\n");
    return false;
  }
  window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            window_width, window_height, SDL_WINDOW_INPUT_GRABBED);
  if (!window)
  {
    fprintf(stderr, "Error creating sdl window");
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer)
  {
    fprintf(stderr, "Error creating SDL renderer");
    return false;
  }

  return true;
}

void setup(void)
{
  color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);

  color_buffer_texture = SDL_CreateTexture(
      renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
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

void destroy_window(void)
{
  free(color_buffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void clear_color_buffer(uint32_t color)
{
  int num_pixels = window_height * window_width;
  for (uint32_t i = 0; i < num_pixels; i++)
  {
    color_buffer[i] = color;
  }
}

/*
The last for loop is for the fallback case, if the color buffer is of a size
that is not evenly divisable with 4. This should be fast enough for this learning
code, not going to bother going into multithreading and dividing up sections of the
color buffer

[ buffer ]
   ↓
+--------+--------+--------+--------+--------+--------+--------+--------+ ...
|  pixel |  pixel |  pixel |  pixel |  pixel |  pixel |  pixel |  pixel | ...
+--------+--------+--------+--------+--------+--------+--------+--------+
     ← fillColor (4 at once) ←       ← fillColor       ← fallback loop

*/
void clear_color_buffer_SIMD(uint32_t *buffer, size_t width, size_t height, uint32_t color)
{
  size_t count = width * height;
  size_t i = 0;

  uint32x4_t fillColor = vdupq_n_u32(color);

  for (; i + 4 <= count; i += 4)
  {
    vst1q_u32(&buffer[i], fillColor);
  }

  for (; i < count; i++)
  {
    buffer[i] = color;
  }
}

void render_color_buffer(void)
{
  SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer,
                    (int)(window_width * sizeof(uint32_t)));
  SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void render(void)
{
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);

  // clear_color_buffer(0xFFFFF00);
  render_color_buffer();
  clear_color_buffer_SIMD(color_buffer, window_width, window_height, 0xFFFFF00);

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
