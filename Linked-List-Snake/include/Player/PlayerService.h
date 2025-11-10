#pragma once
#include "Player/PlayerService.h"
#include "Player/SnakeController.h"

namespace Player
{
    class PlayerService
    {
    private:
        Player::SnakeController* snake_controller;

        void createController();

    public:
        PlayerService();
        ~PlayerService();

        void initialize();
        void update();
        void render();
        bool isPlayerDead();
        void spawnPlayer(Level::LinkedListType level_type);
		int getPlayerScore() const;
        std::vector<sf::Vector2i> getCurrentSnakePositionList();
        TimeComplexity getTimeComplexity();
        LinkedListOperations getLastOperation();

    };
}

