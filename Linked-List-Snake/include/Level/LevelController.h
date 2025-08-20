#pragma once
#include "Level/LevelNumber.h"

namespace Level
{
    class LevelModel;
    class LevelView;

    class LevelController
    {
    private:
        LevelModel* level_model;
        LevelView* level_view;

    public:
        LevelController();
        ~LevelController();

        void initialize();
        void update();
        void render();
		void loadLevel(LevelNumber level_number);

        float getCellWidth();
        float getCellHeight();
    };
}
