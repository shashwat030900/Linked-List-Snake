#pragma once
#include "UI/UIElement/ImageView.h"
#include "Food/FoodType.h"
namespace Food {

	class FoodItem {

	private:
		UI::UIElement::ImageView* food_image;
		sf::Vector2i grid_position;
		float cell_width;
		float cell_height;
		FoodType food_type;

		void initializeFoodImage();

	public:
		FoodItem();
		~FoodItem();

		static const int number_of_foods = 8;

		void update();
		void render();
		sf::String getFoodTexturePath();
		sf::Vector2f getFoodImagePosition();




	};




}