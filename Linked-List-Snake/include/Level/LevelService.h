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

    public:
        LevelService();
        ~LevelService();

        void initialize();
        void update();
        void render();

        void createLevel(LevelNumber level_to_load);
    };
}
