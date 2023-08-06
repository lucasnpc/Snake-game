#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "score.h"

int main() {
  constexpr std::size_t kFramesPerSecond{ 60 };
  constexpr std::size_t kMsPerFrame{ 1000 / kFramesPerSecond };
  constexpr std::size_t kScreenWidth{ 640 };
  constexpr std::size_t kScreenHeight{ 640 };
  constexpr std::size_t kGridWidth{ 32 };
  constexpr std::size_t kGridHeight{ 32 };

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  Score score;
  game.Run(controller, renderer, kMsPerFrame, score.getHighestScore());
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  std::cout << "Do you wanna save your score? (y/n) " << std::endl;
  std::string opt;
  std::cin >> opt;
  if (opt == "y")
  {
    score.saveScore(game.GetScore());
  }

  return 0;
}