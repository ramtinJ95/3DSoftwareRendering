#include "display.hpp"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
uint32_t *color_buffer = NULL;
SDL_Texture *color_buffer_texture = NULL;
int WINDOW_WIDTH = 1920;
int WINDOW_HEIGHT = 1080;

bool initialize_window(void)
{
  if (SDL_Init(SDL_INIT_EVERYTHING != 0))
  {
    fprintf(stderr, "Error initializing SDL.\n");
    return false;
  }
  window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                            WINDOW_HEIGHT, SDL_WINDOW_INPUT_GRABBED);
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

void destroy_window(void)
{
  free(color_buffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void clear_color_buffer(uint32_t color)
{
  int num_pixels = WINDOW_HEIGHT * WINDOW_WIDTH;
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

void draw_grid(int spacing, uint32_t grid_color)
{
  // horizontal lines
  for (int i = 0; i < WINDOW_HEIGHT; i += spacing)
  {
    for (int j = 0; j < WINDOW_WIDTH; j++)
    {
      color_buffer[i * WINDOW_WIDTH + j] = grid_color;
    }
  }
  // vertical lines
  for (int j = 0; j < WINDOW_WIDTH; j += spacing)
  {
    for (int i = 0; i < WINDOW_HEIGHT; i++)
    {
      color_buffer[i * WINDOW_WIDTH + j] = grid_color;
    }
  }
}

void draw_rectangle(int x_pos, int y_pos, int width, int height, uint32_t color)
{
  for (int y = y_pos; y < y_pos + height; y++)
  {
    for (int x = x_pos; x < x_pos + width; x++)
    {
      draw_pixel(x, y, color);
    }
  }
}

void render_color_buffer(void)
{
  SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer,
                    (int)(WINDOW_WIDTH * sizeof(uint32_t)));
  SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}
