#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"
#include "a-star.h"

void Controller::ChangeDirection(Snake& snake, Snake::Direction input,
  Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(bool& running, Snake& snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    }
    else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
      case SDLK_UP:
        ChangeDirection(snake, Snake::Direction::kUp,
          Snake::Direction::kDown);
        break;

      case SDLK_DOWN:
        ChangeDirection(snake, Snake::Direction::kDown,
          Snake::Direction::kUp);
        break;

      case SDLK_LEFT:
        ChangeDirection(snake, Snake::Direction::kLeft,
          Snake::Direction::kRight);
        break;

      case SDLK_RIGHT:
        ChangeDirection(snake, Snake::Direction::kRight,
          Snake::Direction::kLeft);
        break;
      }
    }
  }
}

void Controller::HandleEnemyMove(bool& running, Snake& enemy, SDL_Point& food) const {
  int init[2]{ static_cast<int>(enemy.head_x), static_cast<int>(enemy.head_y) };
  int goal[2]{ food.x, food.y };
  std::vector<std::vector<State>> grid;
  for (int i = 0; i < 32; ++i)
  {
    std::vector<State> line;
    for (int j = 0; j < 32; ++j) {
      line.emplace_back(State::kEmpty);
    }
    grid.emplace_back(line);
  }

  auto solution = Search(grid, init, goal);
  for (size_t x = 0; x < solution.size(); ++x)
  {
    for (size_t y = 0; y < solution[x].size(); ++y)
    {
      if (isNeighbor(enemy.head_x, enemy.head_y, x, y) && solution[x][y] == State::kPath) {
        if (x >= static_cast<int>(enemy.head_x)) {
          ChangeDirection(enemy, Snake::Direction::kRight,
            Snake::Direction::kLeft);
          break;
        }
        else if (x <= static_cast<int>(enemy.head_x)) {
          ChangeDirection(enemy, Snake::Direction::kLeft,
            Snake::Direction::kRight);
          break;
        }
        else if (y >= static_cast<int>(enemy.head_y)) {
          ChangeDirection(enemy, Snake::Direction::kDown,
            Snake::Direction::kUp);
          break;
        }
        else if (y <= static_cast<int>(enemy.head_y)) {
          ChangeDirection(enemy, Snake::Direction::kUp,
            Snake::Direction::kDown);
          break;
        }
      }
    }
  }
}