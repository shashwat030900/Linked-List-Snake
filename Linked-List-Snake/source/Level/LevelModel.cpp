#include "Level/LevelModel.h"
#include "Level/LevelData.h"

namespace Level
{
	LevelModel::LevelModel()
	{
		LevelData level_one_data;
		level_one_data.layout = std::vector<std::vector<int>>(number_of_rows, std::vector<int>(number_of_columns, 0));
		level_configurations.push_back(level_one_data);

		LevelData level_two_data;
		level_two_data.layout = std::vector<std::vector<int>>(number_of_rows, std::vector<int>(number_of_columns, 0));
		for (int i = 0; i < number_of_rows; i++) {
			for (int j = 0; j < number_of_columns; j++) {
				if (i == 0 || i == number_of_rows - 1 || j == 0 || j == number_of_columns - 1) {
					level_two_data.layout[i][j] = 1;
				}
			}
		}
		level_configurations.push_back(level_two_data);
	}

	LevelModel::~LevelModel() = default;

	void LevelModel::initialize(int width, int height)
	{
		cell_width = static_cast<float>(width) / number_of_columns;
		cell_height = static_cast<float>(height) / number_of_rows;
	}

	float LevelModel::getCellWidth()
	{
		return cell_width;
	}

	float LevelModel::getCellHeight()
	{
		return cell_height;
	}

	void LevelModel::loadLevel(int level_number)
	{
		if (level_number >= 0 && level_number < level_configurations.size())
		{
			current_level_layout = level_configurations[level_number].layout;
		}
	}

	const std::vector<std::vector<int>>& LevelModel::getCurrentLevelLayout() const
	{
		return current_level_layout;
	}
}
