#pragma once
#include "Level/LevelController.h"
#include "Level/LevelNumber.h"

namespace Level
{
    class LevelService
    {
    private:
        LevelController* level_controller;
        LevelNumber current_level;

        void spawnPlayer();
        float cell_width = 20.f;
        float cell_height = 20.f;
    

    public:
        LevelService();
        ~LevelService();

        void initialize();
        void update();
        void render();

        void createLevel(LevelNumber level_to_load);

        float getCellWidth();
        float getCellHeight();
    };
}
