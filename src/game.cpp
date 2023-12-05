#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, int _higherScore) :
  snake(grid_width, grid_height),
  enemy(grid_width, grid_height),
  engine(dev()),
  random_w(0, static_cast<int>(grid_width - 1)),
  random_h(0, static_cast<int>(grid_height - 1)),
  higherScore(_higherScore) {
  PlaceFood();
}

void Game::Run(Controller const& controller, Renderer& renderer,
  std::size_t target_frame_duration) {
  while (running)
  {
    frame_start = SDL_GetTicks();

    controller.HandleInput(running, snake);
    controller.HandleEnemyMove(running, enemy, food);

    Update();

    renderer.RenderSnakeAndEnemy(snake, enemy, food);

    frame_end = SDL_GetTicks();
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, higherScore);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  while (true) {
    int x = random_w(engine);
    int y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && !enemy.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();
  enemy.Update();

  auto new_x = static_cast<int>(snake.head_x);
  auto new_y = static_cast<int>(snake.head_y);

  auto enemy_new_x = static_cast<int>(enemy.head_x);
  auto enemy_new_y = static_cast<int>(enemy.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += (0.02 * Game::difficult);
  }
  else if (food.x == enemy_new_x && food.y == enemy_new_y) {
    PlaceFood();
    // Grow enemy and increase speed.
    enemy.GrowBody();
    enemy.speed += (0.005 * Game::difficult);
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }