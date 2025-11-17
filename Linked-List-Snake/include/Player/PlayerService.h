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

        void spawnPlayer();
    };
}

