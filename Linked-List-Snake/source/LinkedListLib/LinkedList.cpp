#include "LinkedListLib/LinkedList.h"
#include "Player/Direction.h"
#include "Level/LevelView.h"

namespace LinkedListLib
{
    LinkedList::LinkedList()
    {
        head_node = nullptr;
        node_width = 0;
        node_height = 0;
        default_position = sf::Vector2i(0, 0);
        default_direction = Direction::RIGHT;
        linked_list_size = 0;
    }

    LinkedList::~LinkedList()
    {
        Node* current_node = head_node;
        while (current_node != nullptr)
        {
            Node* node_to_delete = current_node;
            current_node = current_node->next;
            delete node_to_delete;
        }
    }

    void LinkedList::initialize(float width, float height, sf::Vector2i position, Direction direction)
    {
        node_width = width;
        node_height = height;
        default_position = position;
        default_direction = direction;

        insertNodeAtHead();
    }

    
    void LinkedList::initializeNode(Node* new_node, Node* reference_node, Operation operation)
    {
        if (new_node)
        {
            sf::Vector2i position = getNewNodePosition(reference_node, operation);
            new_node->body_part.initialize(node_width, node_height, position, default_direction);
        }
    }

    sf::Vector2i LinkedList::getNewNodePosition(Node* reference_node, Operation operation)
    {
        if (!reference_node)
        {
            return default_position;
        }

        sf::Vector2i new_position = reference_node->body_part.getPosition();
        sf::Vector2i offset(static_cast<int>(node_width), 0);

        if (operation == Operation::TAIL)
        {
            new_position -= offset;
        }
        else
        {
            new_position += offset;
        }

        return new_position;
    }

    

    Node* LinkedList::getHeadNode()
    {
        return head_node;
    }

    

    Direction LinkedList::getReverseDirection(Direction reference_direction)
    {
        switch (reference_direction)
        {
        case Direction::LEFT:
            return Direction::RIGHT;
        case Direction::RIGHT:
            return Direction::LEFT;
        case Direction::UP:
            return Direction::DOWN;
        case Direction::DOWN:
            return Direction::UP;
        }
    }

    
}