#pragma once
#include <SFML/Graphics.hpp>
#include "UI/UIElement/RectangleShapeView.h"
#include <vector>

namespace Level
{
	class LevelView
	{
	private:
		const sf::Color background_color = sf::Color(180, 200, 160, 255);
		UI::UIElement::RectangleShapeView* background_rectangle;

		const float border_thickness = 10.f;

		float grid_width = 0;
		float grid_height = 0;
		float grid_top = 0;
		float grid_left = 0;
		static const int border_offset_left = 40;
		static const int border_offset_top = 100;
		static const int border_offset_bottom = 40;

		sf::Texture obstacle_texture;
		sf::Sprite obstacle_sprite;
		bool obstacle_texture_loaded = false;

		UI::UIElement::RectangleShapeView* border_rectangle;

		void initializeBackground();
		void calculateGridExtents();
		void initializeBorder();
		void loadObstacleTexture();

	public:
		LevelView();
		~LevelView();

		void initialize();
		void update();
		void render();
		void renderObstacles(const std::vector<std::vector<int>>& layout, float cell_width, float cell_height);

		float getGridWidth();
		float getGridHeight();
		float getGridTop();
		float getGridLeft();
		
		static const float border_top_offset;
		static const float border_left_offset;

		static float getBorderLeftOffset();
		static float getBorderTopOffset();
	};
}
