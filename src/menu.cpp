#include "menu.h"

Menu::Menu() {
    items.emplace_back(MenuItem("1. Init Game"));
    items.emplace_back(MenuItem("2. Choose Difficult"));
    items.emplace_back(MenuItem("3. About Game"));
    items.emplace_back(MenuItem("4. Quit Game"));
    BuildMenu();
}

void Menu::BuildMenu() {
    std::cout << "\033[2J\033[1;1H";

    std::cout << "SnakeGame Menu" << "\n\n";

    for (auto& item : items) {
        std::cout << item.GetText() << "\n";
    }

    std::cout << "\n\nEnter an option: \n";
}

void Menu::waitForStartGame() {
    while (true)
    {
        ReceiveUserInput();
        if (quit || start)
        {
            break;
        }
    }
}

void Menu::ReceiveUserInput() {
    std::lock_guard<std::mutex> lock(_mutex);

    std::string opt = "0";
    std::cin >> opt;

    if (opt == "1")
    {
        start = true;
    }
    else if (opt == "2") {
        ChooseDifficult();
        BuildMenu();
    }
    else if (opt == "4") {
        quit = true;
    }
    else {
        std::cout << "\033[1A";
        std::cout << "\033[2K";
    }
    _cond.notify_one();
}

void Menu::ChooseDifficult() {
    std::string input;
    std::cout << "\033[2J\033[1;1H";

    std::cout << "Choose Game Difficult: " << "\n\n";
    std::cout << "1. Easy (Speed in 50%)" << "\n";
    std::cout << "2. Normal (Speed in 100%)" << "\n";
    std::cout << "3. Hard (Speed in 150%)" << "\n";

    std::cout << "\nInput: " << "\n";
    while (true)
    {
        std::cin >> input;

        if (input == "1")
        {
            Game::difficult = 0.5;
            break;
        }
        else if (input == "2") {
            Game::difficult = 1;
            break;
        }
        else if (input == "3") {
            Game::difficult = 1.5;
            break;
        }
        else {
            std::cout << "\033[1A";
            std::cout << "\033[2K";
        }
    }
}