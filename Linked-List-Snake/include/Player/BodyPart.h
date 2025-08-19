#pragma once

#include <SFML/System/Vector2.hpp>
#include "Direction.h"
#include "UI/UIElement/ImageView.h"
#include "Global/Config.h"  
#include "Level/LevelView.h"  

namespace Player
{
    class BodyPart
    {
    protected:
        UI::UIElement::ImageView* bodypart_image;

        sf::Vector2i grid_position;
        Direction    direction;

        float bodypart_width{};
        float bodypart_height{};

        void createBodyPartImage();
        void destroy();

        
        void initializeBodyPartImage();
        sf::Vector2f getBodyPartScreenPosition();
        void syncImageToGrid();
        float getRotationAngle();

    public:
        Level::LevelView* level_view;
        BodyPart();
        virtual ~BodyPart();

        
        void initialize(float width, float height, sf::Vector2i pos, Direction dir);
        void update();
        void render();

        
        void reset();
        void handleRestart();
        void processPlayerInput();
		void updatePosition();
        void moveSnake();
        void processSnakeCollision();

        void setDirection(Direction direction);
    };
}
