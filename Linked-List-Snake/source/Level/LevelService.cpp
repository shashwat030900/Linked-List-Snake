#include "../../include/Level/LevelService.h"
#include "../../include/Level/LevelController.h"
#include "Global/ServiceLocator.h"
#include "Player/PlayerService.h"
#include "Food/FoodService.h"
#include "Element/ElementData.h" 
#include "Level/LevelConfig.h"

namespace Level
{
    using namespace Global;
    using namespace Player;
	using namespace Food;

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
        LinkedListType list_type_for_this_level = LinkedListType::SINGLE_LINKED_LIST;
        //current_linked_list_type = linked_list_type;
        spawnPlayer(list_type_for_this_level);
		spawnFood();
		spawnLevelElements(current_level);
    }

    void LevelService::spawnPlayer(LinkedListType type_to_use)
    {
        ServiceLocator::getInstance()->getPlayerService()->spawnPlayer(type_to_use);
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
    void LevelService::spawnFood()
    {
        ServiceLocator::getInstance()->getFoodService()->startFoodSpawning();
	}   

    LevelNumber LevelService::getCurrentLevel() const
    {
        return current_level;
	}

    void LevelService::setCurrentLevelNumber(LevelNumber level_to_load)
    {
        current_level = level_to_load;
    }

   

    void LevelService::createLevel(LinkedListType linked_list_type)
    {
        current_linked_list_type = linked_list_type;
        spawnLevelElements(current_level);
        spawnFood();
        spawnPlayer(linked_list_type); 
    }

}
