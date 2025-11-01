#pragma once
#include "LinkedListLib/Node.h"


enum class Operation
{
    HEAD,
    MID,
    TAIL,
};

namespace LinkedListLib
{
    class LinkedList {

        protected:
            Node* head_node;
            float node_width;
            float node_height;
            sf::Vector2i default_position;
            Direction default_direction;
            int linked_list_size;




    };
}