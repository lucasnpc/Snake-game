#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include "snake.h"
#define printVariableNameAndValue(x) std::cout<<"The name of variable **"<<(#x)<<"** and the value of variable is => "<<x<<"\n"

class Controller {
public:
    void HandleInput(bool& running, Snake& snake) const;
    void HandleEnemyMove(bool& running, Snake& enemy, SDL_Point& food) const;

private:
    void ChangeDirection(Snake& snake, Snake::Direction input,
        Snake::Direction opposite) const;
};

#endif