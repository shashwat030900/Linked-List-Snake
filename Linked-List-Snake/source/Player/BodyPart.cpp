#include "Player/BodyPart.h"
#include "Global/Config.h"
#include "Global/ServiceLocator.h"
#include "Level/LevelService.h"
#include "Level/LevelModel.h"

namespace Player
{
    using namespace Global;
    using namespace Level;

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
        LevelView* level_view = ServiceLocator::getInstance()->getLevelService()->getLevelView();
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
            return 0.f;
        case Direction::LEFT:
            return 180.f;
        default:
            return 0.f;
        }
    }

    
    sf::Vector2i BodyPart::getNextPosition()
    {
        switch (direction)
        {
        case Direction::UP:
            return getNextPositionUp();

        case Direction::DOWN:
            return getNextPositionDown();

        case Direction::LEFT:
            return getNextPositionLeft();

        case Direction::RIGHT:
            return getNextPositionRight();

        default:
            return grid_position;
        }
		
        
    }
   

    sf::Vector2i BodyPart::getNextPositionUp()
    {
       // return sf::Vector2i(grid_position.x, (grid_position.y - 1 + (Level::LevelModel::number_of_rows)) % (LevelModel::number_of_rows) );
        int rows = Level::LevelModel::number_of_rows;
        return sf::Vector2i(grid_position.x, (grid_position.y - 1 + rows) % rows);
    }

    sf::Vector2i BodyPart::getNextPositionDown()
    {
        //return sf::Vector2i(grid_position.x, (grid_position.y + 1) % (LevelModel::number_of_rows));
        int rows = Level::LevelModel::number_of_rows;
        return sf::Vector2i(grid_position.x, (grid_position.y + 1) % rows);
    }

    sf::Vector2i BodyPart::getNextPositionLeft()
    {
        //return sf::Vector2i((grid_position.x - 1 + LevelModel::number_of_columns) % (LevelModel::number_of_columns), grid_position.y);
        int cols = Level::LevelModel::number_of_columns;
        return sf::Vector2i((grid_position.x - 1 + cols) % cols, grid_position.y);
    }

    sf::Vector2i BodyPart::getNextPositionRight()
    {
        //return sf::Vector2i((grid_position.x + 1) % (LevelModel::number_of_columns), grid_position.y);
        int cols = Level::LevelModel::number_of_columns;
        return sf::Vector2i((grid_position.x + 1) % cols, grid_position.y);
    }

    void BodyPart::setPosition(sf::Vector2i position)
    {
        grid_position = position;
    }

    Direction BodyPart::getDirection()
    {
        return direction;
    }

    sf::Vector2i BodyPart::getPosition()
    {
        return grid_position;
    }
    void BodyPart::setDirection(Direction direction) {

        this->direction = direction;

    }

    sf::Vector2i BodyPart::getPrevPosition()
    {
        switch (direction)
        {
        case Direction::UP:
            return getNextPositionDown();
        case Direction::DOWN:
            return getNextPositionUp();
        case Direction::RIGHT:
            return getNextPositionLeft();
        case Direction::LEFT:
            return getNextPositionRight();
        default:
            return grid_position;
        }
    }





}
