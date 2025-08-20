#include "../../include/Level/LevelService.h"
#include "../../include/Level/LevelController.h"
#include "Global/ServiceLocator.h"
#include "Player/PlayerService.h"

namespace Level
{
    using namespace Global;
    using namespace Player;

    LevelService::LevelService()
    {
        level_controller = new LevelController();
    }

    LevelService::~LevelService()
    {
        delete level_controller;
    }

    void LevelService::initialize()
    {
        level_controller->initialize();
    }

    void LevelService::update()
    {
        level_controller->update();
    }

    void LevelService::render()
    {
        level_controller->render();
    }

    void LevelService::createLevel(LevelNumber level_to_load)
    {
        current_level = level_to_load;
        level_controller->loadLevel(level_to_load);
        spawnPlayer();
    }

    void LevelService::spawnPlayer()
    {
        ServiceLocator::getInstance()->getPlayerService()->spawnPlayer();
    }

    
    float LevelService::getCellWidth()
    {
        return cell_width;
    }

    float LevelService::getCellHeight()
    {
        return cell_height;
    }
}
