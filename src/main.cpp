#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "score.h"
#include "menu.h" 

float Game::difficult = 1;

void executeGame() {
  constexpr std::size_t kFramesPerSecond{ 60 };
  constexpr std::size_t kMsPerFrame{ 1000 / kFramesPerSecond };
  constexpr std::size_t kScreenWidth{ 1280 };
  constexpr std::size_t kScreenHeight{ 720 };
  constexpr std::size_t kGridWidth{ 32 };
  constexpr std::size_t kGridHeight{ 32 };
  std::future<void> ftr;
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Score score;
  Game game(kGridWidth, kGridHeight, score.getHighestScore());
  game.Run(controller, renderer, kMsPerFrame);

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
}

int main() {

  Menu menu;
  menu.waitForStartGame();
  if (!menu.quit)
  {
    std::cout << "\033[2J\033[1;1H";
    executeGame();
  }

  return 0;
}