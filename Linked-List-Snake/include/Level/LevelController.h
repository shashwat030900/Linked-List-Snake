#pragma once
#include "Level/LevelConfig.h"
#include "Element/ElementData.h"
#include <vector>

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
        LevelView* getLevelView();
        const std::vector<Element::ElementData>& getElementDataList(int level_to_load);
    };
}
