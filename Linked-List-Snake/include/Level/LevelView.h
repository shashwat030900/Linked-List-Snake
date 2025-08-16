#pragma once
#include "SFML/Graphics.hpp"
#include "UI/UIElement/RectangleShapeView.h"

namespace Level
{
	class LevelView
	{
	private:
		const sf::Color background_color = sf::Color(180, 200, 160, 255);
		UI::UIElement::RectangleShapeView* background_rectangle;

		const float border_left_offset = 100.f;
		const float border_top_offset = 50.f;
		const float border_thickness = 10.f;

		float grid_width;
		float grid_height;

		UI::UIElement::RectangleShapeView* border_rectangle;

		void initializeBackground();
		void calculateGridExtents();
		void initializeBorder();

	public:
		LevelView();
		~LevelView();

		void initialize();
		void update();
		void render();

		float getGridWidth();
		float getGridHeight();
	};
}
