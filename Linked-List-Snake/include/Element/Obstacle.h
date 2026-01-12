#pragma once
#include <SFML/Graphics.hpp>
#include "UI/UIElement/ImageView.h"

namespace Level { class LevelView; } 

namespace Element
{
    class Obstacle
    {
    private:
        sf::Vector2i grid_position;
        float cell_width = 0;
        float cell_height = 0;
        sf::Vector2f getObstacleImagePosition();
        UI::UIElement::ImageView* obstacle_image = nullptr;
        Level::LevelView* level_view = nullptr; 

        void initializeObstacleImage();
        

    public:
        Obstacle(Level::LevelView* view); 
        ~Obstacle();

        void initialize(sf::Vector2i grid_pos, float width, float height);
        void update();
        void render();
       
		sf::Vector2i getObstaclePosition();
    };
}
