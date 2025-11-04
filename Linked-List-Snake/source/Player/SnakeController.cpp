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


namespace Player
{
    using namespace LinkedListLib::SingleLinked;
    using namespace Global;
    using namespace Level;
	using namespace Event;
    using namespace Food;


    SnakeController::SnakeController()
    {
		single_linked_list = new SingleLinkedList();
        createLinkedList();
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
            float width = ServiceLocator::getInstance()->getLevelService()->getCellWidth();
            float height = ServiceLocator::getInstance()->getLevelService()->getCellHeight();

            int columns = LevelModel::number_of_columns;
            int rows = LevelModel::number_of_rows;
            default_position = { columns / 2, rows / 2 };

            single_linked_list->initialize(width, height, default_position, default_direction);
    }

        
    void SnakeController::update()
    {
            switch (current_snake_state)
            {
            case SnakeState::ALIVE:
                processPlayerInput();
				delayedUpdate();
              /*  updateSnakeDirection();
                processSnakeCollision();
                moveSnake();*/
                break;

            case SnakeState::DEAD:
                handleRestart();
                break;
            }
			

    }

    void SnakeController::render()
    {
		single_linked_list->render();
    }
    void SnakeController::spawnSnake()
    {
        for (int i = 0; i < initial_snake_length; i++) {
        
			single_linked_list->insertNodeAtTail();
        
        }

	}

    
    void SnakeController::updateSnakeDirection()
    {
		single_linked_list->updateNodeDirection(current_snake_direction);
    }
    void SnakeController::moveSnake()
    {
        single_linked_list->updateNodePosition();

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
        single_linked_list->removeAllNodes();
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
		delete (single_linked_list);

	}
    void SnakeController::createLinkedList()
    {
        single_linked_list = new SingleLinkedList();
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

			//moveSnake();
			current_input_state = InputState::WAITING;
        
        } 
    }

    std::vector<sf::Vector2i> SnakeController::getCurrentSnakePositionList()
    {
        return single_linked_list->getNodesPositionList();
    }

    void SnakeController::processBodyCollision()
    {
        Element::ElementService* element_service = ServiceLocator::getInstance()->getElementService();

        if (element_service->checkSnakeHeadCollision(single_linked_list->getHeadNode()))
        {
            setSnakeState(SnakeState::DEAD);
        }

    }


    void SnakeController::processElementsCollision()
    {
        Element::ElementService* element_service = ServiceLocator::getInstance()->getElementService();

        if (element_service->processElementsCollision(single_linked_list->getHeadNode()))
        {
            current_snake_state = SnakeState::DEAD;
            ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::DEATH);
        }
    }


    void SnakeController::processFoodCollision()
    {
        Food::FoodService* food_service = ServiceLocator::getInstance()->getFoodService();
        Food::FoodType food_type;

        if (food_service->processFoodCollision(single_linked_list->getHeadNode(), food_type))
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
            
            single_linked_list->insertNodeAtTail();
            time_complexity = TimeComplexity::N;
            last_linked_list_operation = LinkedListOperations::INSERT_AT_TAIL;
            break;

        case FoodType::BURGER:
            
            single_linked_list->insertNodeAtHead();
            time_complexity = TimeComplexity::ONE;
            last_linked_list_operation = LinkedListOperations::INSERT_AT_HEAD;
            break;

        case FoodType::CHEESE:
            
                single_linked_list->insertNodeAtMiddle();
                time_complexity = TimeComplexity::N;
                last_linked_list_operation = LinkedListOperations::INSERT_AT_MID;
            
            break;

        case FoodType::APPLE:
            
            if (single_linked_list->getLinkedListSize() > 2)
            {
                single_linked_list->removeNodeAtHead();
                time_complexity = TimeComplexity::ONE;
                last_linked_list_operation = LinkedListOperations::REMOVE_AT_HEAD;
            }
            break;

        case FoodType::MANGO:
            
            if (single_linked_list->getLinkedListSize() > 2)
            {
                single_linked_list->removeNodeAtMiddle();
                time_complexity = TimeComplexity::N;
                last_linked_list_operation = LinkedListOperations::REMOVE_AT_MID;
            }
            break;

        case FoodType::ORANGE:
            
            if (single_linked_list->getLinkedListSize() > 2)
            {
                single_linked_list->removeNodeAtTail();
                time_complexity = TimeComplexity::N;
                last_linked_list_operation = LinkedListOperations::REMOVE_AT_TAIL;
            }
            break;

        case FoodType::POISION:
            
            if (single_linked_list->getLinkedListSize() > 2)
            {
                single_linked_list->removeHalfNodes();
                time_complexity = TimeComplexity::N;
                last_linked_list_operation = LinkedListOperations::DELETE_HALF_LIST;
            }
            break;

        case FoodType::ALCOHOL:
            
            current_snake_direction = single_linked_list->reverse();
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


}
