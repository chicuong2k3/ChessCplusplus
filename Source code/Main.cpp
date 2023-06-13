#include "Game.h"
#include "SFML/Graphics.hpp"
#include "Settings.h"
#include "Menu.h"
#include "Music.h"
#include <thread>
#include <windows.h>

int main()
{
    // Tạo cửa sổ game
    sf::RenderWindow window(sf::VideoMode(Settings::screenWidth, Settings::screenHeight), Settings::screenTitle, (sf::Style::Titlebar | sf::Style::Close) & ~sf::Style::Resize);
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
    bool con = false;
    Music themeSong;
    std::thread musicThread([&themeSong]() {
        themeSong.playMusic(Settings::themeMusicURL, true);
        });
    do
    {
        
        Menu menu(&window);
        menu.addButton(Settings::menuItem1);
        menu.addButton(Settings::menuItem2);
        menu.addButton(Settings::menuItem3);
        int choice = menu.runMenu();
        if (choice == 1 || choice == 2) {
            Game game(&window, choice);
            con = game.play();
        }
        else if (choice == 3) {
            window.close();
        }

    } while (con);
    musicThread.join();

    return 0;
}