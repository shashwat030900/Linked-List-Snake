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

        void spawnPlayer();
        void spawnFood();
        float cell_width = 20.f;
        float cell_height = 20.f;
        void spawnLevelElements(LevelNumber level_to_load);

        
    

    public:
        LevelService();
        ~LevelService();

        void initialize();
        void update();
        void render();
		LevelNumber getCurrentLevel() const;

        void createLevel(LevelNumber level_to_load);

        float getCellWidth();
        float getCellHeight();
        LevelView* getLevelView();
    };
}
