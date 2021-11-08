#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Block.h"
#include "Ball.h"
#include "Physic.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 600), "Ping pong");
    BLOCK::PlayerBlock block(sf::Vector2f(50, 10), sf::Vector2f(200, 500), 400, 0);
    PHYSIC::IPhysicObject* physObj = &block;
    BALL::Ball ball(5, sf::Vector2f(200, 485), 400, 0, 600, 0, physObj, 1);
    ball.setDirection(sf::Vector2f(0.5f, -0.5f));
    

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
        window.draw(block);
        window.draw(ball);
        window.display();
    }

    return 0;
}