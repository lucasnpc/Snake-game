#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include "game.h"

class MenuItem {
    const std::string text;
public:
    MenuItem(std::string _text) : text(_text) {};
    std::string GetText() { return text; };
};

class Menu {
    std::vector<MenuItem> items;
    void BuildMenu();
    void ReceiveUserInput();
    void ChooseDifficult();
    bool start = false;
    std::mutex _mutex;
    std::condition_variable _cond;
public:
    Menu();
    void waitForStartGame();

    bool quit = false;
};

#endif