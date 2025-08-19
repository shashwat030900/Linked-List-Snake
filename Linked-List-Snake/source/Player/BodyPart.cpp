#include "Player/BodyPart.h"
#include "Global/Config.h"

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

    
    sf::Vector2f BodyPart::getBodyPartScreenPosition() const
    {
        
        return sf::Vector2f(
            grid_position.x * bodypart_width + bodypart_width * 0.5f,
            grid_position.y * bodypart_height + bodypart_height * 0.5f
        );
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
    void BodyPart::updateSnakeDirection() {}
    void BodyPart::moveSnake() { }
    void BodyPart::processSnakeCollision() {}
    void BodyPart::update() { }
}
