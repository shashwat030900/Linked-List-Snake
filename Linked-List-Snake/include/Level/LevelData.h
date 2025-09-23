#pragma once
#include "LevelNumber.h"
#include "Element/ElementData.h"
#include <vector>

namespace Level
{
    struct LevelData
    {
		LevelData() = default;
        LevelData(LevelNumber ind, std::vector<Element::ElementData>* data_list) {

			level_index = ind;
			element_data_list = data_list;  



        }
		LevelNumber level_index;
		std::vector<Element::ElementData>* element_data_list;
        std::vector<std::vector<int>> layout;
        std::vector<Element::ElementData> level_one_element_list;
        std::vector<Element::ElementData> level_two_element_list;
        std::vector<LevelData> level_configurations;

	private:


		void initializeLevelData();



    };
}
