#include "Player/SnakeController.h"
#include "Global/ServiceLocator.h"
#include "Level/LevelService.h"
#include "LinkedList/SingleLinkedList.h"
#include "Player/Direction.h"
#include "Level/LevelView.h"
#include "Level/LevelModel.h"


namespace Player
{
    using namespace LinkedList;
    using namespace Global;
    using namespace Level;


    SnakeController::SnakeController()
    {
        single_linked_list = nullptr;
        createLinkedList();
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
    }
    void SnakeController::handleRestart()
    {
    }
    void SnakeController::reset()
    {
    }
    void SnakeController::respawnSnake()
    {
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

    void SnakeController::processPlayerInput() {
    
		Event::EventService* event_service = ServiceLocator::getInstance()->getEventService();

        if(event_service->pressedLeftArrowKey())
        {
            current_snake_direction = Direction::LEFT;
        }
        else if(event_service->pressedRightArrowKey())
        {
            current_snake_direction = Direction::RIGHT;
        }
        else if(event_service->pressedUpArrowKey())
        {
            current_snake_direction = Direction::UP;
        }
        else if(event_service->pressedDownArrowKey())
        {
            current_snake_direction = Direction::DOWN;
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
        
        }
    
    
    
    
    
    
    
    
    }














}
