#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include <memory>
#include <mutex>

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

  void UpdateWindowTitle(int score, int fps, int higherScore);
  void RenderSnakeAndEnemy(Snake const& snake, Snake const& enemy, SDL_Point const& food);
private:
  std::unique_ptr<SDL_Window, SDLWindowDeleter> sdl_window;
  std::unique_ptr<SDL_Renderer, SDLRendererDeleter> sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
  std::mutex _mutex;
};

#endif