#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, int _higherScore) :
  snake(grid_width, grid_height),
  enemy(1, grid_height),
  engine(dev()),
  random_w(0, static_cast<int>(grid_width - 1)),
  random_h(0, static_cast<int>(grid_height - 1)),
  higherScore(_higherScore) {
  PlaceFood();
}

void Game::Run(Controller const& controller, Renderer& renderer,
  std::size_t target_frame_duration) {

  futures.emplace_back(std::async(std::launch::deferred, [&]() {
    Update(controller, renderer, target_frame_duration);
    }));
  futures.emplace_back(std::async(std::launch::async, [&]() {
    UpdateEnemy(controller, renderer, target_frame_duration);
    }));
  futures.emplace_back(std::async(std::launch::async, [&]() {
    while (running)
    {
      if (!snake.alive) break;

      if (frame_end - title_timestamp >= 1000) {
        renderer.UpdateWindowTitle(score, frame_count, higherScore);
        frame_count = 0;
        title_timestamp = frame_end;
      }
    }
    }));

  for (auto& ftr : futures) {
    ftr.wait();
  }

  renderer.~Renderer();
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) || !enemy.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update(Controller const& controller, Renderer& renderer, std::size_t target_frame_duration) {
  while (running)
  {
    if (!snake.alive) break;
    frame_start = SDL_GetTicks();

    controller.HandleInput(running, snake);

    snake.Update();

    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);

    // Check if there's food over here
    if (food.x == new_x && food.y == new_y) {
      score++;
      PlaceFood();
      // Grow snake and increase speed.
      snake.GrowBody();
      snake.speed += (0.02 * Game::difficult);
    }

    renderer.RenderSnake(snake, food);

    frame_end = SDL_GetTicks();
    frame_count++;
    frame_duration = frame_end - frame_start;

    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::UpdateEnemy(Controller const& controller, Renderer& renderer, std::size_t target_frame_duration) {
  while (running)
  {
    if (!snake.alive) break;

    enemy.Update();

    int new_x = static_cast<int>(enemy.head_x);
    int new_y = static_cast<int>(enemy.head_y);

    // Check if there's food over here
    if (food.x == new_x && food.y == new_y) {
      PlaceFood();
      // Grow enemy and increase speed.
      enemy.GrowBody();
    }

    renderer.RenderEnemy(enemy, food);

    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }