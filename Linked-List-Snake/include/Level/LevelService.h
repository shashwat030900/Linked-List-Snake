#pragma once
#include "Level/LevelController.h"
#include "Level/LevelConfig.h"

namespace Level
{
    class LevelView;

    class LevelService
    {
    private:
        LevelController* level_controller;
        LevelNumber current_level;

        void spawnPlayer(LinkedListType type_to_use);
        void spawnFood();
        float cell_width = 20.f;
        float cell_height = 20.f;
        void spawnLevelElements(LevelNumber level_to_load);
        Level::LinkedListType current_linked_list_type;
        

    public:
        LevelService();
        ~LevelService();
        void setCurrentLevelNumber(LevelNumber level_to_load);
        void initialize();
        void update();
        void render();
        LevelNumber getCurrentLevel() const;
        
        void createLevel(LevelNumber level_to_load);
        void createLevel(LinkedListType linked_list_type); 

        float getCellWidth();
        float getCellHeight();
        LevelView* getLevelView();
    };
}
