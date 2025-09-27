#pragma once
#include <SFML/System/Vector2.hpp>
#include "Level/LevelData.h"
#include <vector>
#include "Element/ElementData.h"

namespace Level
{
    class LevelModel
    {
    private:
        std::vector<LevelData> level_configurations;
        std::vector<std::vector<int>> current_level_layout;

        std::vector<Element::ElementData> level_one_element_list;
        std::vector<Element::ElementData> level_two_element_list;
        

        
        float cell_width;
        float cell_height;

		void initializeLevelData();
        static std::vector<Element::ElementData> empty_element_list;
    public:
        static const int number_of_rows = 28;
        static const int number_of_columns = 50;

        LevelModel();
        ~LevelModel();

        void initialize(int width, int height);
        void loadLevel(int level_number);

        const std::vector<std::vector<int>>& getCurrentLevelLayout() const;
        const std::vector<Element::ElementData>& getElementDataList(int level_to_load);
        float getCellWidth();
        float getCellHeight();
    };
}
