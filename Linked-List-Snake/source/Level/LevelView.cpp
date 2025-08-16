#include "../../include/Level/LevelView.h"
#include "../../include/Global/ServiceLocator.h"

namespace Level
{
    using namespace Global;
    using namespace UI::UIElement;

    LevelView::LevelView()
    {
        background_rectangle = new RectangleShapeView();
    }

    LevelView::~LevelView()
    {
        delete background_rectangle;
    }

    void LevelView::initialize()
    {
        initializeBackground();
    }

    void LevelView::update()
    {
        background_rectangle->update();
    }

    void LevelView::render()
    {
        background_rectangle->render();
    }

    void LevelView::initializeBackground()
    {
        sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();
        sf::Vector2f window_size = sf::Vector2f(static_cast<float>(game_window->getSize().x), static_cast<float>(game_window->getSize().y));

        background_rectangle->initialize(window_size, sf::Vector2f(0.f, 0.f), 0, background_color);
        background_rectangle->show();
    }
}
