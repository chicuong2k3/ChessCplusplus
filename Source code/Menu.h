#pragma once

#include <SFML/Graphics.hpp>
#include "Settings.h"
#include <iostream>

class Menu
{
private:
    sf::RenderWindow* window;
    sf::Sprite backgroundSprite;
    std::vector<const char*> urls;
    std::vector<sf::Sprite> items;
	int itemWidth;
	int itemHeight;
public:
	Menu(sf::RenderWindow* wind) {
        itemWidth = 300;
        itemHeight = 80;
        window = wind;
    }

    void drawBackground() {
        sf::Texture background;
        background.loadFromFile(Settings::menuBackgroundURL);
        sf::Sprite backgroundSprite;
        backgroundSprite.setTexture(background);
        backgroundSprite.setScale((float)window->getSize().x / background.getSize().x, (float)window->getSize().y / background.getSize().y);
        window->draw(backgroundSprite);
    }

    void addButton(const char* url) {
        urls.push_back(url);
        sf::Texture buttonTexture1;
        buttonTexture1.loadFromFile(url);
        sf::Sprite button1;
        button1.setTexture(buttonTexture1);
        button1.setScale((float)itemWidth / buttonTexture1.getSize().x, (float)itemHeight / buttonTexture1.getSize().y);
        button1.setPosition(window->getSize().x / 2 - itemWidth / 2, window->getSize().y / 3 + items.size() * (itemHeight + 10));
        items.push_back(button1);
    }

	void drawButton() {
        for (int i = 0; i < items.size(); i++)
        {
            sf::Texture buttonTexture1;
            buttonTexture1.loadFromFile(urls[i]);
            items[i].setTexture(buttonTexture1);
            window->draw(items[i]);
        }
    }

    int runMenu() {
        while (window->isOpen())
        {
            sf::Event event;
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window->close();
                }
                else if (event.type == sf::Event::MouseButtonPressed)
                {
                    for (int i = 0; i < items.size(); i++)
                    {
                        if (event.mouseButton.button == sf::Mouse::Left &&
                            items[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                        {
                            return i + 1;
                        }
                    }
                }
                else if (event.type == sf::Event::MouseMoved)
                {
                   
                    for (int i = 0; i < items.size(); i++)
                    {
                        if (items[i].getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
                        {
                           
                            //items[i].setTexture(hoverTexture);
                        }
                        else
                        {
                            
                           // items[i].setTexture(defaultTexture);
                        }
                    }
                }
            }

            window->clear();
            drawBackground();
            drawButton();
            window->display();
        }
    }
};

