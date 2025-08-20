#pragma once

#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <arm_neon.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <stdint.h>
#include <stdio.h>

inline constexpr int FPS = 60;
inline constexpr float FRAME_TARGET_TIME = 1000.0f / FPS;
inline constexpr int WINDOW_WIDTH = 1920;
inline constexpr int WINDOW_HEIGHT = 1080;

enum class Cull_method
{
  cull_none,
  cull_backface
};

enum class Render_method
{
  render_wire,
  render_wire_vertex,
  render_fill_triangle,
  render_fill_triangle_wire
};

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern uint32_t *color_buffer;
extern SDL_Texture *color_buffer_texture;

bool initialize_window(void);
void draw_grid(int spacing, uint32_t grid_color);
void draw_rectangle(int x_pos, int y_pos, int width, int height, uint32_t color);
void draw_line(int x0, int y0, int x1, int y1, uint32_t color);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void render_color_buffer(void);
void clear_color_buffer(uint32_t color);
void clear_color_buffer_SIMD(uint32_t *buffer, size_t width, size_t height, uint32_t color);
void destroy_window(void);

inline void draw_pixel(int x_pos, int y_pos, uint32_t color)
{
  if (x_pos >= 0 && x_pos < WINDOW_WIDTH && y_pos >= 0 && y_pos < WINDOW_HEIGHT)
  {
    color_buffer[(y_pos * WINDOW_WIDTH) + x_pos] = color;
  }
}
