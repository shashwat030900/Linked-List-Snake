#include "UI/LevelSelection/LevelSelectionUIController.h"
#include "Global/ServiceLocator.h"
#include "Global/Config.h"
#include "Main/GameService.h"
#include "Level/LevelService.h"
#include "Sound/SoundService.h"

namespace UI
{
    namespace LevelSelection
    {
        using namespace Global;
        using namespace Main;
        using namespace Level;
        using namespace Sound;
        using namespace UIElement;

        LevelSelectionUIController::LevelSelectionUIController()
        {
            createViews();
        }

        LevelSelectionUIController::~LevelSelectionUIController()
        {
            destroy();
        }

        void LevelSelectionUIController::initialize()
        {
            initializeViews();
            registerButtonCallbacks();
        }

        void LevelSelectionUIController::createViews()
        {
            background_image = new ImageView();
            level_one_button = new ButtonView();
            level_two_button = new ButtonView();
            menu_button = new ButtonView();
        }

        void LevelSelectionUIController::initializeViews()
        {
            sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();
            background_image->initialize(Config::background_texture_path, game_window->getSize().x, game_window->getSize().y, sf::Vector2f(0, 0));
            background_image->setImageAlpha(background_alpha);

            level_one_button->initialize("Level One Button", Config::level_one_button_texture_path, button_width, button_height, sf::Vector2f(0, level_one_button_y_position));
            level_two_button->initialize("Level Two Button", Config::level_two_button_texture_path, button_width, button_height, sf::Vector2f(0, level_two_button_y_position));
            menu_button->initialize("Menu Button", Config::menu_button_texture_path, button_width, button_height, sf::Vector2f(0, menu_button_y_position));

            level_one_button->setCentreAlinged();
            level_two_button->setCentreAlinged();
            menu_button->setCentreAlinged();
        }

        void LevelSelectionUIController::registerButtonCallbacks()
        {
            level_one_button->registerCallbackFuntion(std::bind(&LevelSelectionUIController::levelOneCallback, this));
            level_two_button->registerCallbackFuntion(std::bind(&LevelSelectionUIController::levelTwoCallback, this));
            menu_button->registerCallbackFuntion(std::bind(&LevelSelectionUIController::menuButtonCallback, this));
        }

        void LevelSelectionUIController::levelOneCallback()
        {
            ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
            ServiceLocator::getInstance()->getLevelService()->createLevel(LevelNumber::ONE);
            GameService::setGameState(GameState::LINKED_LIST_SELECTION);
        }

        void LevelSelectionUIController::levelTwoCallback()
        {
            ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
            ServiceLocator::getInstance()->getLevelService()->createLevel(LevelNumber::TWO);
            GameService::setGameState(GameState::LINKED_LIST_SELECTION);
        }

        void LevelSelectionUIController::menuButtonCallback()
        {
            ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
            GameService::setGameState(GameState::MAIN_MENU);
        }

        void LevelSelectionUIController::update()
        {
            background_image->update();
            level_one_button->update();
            level_two_button->update();
            menu_button->update();
        }

        void LevelSelectionUIController::render()
        {
            background_image->render();
            level_one_button->render();
            level_two_button->render();
            menu_button->render();
        }

        void LevelSelectionUIController::show()
        {
            background_image->show();
            level_one_button->show();
            level_two_button->show();
            menu_button->show();
        }

        void LevelSelectionUIController::destroy()
        {
            delete background_image;
            delete level_one_button;
            delete level_two_button;
            delete menu_button;
        }
    }
}
