#pragma once

#include "LinkedList/SingleLinkedList.h"
#include "Player/Direction.h"

namespace Player
{
    enum class SnakeState { ALIVE, DEAD };

    class SnakeController
    {
    private:
        LinkedList::SingleLinkedList* single_linked_list; 
        SnakeState current_snake_state = SnakeState::ALIVE;

        sf::Vector2i default_position = { 24, 13 };
        Player::Direction default_direction = Direction::RIGHT;

    public:
        SnakeController();
        ~SnakeController();

        void initialize();
        void update();
        void render();

        void spawnSnake();
        void respawnSnake();
        void reset();
        void handleRestart();
        void processPlayerInput();
        void updateSnakeDirection();
        void moveSnake();
        void processSnakeCollision();
        
        void setSnakeState(SnakeState state);
        SnakeState getSnakeState();

    private:
        void destroy();
        void createLinkedList();
    };
}
