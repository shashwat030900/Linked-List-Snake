#include "Food/FoodItem.h"
#include "Global/Config.h"
#include "Level/LevelView.h"

namespace Food {
	using namespace Global;

	FoodItem::FoodItem() {
		
	}
	FoodItem::~FoodItem() {
		
	}
	sf::String FoodItem::getFoodTexturePath()
	{
		switch (food_type)
		{
		case Food::FoodType::APPLE:
			return Config::apple_texture_path;

		case Food::FoodType::MANGO:
			return Config::mango_texture_path;

		case Food::FoodType::ORANGE:
			return Config::orange_texture_path;

		case Food::FoodType::PIZZA:
			return Config::pizza_texture_path;

		case Food::FoodType::BURGER:
			return Config::burger_texture_path;

		case Food::FoodType::CHEESE:
			return Config::cheese_texture_path;

		case Food::FoodType::POISION:
			return Config::poision_texture_path;

		case Food::FoodType::ALCOHOL:
			return Config::alcohol_texture_path;

		default:
			return Config::apple_texture_path;
		}
	}
	void FoodItem::update() {
		
	}
	void FoodItem::render() {
		
		
	}
	sf::Vector2f FoodItem::getFoodImagePosition()
	{
		float screen_position_x = Level::LevelView::getBorderLeftOffset() + (cell_width * grid_position.x);
		float screen_position_y = Level::LevelView::getBorderTopOffset() + (cell_height * grid_position.y);
		return sf::Vector2f(screen_position_x, screen_position_y);
	}
}