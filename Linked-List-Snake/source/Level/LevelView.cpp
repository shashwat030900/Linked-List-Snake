#include "../../include/Level/LevelView.h"
#include "../../include/Global/ServiceLocator.h"

namespace Level
{
    using namespace Global;
    using namespace UI::UIElement;

    LevelView::LevelView()
    {
        background_rectangle = new RectangleShapeView();
        border_rectangle = new RectangleShapeView();
    }

    LevelView::~LevelView()
    {
        delete background_rectangle;
        delete border_rectangle;
    }

    void LevelView::initialize()
    {
        initializeBackground();
        calculateGridExtents();
        initializeBorder();
    }

    void LevelView::update()
    {
        background_rectangle->update();
        border_rectangle->update();
    }

    void LevelView::render()
    {
        background_rectangle->render();
        border_rectangle->render();
    }

    void LevelView::initializeBackground()
    {
        sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();
        sf::Vector2f window_size = sf::Vector2f(static_cast<float>(game_window->getSize().x), static_cast<float>(game_window->getSize().y));

        background_rectangle->initialize(window_size, sf::Vector2f(0.f, 0.f), 0, background_color);
        background_rectangle->show();
    }

    void LevelView::calculateGridExtents()
    {
        sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();
        grid_width = game_window->getSize().x - (2 * border_left_offset);
        grid_height = game_window->getSize().y - (2 * border_top_offset);
    }

    void LevelView::initializeBorder()
    {
        sf::Vector2f border_size(grid_width, grid_height);
        sf::Vector2f border_position(border_left_offset, border_top_offset);

        border_rectangle->initialize(border_size, border_position, border_thickness, sf::Color::Transparent, sf::Color::Black);
        border_rectangle->show();
    }

    float LevelView::getGridWidth()
    {
        return grid_width;
    }

    float LevelView::getGridHeight()
    {
        return grid_height;
    }
}
