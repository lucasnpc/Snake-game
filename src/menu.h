#ifndef MENU_H
#define MENU_H

#include <string>

class MenuItem {
    const std::string text;
public:
    MenuItem(SDL_Rect _rect, std::string _text) : text(_text) {};
    std::string GetText() { return text; };
};

#endif