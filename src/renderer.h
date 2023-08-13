#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include <memory>

struct SDLWindowDeleter {
  void operator()(SDL_Window* window) const {
    SDL_DestroyWindow(window);
  }
};

struct SDLRendererDeleter {
  void operator()(SDL_Renderer* renderer) const {
    SDL_DestroyRenderer(renderer);
  }
};

class Renderer {
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
    const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, Snake const enemySnake, SDL_Point const& food);
  void UpdateWindowTitle(int score, int fps, int higherScore);

  void RenderSnake(Snake const snake, SDL_Rect block);
  void RenderEnemy(Snake const enemy, SDL_Rect block);

private:
  std::unique_ptr<SDL_Window, SDLWindowDeleter> sdl_window;
  std::unique_ptr<SDL_Renderer, SDLRendererDeleter> sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif