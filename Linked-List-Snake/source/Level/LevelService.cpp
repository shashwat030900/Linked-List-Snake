#include "../../include/Level/LevelService.h"
#include "../../include/Level/LevelController.h"
#include "Global/ServiceLocator.h"
#include "Player/PlayerService.h"
#include "Element/ElementData.h" // Add this include

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
        cell_width = level_controller->getCellWidth();
        cell_height = level_controller->getCellHeight();

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
		spawnLevelElements(level_to_load);
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

	LevelView* LevelService::getLevelView()
	{
		return level_controller->getLevelView();
	}
    void LevelService::spawnLevelElements(LevelNumber level_to_load)
    {
        float cell_width = level_controller->getCellWidth();
        float cell_height = level_controller->getCellHeight();

        std::vector<Element::ElementData> element_data_list = level_controller->getElementDataList((int)level_to_load);
        ServiceLocator::getInstance()->getElementService()->spawnElements(element_data_list, cell_width, cell_height);
    }
}
