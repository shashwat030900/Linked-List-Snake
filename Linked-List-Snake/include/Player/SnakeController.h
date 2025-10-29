#pragma once
#include <SFML/System/Vector2.hpp>
#include "LinkedList/SingleLinkedList.h"
#include "Player/Direction.h"
#include "Food/FoodType.h"

namespace Player
{

    enum class TimeComplexity
    {
        NONE,
        ONE,
        N,
    };

    enum class LinkedListOperations
    {
        NONE,
        INSERT_AT_HEAD,
        INSERT_AT_TAIL,
        INSERT_AT_MID,
        REMOVE_AT_HEAD,
        REMOVE_AT_TAIL,
        REMOVE_AT_MID,
        DELETE_HALF_LIST,
        REVERSE_LIST,
    };


    enum class SnakeState { ALIVE, DEAD }; \
        enum class InputState
    {
        WAITING,
		PROCESSING
    };

    class SnakeController
    {
    private:

        TimeComplexity time_complexity;
        LinkedListOperations last_linked_list_operation;
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
        float elapsed_duration = 2.f;
        float restart_counter = 0.f;

        InputState current_input_state;
        int player_score;
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

        void processBodyCollision();
        void processElementsCollision();
        void processFoodCollision();

        void OnFoodCollected(Food::FoodType food_type);
        
        void setSnakeState(SnakeState state);
        SnakeState getSnakeState();
        const float restart_duration = 2.f;
        std::vector<sf::Vector2i> getCurrentSnakePositionList();
        int getPlayerScore() const;
        TimeComplexity getTimeComplexity();
        LinkedListOperations getLastOperation();
      
    };
}
