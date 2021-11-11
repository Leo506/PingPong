#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "Block.h"
#include "Ball.h"
#include "Physic.h"
#include "Settings.h"
#include "UI.h"
#include "Game.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ping pong");

    // Вектор указателей на все физические объекты
    std::vector<PHYSIC::IPhysicObject*> physObj;

    UI::UIController uiController;

    GAME::GameController gameController;

    // Блок, которым управляет игрок (размер, стартовая позиция, максимальное и минимальное значение по X
    BLOCK::PlayerBlock block(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT), sf::Vector2f((WINDOW_WIDTH - OFFSET) / 2, 500), WINDOW_WIDTH, OFFSET);

    // Создаём шарик (радиус, позиция, максимальные значения по осям)
    BALL::Ball ball(BALL_RADIUS, sf::Vector2f(200, 485), WINDOW_WIDTH, OFFSET, WINDOW_HEIGHT, 0, &physObj, &gameController);
    ball.setDirection(sf::Vector2f(0.5f, -0.5f));
    ball.setFillColor(sf::Color::Blue);

    sf::Vertex border1[] = {
        sf::Vertex(sf::Vector2f(OFFSET, 0)),
        sf::Vertex(sf::Vector2f(OFFSET, 600))
    };
    

    // Расчёт размера разрушаюющихся блоков
    float blocksWidth = (WINDOW_WIDTH - OFFSET) / BLOCKS_PER_LINE;
    bool nowRed = true;

    for (size_t i = 0; i < BLOCKS_PER_LINE; i++)
    {
        for (int j = 0; j < 5; j++) {

            // Создаём новый разрушающийся блок (позиция, размер и количество очков здоровья)
            // Также чередуем их цвета (красный и синий)
            // Добавляем указатель на новый блок в вектор физ. объектов
            
            BLOCK::DestoyingBlock* destrBlock = new BLOCK::DestoyingBlock(sf::Vector2f(i * blocksWidth + blocksWidth / 2 + OFFSET, j * 10 + 5), sf::Vector2f(blocksWidth, BLOCKS_HEIGHT), 10);
            
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

    // Блок игрока тоже физ. объект, поэтому его добавляем в вектор
    physObj.push_back(&block);

    
    bool isPlaying = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear();
        if (gameController.getHPCount() > 0) {

            // Движение влево
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                block.move(sf::Vector2f(-0.25f, 0));

            // Движение вправо
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                block.move(sf::Vector2f(0.25f, 0));

            ball.move();
        }
        else {
            uiController.gameOver(window);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                gameController.setHPCount();
        }

        
        window.draw(ball);
        window.draw(block);
        window.draw(border1, 2, sf::Lines);
        uiController.drawUI(window, gameController);

        // Проходим по всем физическим объектам и выводим их на экран
        for (auto obj : physObj) {
            if (obj != NULL)
                window.draw(*dynamic_cast<sf::Shape*>(obj));
        }

        window.display();


        // Проверка количества очков здоровья у разрушающихся блоков
        // Если они <= 0, то удаляем блок
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


    // Если игра завершена дострочно (не все блоки разбиты)
    // освобождаем занятую память
    for (int i = 0; i < physObj.size()-1; i++)
    {
        std::cout << "\n\nDeleting physic object # " << i << " " << std::endl;
        if (physObj[i] != NULL)
            delete physObj[i];
    }

    return 0;
}