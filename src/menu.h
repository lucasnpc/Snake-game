#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <iostream>

class MenuItem {
    const std::string text;
public:
    MenuItem(std::string _text) : text(_text) {};
    std::string GetText() { return text; };
};

class Menu {
    std::vector<MenuItem> items;
public:
    Menu();
    void waitForStartGame();

    bool quit = false;
};

#endif