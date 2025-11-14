#include "Player/SnakeController.h"
#include "Global/ServiceLocator.h"
#include "Level/LevelService.h"
#include "LinkedListLib/SingleLinked/SingleLinkedList.h"
#include "Player/Direction.h"
#include "Level/LevelView.h"
#include "Level/LevelModel.h"
#include "Event/EventService.h"
#include "Sound/SoundService.h"
#include "Element/ElementService.h"
#include "Food/FoodType.h"
#include "Sound/SoundService.h"
#include "LinkedListLib/DoubleLinked/DoubleLinkedList.h"


namespace Player
{
    using namespace UI;
    using namespace LinkedListLib;
    using namespace Global;
    using namespace Level;
	using namespace Event;
    using namespace Food;

    LinkedListSelection::LinkedListSelectionUIController* linked_list_selection_ui_controller;
    Level::LinkedListType SnakeController::selected_linked_list_type = Level::LinkedListType::SINGLE_LINKED_LIST;

    SnakeController::SnakeController()
    {
		
        
        elapsed_duration = 0.f;
        time_complexity = TimeComplexity::NONE;
        last_linked_list_operation = LinkedListOperations::NONE;   
        player_score = 0;
    }

    
        
    SnakeController::~SnakeController() {
        
            destroy();
    }

        
    void SnakeController::initialize()
    {
            
            
    }

        
    void SnakeController::update()
    {
        processPlayerInput();
            switch (current_snake_state)
            {
            case SnakeState::ALIVE:
                elapsed_duration += ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

                if (elapsed_duration >= movement_frame_duration) {

                    elapsed_duration = 0.0f;
                    updateSnakeDirection();
                    processSnakeCollision();

                    if (current_snake_state == SnakeState::ALIVE)
                        moveSnake();

                    current_input_state = InputState::WAITING;
                }
                break;

            case SnakeState::DEAD:
                handleRestart();
                break;
            }
			

    }

    void SnakeController::render()
    {
		linked_list->render();
    }
    void SnakeController::spawnSnake()
    {
        
        for (int i = 0; i < initial_snake_length; i++) {
            linked_list->insertNodeAtTail();
        }

       
        LinkedListLib::Node* current_node = linked_list->getHeadNode();
        int position_offset = 0;

        while (current_node)
        {
            sf::Vector2i body_position = default_position;

            
            switch (default_direction)
            {
            case Direction::RIGHT:
                body_position.x -= position_offset;
                break;
            case Direction::LEFT:
                body_position.x += position_offset;
                break;
            case Direction::UP:
                body_position.y += position_offset;
                break;
            case Direction::DOWN:
                body_position.y -= position_offset;
                break;
            }

            current_node->body_part.setPosition(body_position);
            position_offset++;
            current_node = current_node->next;
        }

        
        linked_list->updateNodePosition();
    }

    
    void SnakeController::updateSnakeDirection()
    {
		linked_list->updateNodeDirection(current_snake_direction);
    }
    void SnakeController::moveSnake() {
        
        sf::Vector2i next_head_position = linked_list->getHeadNode()->body_part.getNextPosition();

        
        sf::Vector2i head_current_position = linked_list->getHeadNode()->body_part.getPosition();

        
        linked_list->getHeadNode()->body_part.setPosition(next_head_position);

        
        LinkedListLib::Node* current_node = linked_list->getHeadNode()->next;
        sf::Vector2i previous_position = head_current_position;

        while (current_node)
        {
            sf::Vector2i temp = current_node->body_part.getPosition();
            current_node->body_part.setPosition(previous_position);
            previous_position = temp;
            current_node = current_node->next;
        }

        // Update visuals
        linked_list->updateNodePosition();
    }
    void SnakeController::processSnakeCollision()
    {

        processBodyCollision();
        processElementsCollision();
        processFoodCollision();

    }
    void SnakeController::handleRestart()
    {
        restart_counter += ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

        if (restart_counter >= restart_duration)
        {
            respawnSnake();
        }
    }
    void SnakeController::reset()
    {
        current_snake_state = SnakeState::ALIVE;
        current_snake_direction = default_direction;
        elapsed_duration = 0.f;
        restart_counter = 0.f;
		current_input_state = InputState::WAITING;
        player_score = 0;
    }
    void SnakeController::respawnSnake()
    {
        linked_list->removeAllNodes();
		reset();
		spawnSnake();
    }
    void SnakeController::setSnakeState(SnakeState state)
    {
        current_snake_state = state;
    }
    SnakeState SnakeController::getSnakeState()
    {
        return current_snake_state;
    }
    void SnakeController::destroy()
    {
		delete (linked_list);

	}
    void SnakeController::createLinkedList(LinkedListType level_type)
    {
        switch (level_type)
        {
        case LinkedListType::SINGLE_LINKED_LIST:
            linked_list = new LinkedListLib::SingleLinked::SingleLinkedList();
            break;
        case LinkedListType::DOUBLE_LINKED_LIST:
            linked_list = new LinkedListLib::DoubleLinked::DoubleLinkedList();
            break;
        }

        initializeLinkedList();
    }

