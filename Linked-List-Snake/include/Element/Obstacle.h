#pragma once
#include "UI/UIElement/ImageView.h"

namespace Element {

	class Obstacle {

	public:
		Obstacle();
		~Obstacle();
		void render();
		void update();

	private:
		UI::UIElement::ImageView* obstacle_image;
		sf::Vector2i grid_position;
		float cell_width;
		float cell_height;




	};





}