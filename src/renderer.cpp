#include "renderer.h"
#include <iostream>
#include <string>
#include <memory>

Renderer::Renderer(const std::size_t screen_width,
  const std::size_t screen_height,
  const std::size_t grid_width, const std::size_t grid_height)
  : screen_width(screen_width),
  screen_height(screen_height),
  grid_width(grid_width),
  grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = std::unique_ptr<SDL_Window, SDLWindowDeleter>(SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, screen_width,
    screen_height, SDL_WINDOW_SHOWN));

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = std::unique_ptr<SDL_Renderer, SDLRendererDeleter>(SDL_CreateRenderer(sdl_window.get(), -1, SDL_RENDERER_ACCELERATED));
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_Quit();
}

void Renderer::Render(Snake const snake, Snake const enemy, SDL_Point const& food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer.get(), 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer.get());

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer.get(), &block);

  RenderSnake(snake, block);
  RenderEnemy(enemy, block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer.get());
}

void Renderer::UpdateWindowTitle(int score, int fps, int higherScore) {
  std::string title = higherScore != 0 ? "Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps) + " Higher Score: " + std::to_string(higherScore)
    : "Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps);
  SDL_SetWindowTitle(sdl_window.get(), title.c_str());
}

void Renderer::RenderSnake(Snake const snake, SDL_Rect block) {
  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const& point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer.get(), &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer.get(), 0x00, 0x7A, 0xCC, 0xFF);
  }
  else {
    SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer.get(), &block);
}

void Renderer::RenderEnemy(Snake const enemySnake, SDL_Rect block) {
  //Render Enemy Snake Body
  for (SDL_Point const& point : enemySnake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer.get(), &block);
  }

  // Render enemy's head
  block.x = static_cast<int>(enemySnake.head_x) * block.w;
  block.y = static_cast<int>(enemySnake.head_y) * block.h;
  SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderFillRect(sdl_renderer.get(), &block);
}
