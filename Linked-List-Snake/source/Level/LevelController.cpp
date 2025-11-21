#include "Level/LevelController.h"
#include "Level/LevelModel.h"
#include "Level/LevelView.h"
#include "Level/LevelConfig.h"

namespace Level
{
    LevelController::LevelController() :
        level_model(new LevelModel()),
        level_view(new LevelView())
    {
    }

    LevelController::~LevelController()
    {
        delete level_model;
        delete level_view;
    }

    void LevelController::initialize()
    {
        level_view->initialize();
        level_model->initialize(static_cast<int>(level_view->getGridWidth()), static_cast<int>(level_view->getGridHeight()));
    }

    void LevelController::update()
    {
        level_view->update();
    }

    void LevelController::render()
    {
        level_view->render();
        level_view->renderObstacles(level_model->getCurrentLevelLayout(), level_model->getCellWidth(), level_model->getCellHeight());
    }

    void LevelController::loadLevel(LevelNumber level_number)
    {
        level_model->loadLevel(static_cast<int>(level_number));
    }

    float LevelController::getCellWidth()
    {
        return level_model->getCellWidth();
    }

    float LevelController::getCellHeight()
    {
        return level_model->getCellHeight();
    }

    LevelView* LevelController::getLevelView()
    {
        return level_view;
    }

    const std::vector<Element::ElementData>& LevelController::getElementDataList(int level_to_load)
    {
        return level_model->getElementDataList(level_to_load);
    }
}
