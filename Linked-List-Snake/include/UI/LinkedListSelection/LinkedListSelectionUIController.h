#pragma once
#include "UI/Interface/IUIController.h"
#include "UI/UIElement/ImageView.h"
#include "UI/UIElement/ButtonView.h"

namespace UI
{
    namespace LinkedListSelection
    {
        class LinkedListSelectionUIController : public Interface::IUIController
        {
        private:
            // Constants:
            const float button_width = 400.f;
            const float button_height = 140.f;

            const float single_linked_list_button_y_position = 500.f;
            const float double_linked_list_button_y_position = 700.f;
            const float menu_button_y_position = 900.f;

            const float background_alpha = 85.f;

            // UI Elements:
            UIElement::ImageView* background_image;
            UIElement::ButtonView* single_linked_list_button;
            UIElement::ButtonView* double_linked_list_button;
            UIElement::ButtonView* menu_button;

            // Private methods:
            void createViews();
            void initializeViews();
            void registerButtonCallbacks();
            void destroy();

            // Callback methods:
            void singleLinkedListButtonCallback();
            void doubleLinkedListButtonCallback();
            void menuButtonCallback();

        public:
            LinkedListSelectionUIController();
            ~LinkedListSelectionUIController();

            void initialize() override;
            void update() override;
            void render() override;
            void show() override;
        };
    }
}