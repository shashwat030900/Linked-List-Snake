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
		Direction current_snake_direction = Direction::RIGHT;

        //sf::Vector2i default_position = { 48, 27 };
        sf::Vector2i default_position{};
        Player::Direction default_direction = Direction::RIGHT;

        void destroy();
        void createLinkedList();
        void processPlayerInput();
        const float movement_frame_duration = 0.1f;
        void delayedUpdate();
        float elapsed_duration;
		

    public:
        SnakeController();
        ~SnakeController();

		const int initial_snake_length = 8; 

        void initialize();
        void update();
        void render();

        void spawnSnake();
        void respawnSnake();
        void reset();
        void handleRestart();
        
        void updateSnakeDirection();
        void moveSnake();
        void processSnakeCollision();
        
        void setSnakeState(SnakeState state);
        SnakeState getSnakeState();
        const float restart_duration = 2.f;
   
      
    };
}
