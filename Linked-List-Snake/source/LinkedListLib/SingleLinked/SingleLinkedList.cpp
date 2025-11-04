#include "LinkedListLib/SingleLinked/SingleLinkedList.h"

namespace LinkedListLib
{
    namespace SingleLinked
    {
        SingleLinkedList::SingleLinkedList() = default;

        SingleLinkedList::~SingleLinkedList() = default;

        Node* SingleLinkedList::createNode()
        {
            return new Node();
        }

        void SingleLinkedList::insertNodeAtHead()
        {
            Node* new_node = createNode();
            initializeNode(new_node, head_node, Operation::HEAD);
            new_node->next = head_node;
            head_node = new_node;
            linked_list_size++;
        }

        void SingleLinkedList::insertNodeAtTail()
        {
            Node* new_node = createNode();
            if (!head_node)
            {
                head_node = new_node;
                initializeNode(new_node, nullptr, Operation::HEAD);
            }
            else
            {
                Node* current_node = head_node;
                while (current_node->next)
                {
                    current_node = current_node->next;
                }
                current_node->next = new_node;
                initializeNode(new_node, current_node, Operation::TAIL);
            }
            linked_list_size++;
        }

        void SingleLinkedList::insertNodeAtMiddle()
        {
            int middle_node_index = findMiddleNode();
            insertNodeAtIndex(middle_node_index);
        }

         void SingleLinkedList::insertNodeAtIndex(int index)
        {
            if (index < 0 || index > linked_list_size)
            {
                return;
            }

            Node* new_node = createNode();

            if (index == 0)
            {
                initializeNode(new_node, head_node, Operation::HEAD);
                new_node->next = head_node;
                head_node = new_node;
                linked_list_size++;
            }
            else
            {
                Node* current_node = head_node;
                Node* previous_node = nullptr;
                for (int i = 0; i < index; ++i)
                {
                    previous_node = current_node;
                    current_node = current_node->next;
                }
                shiftNodesAfterInsertion(new_node, current_node, previous_node);
            }
        }

        void SingleLinkedList::shiftNodesAfterInsertion(Node* new_node, Node* cur_node, Node* prev_node)
        {
            prev_node->next = new_node;
            new_node->next = cur_node;

            initializeNode(new_node, prev_node, Operation::TAIL);
            linked_list_size++;
        }

        void SingleLinkedList::removeNodeAtHead()
        {
            if (!head_node)
            {
                return;
            }
            Node* node_to_delete = head_node;
            head_node = head_node->next;
            delete node_to_delete;
            linked_list_size--;
        }

        void SingleLinkedList::removeNodeAtTail()
        {
            if (!head_node)
            {
                return;
            }
            if (!head_node->next)
            {
                delete head_node;
                head_node = nullptr;
            }
            else
            {
                Node* current_node = head_node;
                while (current_node->next && current_node->next->next)
                {
                    current_node = current_node->next;
                }
                delete current_node->next;
                current_node->next = nullptr;
            }
            linked_list_size--;
        }

        void SingleLinkedList::removeNodeAtMiddle()
        {
            int middle_node_index = findMiddleNode();
            removeNodeAtIndex(middle_node_index);
        }

        void SingleLinkedList::removeNodeAt(int index)
        {
            if (index < 0 || index >= linked_list_size)
            {
                return;
            }

            if (index == 0)
            {
                removeNodeAtHead();
            }
            else
            {
                Node* current_node = head_node;
                Node* previous_node = nullptr;
                for (int i = 0; i < index; ++i)
                {
                    previous_node = current_node;
                    current_node = current_node->next;
                }
                previous_node->next = current_node->next;
                delete current_node;
                linked_list_size--;
            }
        }

        void SingleLinkedList::removeNodeAtIndex(int index)
        {
            if (index < 0 || index >= linked_list_size)
            {
                return;
            }

            if (index == 0)
            {
                removeNodeAtHead();
            }
            else
            {
                Node* current_node = head_node;
                Node* previous_node = nullptr;
                for (int i = 0; i < index; ++i)
                {
                    previous_node = current_node;
                    current_node = current_node->next;
                }
                previous_node->next = current_node->next;
                delete current_node;
                linked_list_size--;
            }
        }

        void SingleLinkedList::removeAllNodes()
        {
            Node* current_node = head_node;
            while (current_node)
            {
                Node* node_to_delete = current_node;
                current_node = current_node->next;
                delete node_to_delete;
            }
            head_node = nullptr;
            linked_list_size = 0;
        }

        void SingleLinkedList::removeHalfNodes()
        {
            int nodes_to_remove = linked_list_size / 2;
            for (int i = 0; i < nodes_to_remove; ++i)
            {
                removeNodeAtTail();
            }
        }

        void SingleLinkedList::shiftNodesAfterRemoval(Node* cur_node)
        {
            if (!cur_node || !cur_node->next)
            {
                return;
            }
            cur_node->body_part.setPosition(cur_node->next->body_part.getPosition());
            shiftNodesAfterRemoval(cur_node->next);
        }

        Player::Direction SingleLinkedList::reverse()
        {
            if (!head_node || !head_node->next)
            {
                if (head_node)
                {
                    return head_node->body_part.getDirection();
                }
                return Player::Direction::RIGHT;
            }

            Node* previous_node = nullptr;
            Node* current_node = head_node;
            Node* next_node = nullptr;

            while (current_node)
            {
                next_node = current_node->next;
                current_node->next = previous_node;
                previous_node = current_node;
                current_node = next_node;
            }
            head_node = previous_node;

            reverseNodeDirections();
            return head_node->body_part.getDirection();
        }

        void SingleLinkedList::reverseNodeDirections()
        {
            if (!head_node)
            {
                return;
            }

            Node* current_node = head_node;
            Player::Direction previous_direction = getReverseDirection(current_node->body_part.getDirection());
            current_node->body_part.setDirection(previous_direction);

            while (current_node->next)
            {
                previous_direction = current_node->body_part.getDirection();
                current_node = current_node->next;
                Player::Direction current_direction = getReverseDirection(current_node->body_part.getDirection());
                current_node->body_part.setDirection(previous_direction);
                previous_direction = current_direction;
            }
        }
    }
}
