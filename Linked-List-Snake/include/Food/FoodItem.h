#pragma once
#include <SFML/Graphics.hpp>
#include "Food/FoodType.h"
#include "UI/UIElement/ImageView.h"

namespace Food {
    class FoodItem {
    private:
        FoodType food_type;
        float cell_width;
        float cell_height;
        sf::Vector2i grid_position;
        UI::UIElement::ImageView* food_image; // pointer

    public:
        FoodItem();
        ~FoodItem();

        void initialize(sf::Vector2i gridPos, float cellW, float cellH, FoodType type);
        sf::String getFoodTexturePath();
        void update();
        void render();
        sf::Vector2f getFoodImagePosition();
        void initializeFoodImage();
    };
}