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

		void initializeBackground();

	public:
		LevelView();
		~LevelView();

		void initialize();
		void update();
		void render();
	};
}
