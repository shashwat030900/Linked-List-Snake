#include "Player/PlayerService.h"
#include "Player/SnakeController.h"
#include "Global/ServiceLocator.h"
#include "Level/LevelService.h"
#include "Level/LevelView.h"

namespace Player
{
    using namespace Global;
    using namespace Level;

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
        LevelView* level_view = ServiceLocator::getInstance()->getLevelService()->getLevelView();
        snake_controller->initialize(level_view);
    }

    void PlayerService::update()
    {
        snake_controller->update();
    }

    void PlayerService::render()
    {
        snake_controller->render();
    }

    void PlayerService::spawnPlayer()
    {
        snake_controller->spawnSnake();
    }
}
