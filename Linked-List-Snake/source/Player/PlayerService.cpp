#include "Player/PlayerService.h"
#include "Player/SnakeController.h"
#include "Level/LevelConfig.h"

namespace Player
{
    PlayerService::PlayerService()
    {
        createController();
    }

    PlayerService::~PlayerService()
    {
        delete snake_controller;
    }

    void PlayerService::createController()
    {
        snake_controller = new SnakeController();
    }

    void PlayerService::initialize()
    {
        snake_controller->initialize();
    }

    void PlayerService::update()
    {
        snake_controller->update();
    }

    void PlayerService::render()
    {
        snake_controller->render();
    }

    void PlayerService::spawnPlayer(Level::LinkedListType level_type)
{
	snake_controller->createLinkedList(level_type);
	snake_controller->spawnSnake();
}

    int PlayerService::getPlayerScore() const
    {
        return snake_controller->getPlayerScore();
	}

    TimeComplexity PlayerService::getTimeComplexity()
    {
        return snake_controller->getTimeComplexity();
    }

    LinkedListOperations PlayerService::getLastOperation()
    {
        return snake_controller->getLastOperation();
    }

    std::vector<sf::Vector2i> PlayerService::getCurrentSnakePositionList()
    {
        return snake_controller->getCurrentSnakePositionList();
    }

    bool PlayerService::isPlayerDead()
    {
        return snake_controller->isSnakeDead();
    }
}
