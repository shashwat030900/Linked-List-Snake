#include "UI/LinkedListSelection/LinkedListSelectionUIController.h"
#include "Global/ServiceLocator.h"
#include "Global/Config.h"
#include "Main/GameService.h"
#include "Player/PlayerService.h"
#include "Sound/SoundService.h"
#include "Player/SnakeController.h"
#include "Level/LevelConfig.h"

namespace UI
{
    namespace LinkedListSelection
    {
        using namespace Global;
        using namespace Main;
        using namespace Player;
        using namespace Sound;
        using namespace UIElement;
        using namespace Level;

        LinkedListSelectionUIController::LinkedListSelectionUIController()
        {
            createViews();
        }

        LinkedListSelectionUIController::~LinkedListSelectionUIController()
        {
            destroy();
        }

        void LinkedListSelectionUIController::initialize()
        {
            initializeViews();
            registerButtonCallbacks();
        }

        void LinkedListSelectionUIController::createViews()
        {
            background_image = new ImageView();
            single_linked_list_button = new ButtonView();
            double_linked_list_button = new ButtonView();
            menu_button = new ButtonView();
        }

        void LinkedListSelectionUIController::initializeViews()
        {
            sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();
            background_image->initialize(Config::background_texture_path, game_window->getSize().x, game_window->getSize().y, sf::Vector2f(0, 0));
            background_image->setImageAlpha(background_alpha);

            single_linked_list_button->initialize("Single Linked List Button", Config::single_linked_list_button_texture_path, button_width, button_height, sf::Vector2f(0, single_linked_list_button_y_position));
            double_linked_list_button->initialize("Double Linked List Button", Config::double_linked_list_button_texture_path, button_width, button_height, sf::Vector2f(0, double_linked_list_button_y_position));
            menu_button->initialize("Menu Button", Config::menu_button_texture_path, button_width, button_height, sf::Vector2f(0, menu_button_y_position));

            single_linked_list_button->setCentreAlinged();
            double_linked_list_button->setCentreAlinged();
            menu_button->setCentreAlinged();
        }

        void LinkedListSelectionUIController::registerButtonCallbacks()
        {
            single_linked_list_button->registerCallbackFuntion(std::bind(&LinkedListSelectionUIController::singleLinkedListCallback, this));
            double_linked_list_button->registerCallbackFuntion(std::bind(&LinkedListSelectionUIController::doubleLinkedListCallback, this));
            menu_button->registerCallbackFuntion(std::bind(&LinkedListSelectionUIController::menuButtonCallback, this));
        }

        void LinkedListSelectionUIController::singleLinkedListCallback()
        {
            ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
            SnakeController::setLinkedListType(Level::LinkedListType::SINGLE_LINKED_LIST);
            GameService::setGameState(GameState::GAMEPLAY);
        }

        void LinkedListSelectionUIController::doubleLinkedListCallback()
        {
            ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
            SnakeController::setLinkedListType(Level::LinkedListType::DOUBLE_LINKED_LIST);
            GameService::setGameState(GameState::GAMEPLAY);
        }

        void LinkedListSelectionUIController::menuButtonCallback()
        {
            ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
            GameService::setGameState(GameState::MAIN_MENU);
        }

        void LinkedListSelectionUIController::update()
        {
            background_image->update();
            single_linked_list_button->update();
            double_linked_list_button->update();
            menu_button->update();
        }

        void LinkedListSelectionUIController::render()
        {
            background_image->render();
            single_linked_list_button->render();
            double_linked_list_button->render();
            menu_button->render();
        }

        void LinkedListSelectionUIController::show()
        {
            background_image->show();
            single_linked_list_button->show();
            double_linked_list_button->show();
            menu_button->show();
        }

        void LinkedListSelectionUIController::destroy()
        {
            delete background_image;
            delete single_linked_list_button;
            delete double_linked_list_button;
            delete menu_button;
        }
    }
}