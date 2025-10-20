#pragma once

#include <SFML/System/Vector2.hpp>
#include "Player/Direction.h"
#include "UI/UIElement/ImageView.h"
#include "Global/Config.h"
#include "Level/LevelView.h"

namespace Player
{
    class BodyPart
    {
		class ImageView;    
    protected:
        UI::UIElement::ImageView* bodypart_image;
        sf::Vector2i grid_position;
        Direction direction;  

        float bodypart_width{};
        float bodypart_height{};

        void createBodyPartImage();
        void destroy();
        void initializeBodyPartImage();
        sf::Vector2f getBodyPartScreenPosition();
        void syncImageToGrid();
        float getRotationAngle();
        
    public:
        BodyPart();
        ~BodyPart();

        void initialize(float width, float height, sf::Vector2i pos, Direction dir);
        void update();
        void render();
        void reset();
        void handleRestart();
        void processPlayerInput();
        void updatePosition();
        void moveSnake();
        void processSnakeCollision();
        void setPosition(sf::Vector2i position);
        void setDirection(Direction direction);

        sf::Vector2i getNextPosition();
        sf::Vector2i getNextPositionUp();
        sf::Vector2i getNextPositionDown();
        sf::Vector2i getNextPositionLeft();
        sf::Vector2i getNextPositionRight();

        Direction getDirection(); 
        sf::Vector2i getPosition();
        sf::Vector2i getPrevPosition();
    };
}
