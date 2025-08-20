#include "Player/SnakeController.h"
#include "Global/ServiceLocator.h"
#include "Level/LevelService.h"
#include "LinkedList/SingleLinkedList.h"


namespace Player
{
    using namespace LinkedList;
    using namespace Global;
    using namespace Level;


    SnakeController::SnakeController()
    {
        single_linked_list = nullptr;
        level_view = nullptr;
        createLinkedList();
    }

    
        
    SnakeController::~SnakeController() {
        
            destroy();
    }

        
    void SnakeController::initialize(Level::LevelView* view)
    {
            level_view = view;
            float width = ServiceLocator::getInstance()->getLevelService()->getCellWidth();
            float height = ServiceLocator::getInstance()->getLevelService()->getCellHeight();

            single_linked_list->initialize(width, height, default_position, default_direction);
    }

        
    void SnakeController::update()
    {
            switch (current_snake_state)
            {
            case SnakeState::ALIVE:
                processPlayerInput();
                updateSnakeDirection();
                processSnakeCollision();
                moveSnake();
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
        single_linked_list->createHeadNode(level_view);

	}

    void SnakeController::processPlayerInput()
    {
    }
    void SnakeController::updateSnakeDirection()
    {
    }
    void SnakeController::moveSnake()
    {
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
}
