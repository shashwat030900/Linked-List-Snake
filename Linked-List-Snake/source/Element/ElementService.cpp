#include "Element/ElementService.h"
#include "Element/ElementData.h"
#include "Element/Obstacle.h"
#include "Global/ServiceLocator.h"
#include "Level/LevelController.h"
#include "Level/LevelView.h"
#include "Level/LevelService.h"
#include "LinkedList/SingleLinkedList.h"

namespace Element
{
    ElementService::ElementService() = default;
    ElementService::~ElementService() = default;

    void ElementService::initialize() {}

    void ElementService::update()
    {
        for (size_t i = 0; i < obstacle_list.size(); i++)
        {
            obstacle_list[i]->update();
        }
    }

    void ElementService::render()
    {
        for (size_t i = 0; i < obstacle_list.size(); i++)
        {
            obstacle_list[i]->render();
        }
    }

    void ElementService::spawnElements(std::vector<ElementData>& element_data_list, float cell_width, float cell_height)
    {
        for (size_t i = 0; i < element_data_list.size(); i++)
        {
            switch (element_data_list[i].element_type)
            {
            case Element::ElementType::OBSTACLE:
                spawnObstacle(element_data_list[i].position, cell_width, cell_height);
                break;
            }
        }
    }

    void ElementService::spawnObstacle(sf::Vector2i position, float cell_width, float cell_height)
    {
        Level::LevelView* level_view = Global::ServiceLocator::getInstance()->getLevelService()->getLevelView();
        Obstacle* obstacle = new Obstacle(level_view);
        obstacle->initialize(position, cell_width, cell_height);
        obstacle_list.push_back(obstacle);
    }

    std::vector<sf::Vector2i> ElementService::getElementsPositionList()
    {
        std::vector<sf::Vector2i> elements_position_list;
        for (size_t i = 0; i < obstacle_list.size(); i++)
        {
            elements_position_list.push_back(obstacle_list[i]->getObstaclePosition());
        }
        return elements_position_list;
    }

    bool ElementService::processElementsCollision(LinkedList::Node* head_node)
    {
        for (size_t i = 0; i < obstacle_list.size(); i++)
        {
            if (obstacle_list[i]->getObstaclePosition() == head_node->body_part.getNextPosition() ||
                obstacle_list[i]->getObstaclePosition() == head_node->body_part.getPosition())
            {
                return true;
            }
        }
        return false;
    }

    bool ElementService::checkSnakeHeadCollision(LinkedList::Node* head_node)
    {
        if (head_node == nullptr) return false;

        sf::Vector2i predicted_position = head_node->body_part.getNextPosition();

        LinkedList::Node* cur_node = head_node->next;
        while (cur_node != nullptr) {
            if (cur_node->body_part.getPosition() == predicted_position) {
                return true;

            }
            cur_node = cur_node->next;

        }

        for (int i = 0; i < obstacle_list.size(); i++)
        {
            if (obstacle_list[i]->getObstaclePosition() == predicted_position)
            {
                return true;
            }
        }

        return false;
    }

}