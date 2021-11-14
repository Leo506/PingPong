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
#include "Reset.h"


void spawnDestrBlocks(std::vector<PHYSIC::IPhysicObject*>&);
void respawnDestrBlocks(std::vector<PHYSIC::IPhysicObject*>&);
void checkDestrBlocks(std::vector<PHYSIC::IPhysicObject*>&);


int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ping pong");

    // ������ ���������� �� ��� ���������� �������
    std::vector<PHYSIC::IPhysicObject*> physObj;

    // ������ ���������� �� reset-�������
    std::vector<RESET::IResetableObject*> resetObj;

    UI::UIController uiController;

    GAME::GameController gameController;

    // ����, ������� ��������� ����� (������, ��������� �������, ������������ � ����������� �������� �� X
    BLOCK::PlayerBlock block(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT), sf::Vector2f((WINDOW_WIDTH - OFFSET) / 2, 500), WINDOW_WIDTH, OFFSET);

    // ������ ����� (������, �������, ������������ �������� �� ����)
    BALL::Ball ball(BALL_RADIUS, sf::Vector2f(200, 485), WINDOW_WIDTH, OFFSET, WINDOW_HEIGHT, 0, &physObj, &gameController);
    ball.setDirection(sf::Vector2f(0.5f, -0.5f));
    ball.setFillColor(sf::Color::Blue);

    resetObj.push_back(&block);
    resetObj.push_back(&ball);
    
    spawnDestrBlocks(physObj);

    // ���� ������ ���� ���. ������, ������� ��� ��������� � ������
    physObj.push_back(&block);


    sf::Vertex border1[] = {
        sf::Vertex(sf::Vector2f(OFFSET, 0)),
        sf::Vertex(sf::Vector2f(OFFSET, 600))
    };
    



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear();

        if (gameController.getHPCount() > 0 && physObj.size() > 1) {

            // �������� �����
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                block.move(sf::Vector2f(-0.25f, 0));

            // �������� ������
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                block.move(sf::Vector2f(0.25f, 0));

            ball.move();
        }
        else {
            if (gameController.getHPCount() <= 0)
                uiController.gameOver(window);
            else
                uiController.win(window);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                gameController.resetGame(resetObj);
                respawnDestrBlocks(physObj);
                physObj.push_back(&block);
            }
        }

        
        window.draw(ball);
        window.draw(block);
        window.draw(border1, 2, sf::Lines);
        uiController.drawUI(window, gameController);

        // �������� �� ���� ���������� �������� � ������� �� �� �����
        for (auto obj : physObj) {
            if (obj != NULL)
                window.draw(*dynamic_cast<sf::Shape*>(obj));
        }

        window.display();

        checkDestrBlocks(physObj);
        
    }


    // ���� ���� ��������� ��������� (�� ��� ����� �������)
    // ����������� ������� ������
    for (int i = 0; i < physObj.size(); i++)
    {
        std::cout << "\n\nDeleting physic object # " << i << " " << std::endl;
        if (physObj[i] != NULL && dynamic_cast<BLOCK::PlayerBlock*>(physObj[i]) == NULL)
            delete physObj[i];
    }

    return 0;
}


void spawnDestrBlocks(std::vector<PHYSIC::IPhysicObject*>& physVector) {
    // ������ ������� �������������� ������
    float blocksWidth = (WINDOW_WIDTH - OFFSET) / BLOCKS_PER_LINE;
    bool nowRed = true;

    for (size_t i = 0; i < BLOCKS_PER_LINE; i++)
    {
        for (int j = 0; j < 5; j++) {

            // ������ ����� ������������� ���� (�������, ������ � ���������� ����� ��������)
            // ����� �������� �� ����� (������� � �����)
            // ��������� ��������� �� ����� ���� � ������ ���. ��������

            BLOCK::DestoyingBlock* destrBlock = new BLOCK::DestoyingBlock(sf::Vector2f(i * blocksWidth + blocksWidth / 2 + OFFSET, j * 10 + 5), sf::Vector2f(blocksWidth, BLOCKS_HEIGHT), 10);

            if (nowRed) {
                (*destrBlock).setFillColor(sf::Color::Red);
                nowRed = false;
            }

            else {
                (*destrBlock).setFillColor(sf::Color::Blue);
                nowRed = true;
            }

            physVector.push_back(destrBlock);
        }
    }
}


void checkDestrBlocks(std::vector<PHYSIC::IPhysicObject*>& physObj) {
    // �������� ���������� ����� �������� � ������������� ������
    // ���� ��� <= 0, �� ������� ����
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

void respawnDestrBlocks(std::vector<PHYSIC::IPhysicObject*>& physObj) {
    for (size_t i = 0; i < physObj.size(); i++)
    {
        if (physObj[i] != NULL && dynamic_cast<BLOCK::PlayerBlock*>(physObj[i]) == NULL) {
            delete physObj[i];
        }
    }

    physObj.clear();

    spawnDestrBlocks(physObj);
}