    void SnakeController::processPlayerInput()
    {
        if (current_input_state == InputState::PROCESSING)
            return;

        Event::EventService* event_service = ServiceLocator::getInstance()->getEventService();

        if (event_service->pressedUpArrowKey() && current_snake_direction != Direction::DOWN)
        {
            current_snake_direction = Direction::UP;
            current_input_state = InputState::PROCESSING;
        }
        else if (event_service->pressedDownArrowKey() && current_snake_direction != Direction::UP)
        {
            current_snake_direction = Direction::DOWN;
            current_input_state = InputState::PROCESSING;
        }
        else if (event_service->pressedLeftArrowKey() && current_snake_direction != Direction::RIGHT)
        {
            current_snake_direction = Direction::LEFT;
            current_input_state = InputState::PROCESSING;
        }
        else if (event_service->pressedRightArrowKey() && current_snake_direction != Direction::LEFT)
        {
            current_snake_direction = Direction::RIGHT;
            current_input_state = InputState::PROCESSING;
        }
    }

    void SnakeController::delayedUpdate() {
    
    
		elapsed_duration += ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

        if (elapsed_duration >= movement_frame_duration) {
        
			elapsed_duration = 0.0f;
			updateSnakeDirection();
			processSnakeCollision();

            if (current_snake_state == SnakeState::ALIVE)
            moveSnake();

        current_input_state = InputState::WAITING;
    } 
}

    std::vector<sf::Vector2i> SnakeController::getCurrentSnakePositionList()
    {
        return linked_list->getNodesPositionList();
    }

    void SnakeController::processBodyCollision()
    {
        Element::ElementService* element_service = ServiceLocator::getInstance()->getElementService();

        if (element_service->checkSnakeHeadCollision(linked_list->getHeadNode()))
        {
            setSnakeState(SnakeState::DEAD);
        }

    }


    void SnakeController::processElementsCollision()
    {
        Element::ElementService* element_service = ServiceLocator::getInstance()->getElementService();

        if (element_service->processElementsCollision(linked_list->getHeadNode()))
        {
            current_snake_state = SnakeState::DEAD;
            ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::DEATH);
        }
    }


    void SnakeController::processFoodCollision()
    {
        Food::FoodService* food_service = ServiceLocator::getInstance()->getFoodService();
        Food::FoodType food_type;

        if (food_service->processFoodCollision(linked_list->getHeadNode(), food_type))
        {
            ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::PICKUP);

            food_service->destroyFood();
            OnFoodCollected(food_type);
            player_score++;
        }
    }

    void SnakeController::OnFoodCollected(FoodType food_type)
    {
        switch (food_type)
        {
        case FoodType::PIZZA:
            
            linked_list->insertNodeAtTail();
            time_complexity = TimeComplexity::N;
            last_linked_list_operation = LinkedListOperations::INSERT_AT_TAIL;
            break;

        case FoodType::BURGER:
            
            linked_list->insertNodeAtHead();
            time_complexity = TimeComplexity::ONE;
            last_linked_list_operation = LinkedListOperations::INSERT_AT_HEAD;
            break;

        case FoodType::CHEESE:
            
                linked_list->insertNodeAtMiddle();
                time_complexity = TimeComplexity::N;
                last_linked_list_operation = LinkedListOperations::INSERT_AT_MID;
            
            break;

        case FoodType::APPLE:
            
            if (linked_list->getLinkedListSize() > 2)
            {
                linked_list->removeNodeAtHead();
                time_complexity = TimeComplexity::ONE;
                last_linked_list_operation = LinkedListOperations::REMOVE_AT_HEAD;
            }
            break;

        case FoodType::MANGO:
            
            if (linked_list->getLinkedListSize() > 2)
            {
                linked_list->removeNodeAtMiddle();
                time_complexity = TimeComplexity::N;
                last_linked_list_operation = LinkedListOperations::REMOVE_AT_MID;
            }
            break;

        case FoodType::ORANGE:
            
            if (linked_list->getLinkedListSize() > 2)
            {
                linked_list->removeNodeAtTail();
                time_complexity = TimeComplexity::N;
                last_linked_list_operation = LinkedListOperations::REMOVE_AT_TAIL;
            }
            break;

        case FoodType::POISION:
            
            if (linked_list->getLinkedListSize() > 2)
            {
                linked_list->removeHalfNodes();
                time_complexity = TimeComplexity::N;
                last_linked_list_operation = LinkedListOperations::DELETE_HALF_LIST;
            }
            break;

        case FoodType::ALCOHOL:
            
            current_snake_direction = linked_list->reverse();
            time_complexity = TimeComplexity::N;
            last_linked_list_operation = LinkedListOperations::REVERSE_LIST;
            break;
        }
    }

    int SnakeController::getPlayerScore() const
    {
        return player_score;
	}

    TimeComplexity SnakeController::getTimeComplexity()
    {
        return time_complexity;
    }

    LinkedListOperations SnakeController::getLastOperation()
    {
        return last_linked_list_operation;
    }
    void SnakeController::setLinkedListType(LinkedListType type)
    {
        selected_linked_list_type = type;
    }

    void SnakeController::initializeLinkedList() {

        float width = ServiceLocator::getInstance()->getLevelService()->getCellWidth();
        float height = ServiceLocator::getInstance()->getLevelService()->getCellHeight();

        reset();
        linked_list->initialize(width, height, default_position, default_direction);

        spawnSnake();

    }

    bool SnakeController::isSnakeDead()
    {
        return current_snake_state == SnakeState::DEAD;
    }

}
