#include "../../include/Level/LevelView.h"
#include "../../include/Global/ServiceLocator.h"
#include "../../include/Global/Config.h"

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
        loadObstacleTexture();
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

    void LevelView::renderObstacles(const std::vector<std::vector<int>>& layout, float cell_width, float cell_height)
    {
        if (!obstacle_texture_loaded) return;

        sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();
        for (size_t i = 0; i < layout.size(); ++i)
        {
            for (size_t j = 0; j < layout[i].size(); ++j)
            {
                if (layout[i][j] == 1)
                {
                    obstacle_sprite.setPosition(border_left_offset + j * cell_width, border_top_offset + i * cell_height);
                    obstacle_sprite.setScale(cell_width / obstacle_sprite.getTexture()->getSize().x, cell_height / obstacle_sprite.getTexture()->getSize().y);
                    game_window->draw(obstacle_sprite);
                }
            }
        }
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

    void LevelView::loadObstacleTexture()
    {
        if (obstacle_texture.loadFromFile(Config::obstacle_texture_path))
        {
            obstacle_sprite.setTexture(obstacle_texture);
            obstacle_texture_loaded = true;
        }
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
