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
            linked_list_size++;
            Node* new_node = createNode();

            if (head_node == nullptr)
            {
                head_node = new_node;
                static_cast<DoubleNode*>(new_node)->previous = nullptr;
                initializeNode(new_node, nullptr, Operation::HEAD);
                return;
            }

            initializeNode(new_node, head_node, Operation::HEAD);

            new_node->next = head_node;
            static_cast<DoubleNode*>(head_node)->previous = new_node;

            head_node = new_node;
        }

        void DoubleLinkedList::insertNodeAtTail()
        {
            linked_list_size++;
            Node* new_node = createNode();
            Node* cur_node = head_node;

            if (cur_node == nullptr)
            {
                head_node = new_node;
                static_cast<DoubleNode*>(new_node)->previous = nullptr;
                initializeNode(new_node, nullptr, Operation::TAIL);
                return;
            }

            while (cur_node->next != nullptr)
            {
                cur_node = cur_node->next;
            }

            cur_node->next = new_node;
            static_cast<DoubleNode*>(new_node)->previous = cur_node;
            initializeNode(new_node, cur_node, Operation::TAIL);
        }

        void DoubleLinkedList::insertNodeAtMiddle()
        {
            int middle_node_index = findMiddleNode();
            insertNodeAtIndex(middle_node_index);
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
            

            Node* new_node = createNode();
            Node* current_node = head_node;
            Node* previous_node = nullptr;

            for (int i = 0; i < index; ++i)
            {
                previous_node = current_node;
                current_node = current_node->next;
            }

            shiftNodesAfterInsertion(new_node, current_node, previous_node);
        }

        void DoubleLinkedList::shiftNodesAfterInsertion(Node* new_node, Node* cur_node, Node* prev_node)
        {
            prev_node->next = new_node;
            static_cast<DoubleNode*>(new_node)->previous = prev_node;
            new_node->next = cur_node;

            if (cur_node)
            {
                static_cast<DoubleNode*>(cur_node)->previous = new_node;
            }

            initializeNode(new_node, prev_node, Operation::TAIL);
            linked_list_size++;
        }

        void DoubleLinkedList::removeNodeAtHead() {
            linked_list_size--;

            Node* cur_node = head_node;
            head_node = head_node->next;

            if (head_node != nullptr) {
                static_cast<DoubleNode*>(head_node)->previous = nullptr;
            }

            cur_node->next = nullptr;
            delete cur_node;
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

        
        Direction DoubleLinkedList::reverse()
        {
            if (!head_node || !head_node->next)
            {
                return head_node ? head_node->body_part.getDirection() : Direction::RIGHT;
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
