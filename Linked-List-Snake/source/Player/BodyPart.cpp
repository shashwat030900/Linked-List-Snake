#include "Player/BodyPart.h"
#include "Global/Config.h"
#include "Level/LevelView.h"

namespace Player
{
    BodyPart::BodyPart()
        : grid_position(0, 0), bodypart_image(nullptr)
    {
        createBodyPartImage();
    }

    BodyPart::~BodyPart()
    {
        destroy();
    }

    void BodyPart::createBodyPartImage()
    {
        if (!bodypart_image)
            bodypart_image = new UI::UIElement::ImageView();
    }

   
    void BodyPart::initializeBodyPartImage()
    {
        if (!bodypart_image) createBodyPartImage();

        bodypart_image->initialize(
			Global::Config::snake_body_texture_path,
            bodypart_width,
            bodypart_height,
            getBodyPartScreenPosition()
        );
        bodypart_image->setOriginAtCentre();
    }

    
    sf::Vector2f BodyPart::getBodyPartScreenPosition()
    {
        float x_screen_position = level_view->border_left_offset + (grid_position.x * bodypart_width) + (bodypart_width / 2);
        float y_screen_position = level_view->border_top_offset + (grid_position.y * bodypart_height) + (bodypart_height / 2);

        return sf::Vector2f(x_screen_position, y_screen_position);
    }

   
    void BodyPart::syncImageToGrid()
    {
        if (bodypart_image)
            bodypart_image->setPosition(getBodyPartScreenPosition());
    }

  
    void BodyPart::initialize(float width, float height, sf::Vector2i pos, Direction dir)
    {
        bodypart_width = width;
        bodypart_height = height;
        direction = dir;
        grid_position = pos;

        initializeBodyPartImage();
    }

    void BodyPart::render()
    {
        if (bodypart_image)
            bodypart_image->render();
    }

    void BodyPart::destroy()
    {
        delete bodypart_image;
        bodypart_image = nullptr;
    }

    
    void BodyPart::reset() {}
    void BodyPart::handleRestart() {}
    void BodyPart::processPlayerInput() {}
    void BodyPart::updatePosition()
    {
        bodypart_image->setPosition(getBodyPartScreenPosition());
        bodypart_image->setRotation(getRotationAngle());
        bodypart_image->update();
    }
    void BodyPart::moveSnake() { }
    void BodyPart::processSnakeCollision() {}
    void BodyPart::update() { }
    float BodyPart::getRotationAngle()
    {
        switch (direction)
        {
        case Direction::UP:
            return 270.f;
        case Direction::DOWN:
            return 90.f;
        case Direction::RIGHT:
            return 0;
        case Direction::LEFT:
            return 180.f;
        }
    }

    void BodyPart::setDirection(Direction direction) {

        this->direction = direction;

    }
}
