#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "Block.h"
#include "Ball.h"
#include "Physic.h"

const float WindowWidth = 400;
const float WindowHeight = 600;
const int BlocksPerLine = 10;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "Ping pong");

    BLOCK::PlayerBlock block(sf::Vector2f(50, 10), sf::Vector2f(200, 500), 400, 0);

    std::vector<PHYSIC::IPhysicObject*> physObj;
    
    float blocksWidth = WindowWidth / BlocksPerLine;
    float blocksHeight = 10;
    bool nowRed = true;
    for (size_t i = 0; i < BlocksPerLine; i++)
    {
        for (int j = 0; j < 5; j++) {
            BLOCK::DestoyingBlock* destrBlock = new BLOCK::DestoyingBlock(sf::Vector2f(i * blocksWidth + blocksWidth / 2, j * 10 + 5), sf::Vector2f(blocksWidth, blocksHeight), 10);
            if (nowRed) {
                (*destrBlock).setFillColor(sf::Color::Red);
                nowRed = false;
            }
            else {
                (*destrBlock).setFillColor(sf::Color::Blue);
                nowRed = true;
            }
            physObj.push_back(destrBlock);
        }
    }

    physObj.push_back(&block);

    BALL::Ball ball(5, sf::Vector2f(200, 485), 400, 0, 600, 0, &physObj, 2);
    ball.setDirection(sf::Vector2f(0.5f, -0.5f));
    ball.setFillColor(sf::Color::Blue);
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                block.move(sf::Vector2f(-20, 0));

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                block.move(sf::Vector2f(20, 0));
        }

        ball.move();

        window.clear();
        window.draw(ball);
        window.draw(block);
        for (auto obj : physObj) {
            if (obj != NULL)
                window.draw(*dynamic_cast<sf::Shape*>(obj));
        }
        window.display();

        for (int i = 0; i < physObj.size(); i++)
        {
            BLOCK::DestoyingBlock* destBlock = dynamic_cast<BLOCK::DestoyingBlock*>(physObj[i]);
            if (destBlock != NULL) {
                if (destBlock->getHP() <= 0) {
                    delete physObj[i];
                    physObj.erase(physObj.cbegin() + i);
                }
            }
        }
    }

    for (int i = 0; i < physObj.size()-1; i++)
    {
        std::cout << "\n\nDeleting physic object # " << i << " " << std::endl;
        if (physObj[i] != NULL)
            delete physObj[i];
    }

    return 0;
}