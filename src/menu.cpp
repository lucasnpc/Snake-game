#include "menu.h"

Menu::Menu() {
    items.emplace_back(MenuItem("1. Init Game"));
    items.emplace_back(MenuItem("2. Choose Difficult"));
    items.emplace_back(MenuItem("3. About Game"));
    items.emplace_back(MenuItem("4. Quit Game"));

    std::cout << "SnakeGame Menu" << "\n\n";

    for (auto& item : items) {
        std::cout << item.GetText() << "\n";
    }
}

void Menu::waitForStartGame() {
    int opt = 0;
    std::cout << "\n\nEnter an option: \n";
    while (true)
    {
        std::cin >> opt;

        if (opt == 1)
        {
            break;
        }
        else if (opt == 4) {
            quit = true;
            break;
        }

        switch (opt)
        {
        case 2:
            break;
        case 3:
            break;
        default:
            std::cout << "\033[1A";
            std::cout << "\033[2K";
            break;
        }

    }

}