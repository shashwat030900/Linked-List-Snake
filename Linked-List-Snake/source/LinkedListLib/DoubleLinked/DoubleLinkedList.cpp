#include "LinkedListLib/DoubleLinked/DoubleLinkedList.h"
#include "LinkedListLib/DoubleLinked/DoubleNode.h"

namespace LinkedListLib
{
    namespace DoubleLinked
    {
        DoubleLinkedList::DoubleLinkedList() = default;

        DoubleLinkedList::~DoubleLinkedList() = default;

        Node* DoubleLinkedList::createNode()
        {
            return new DoubleNode();
        }

        void DoubleLinkedList::insertNodeAtHead()
        {
            Node* new_node = createNode();
            initializeNode(new_node, head_node, Operation::HEAD);

            if (head_node)
            {
                static_cast<DoubleNode*>(head_node)->previous = new_node;
            }
            new_node->next = head_node;
            head_node = new_node;
            linked_list_size++;
        }

        void DoubleLinkedList::insertNodeAtTail()
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
                static_cast<DoubleNode*>(new_node)->previous = current_node;
                initializeNode(new_node, current_node, Operation::TAIL);
            }
            linked_list_size++;
        }

        void DoubleLinkedList::insertNodeAtMiddle()
        {
            insertNodeAtIndex(findMiddleNode());
        }

        void DoubleLinkedList::insertNodeAtIndex(int index)
        {
            if (index < 0 || index > linked_list_size)
            {
                return;
            }
            if (index == 0)
            {
                insertNodeAtHead();
                return;
            }
            if (index == linked_list_size)
            {
                insertNodeAtTail();
                return;
            }

            Node* new_node = createNode();
            Node* current_node = findNodeAtIndex(index);
            Node* previous_node = static_cast<DoubleNode*>(current_node)->previous;

            shiftNodesAfterInsertion(new_node, current_node, previous_node);
        }

        void DoubleLinkedList::shiftNodesAfterInsertion(Node* new_node, Node* cur_node, Node* prev_node)
        {
            prev_node->next = new_node;
            static_cast<DoubleNode*>(new_node)->previous = prev_node;
            new_node->next = cur_node;
            static_cast<DoubleNode*>(cur_node)->previous = new_node;

            initializeNode(new_node, prev_node, Operation::TAIL);
            linked_list_size++;
        }

        void DoubleLinkedList::removeNodeAtHead()
        {
            if (!head_node) return;

            Node* node_to_delete = head_node;
            head_node = head_node->next;

            if (head_node)
            {
                static_cast<DoubleNode*>(head_node)->previous = nullptr;
            }

            delete node_to_delete;
            linked_list_size--;
        }

        void DoubleLinkedList::removeNodeAtTail()
        {
            if (!head_node) return;

            if (!head_node->next)
            {
                removeNodeAtHead();
                return;
            }

            Node* current_node = head_node;
            while (current_node->next)
            {
                current_node = current_node->next;
            }

            Node* prev_node = static_cast<DoubleNode*>(current_node)->previous;
            prev_node->next = nullptr;
            delete current_node;
            linked_list_size--;
        }

        void DoubleLinkedList::removeNodeAtMiddle()
        {
            removeNodeAtIndex(findMiddleNode());
        }

        void DoubleLinkedList::removeNodeAt(int index)
        {
            removeNodeAtIndex(index);
        }

        void DoubleLinkedList::removeNodeAtIndex(int index)
        {
            if (index < 0 || index >= linked_list_size) return;
            if (index == 0)
            {
                removeNodeAtHead();
                return;
            }
            if (index == linked_list_size - 1)
            {
                removeNodeAtTail();
                return;
            }

            Node* node_to_delete = findNodeAtIndex(index);
            Node* prev_node = static_cast<DoubleNode*>(node_to_delete)->previous;
            Node* next_node = node_to_delete->next;

            prev_node->next = next_node;
            static_cast<DoubleNode*>(next_node)->previous = prev_node;

            delete node_to_delete;
            linked_list_size--;
        }

        void DoubleLinkedList::removeAllNodes()
        {
            while (head_node)
            {
                removeNodeAtHead();
            }
        }

        void DoubleLinkedList::removeHalfNodes()
        {
            int nodes_to_remove = linked_list_size / 2;
            for (int i = 0; i < nodes_to_remove; ++i)
            {
                removeNodeAtTail();
            }
        }

        void DoubleLinkedList::shiftNodesAfterRemoval(Node* cur_node)
        {
            // This function is not applicable to a doubly linked list
            // as removal only requires pointer manipulation, not data shifting.
        }

        Direction DoubleLinkedList::reverse()
        {
            if (!head_node || !head_node->next)
            {
                return head_node ? head_node->body_part.getDirection() : Direction::NONE;
            }

            Node* temp = nullptr;
            Node* current = head_node;

            while (current)
            {
                temp = static_cast<DoubleNode*>(current)->previous;
                static_cast<DoubleNode*>(current)->previous = current->next;
                current->next = temp;
                current = static_cast<DoubleNode*>(current)->previous;
            }

            if (temp)
            {
                head_node = static_cast<DoubleNode*>(temp)->previous;
            }

            reverseNodeDirections();
            return head_node->body_part.getDirection();
        }
    }
}
