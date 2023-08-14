#ifndef GAME_H
#define GAME_H

#include <random>
#include <future>
#include <vector>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
public:
  Game(std::size_t grid_width, std::size_t grid_height, int higherScore);
  void Run(Controller const& controller, Renderer& renderer,
    std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  static float difficult;

private:
  Snake snake, enemy;
  SDL_Point food;
  std::vector<std::future<void>> futures;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{ 0 };
  int higherScore{ 0 };

  void PlaceFood();
  void Update(Controller const& controller, Renderer& renderer, std::size_t target_frame_duration);
  void UpdateEnemy(Controller const& controller, Renderer& renderer, std::size_t target_frame_duration);

  bool running = true;
  Uint32 frame_start, frame_end, frame_duration;
  int frame_count = 0;
  Uint32 title_timestamp = SDL_GetTicks();
};

#endif