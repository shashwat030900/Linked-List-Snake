#include "LinkedList/SingleLinkedList.h"
#include "Player/BodyPart.h"
#include "Level/LevelView.h"
#include "Player/SnakeController.h"

namespace LinkedList
{
	using namespace Player;
	

	SingleLinkedList::SingleLinkedList()
		: head_node(nullptr)
		, node_width(0.0f)
		, node_height(0.0f)
		, default_position(0, 0)
		, default_direction(Direction::RIGHT)  
		, linked_list_size(0)
	{
	}

	
	SingleLinkedList::~SingleLinkedList()
	{
		removeAllNodes();  // Ensure proper cleanup
	}


	void SingleLinkedList::initialize(float width, float height, sf::Vector2i position, Direction direction)
	{
		node_width = width;
		node_height = height;
		default_position = position;
		default_direction = direction;
		linked_list_size = 0;
	}

	void SingleLinkedList::render() {
		
		Node* cur_node = head_node;

			while(cur_node != nullptr) {
				cur_node->body_part.updatePosition();
				cur_node->body_part.render();
				cur_node = cur_node->next;
		}

		// head_node->body_part.render();

	}

	Node* SingleLinkedList::createNode()
	{
		return new Node();
	}


	sf::Vector2i SingleLinkedList::getNewNodePosition(Node* reference_node, Operation operation)
	{
		switch (operation)
		{
		case Operation::HEAD:
			return reference_node->body_part.getNextPosition();
		case Operation::TAIL:
			return reference_node->body_part.getPrevPosition();
		}

		return default_position;

		
	}

	void SingleLinkedList::insertNodeAtTail() {	

		linked_list_size++;
		Node* new_node = createNode();
		Node* cur_node = head_node;

		if(cur_node == nullptr){
		
			head_node = new_node;
			new_node->body_part.initialize(node_width, node_height, default_position, default_direction);
			return;

		
		
		}
		while (cur_node->next != nullptr) {
			cur_node = cur_node->next;
		}

		cur_node->next = new_node;
		
        new_node->body_part.initialize(node_width,node_height,getNewNodePosition(cur_node, Operation::TAIL),cur_node->body_part.getDirection());
		

	}

	void SingleLinkedList::updateNodeDirection(Direction direction_to_set)
	{
		Node* cur_node = head_node;
		while (cur_node != nullptr) {
			Direction previous_direction = cur_node->body_part.getDirection();
			cur_node->body_part.setDirection(direction_to_set);
			direction_to_set = previous_direction; 
			cur_node = cur_node->next;
		}
		
	}

	void SingleLinkedList::updateNodePosition()
	{
		if (head_node == nullptr) {
			return;
		}

		sf::Vector2i previous_position = head_node->body_part.getPosition();
		sf::Vector2i next_head_position = head_node->body_part.getNextPosition();
		head_node->body_part.setPosition(next_head_position);

		Node* current_node = head_node->next;
		while (current_node != nullptr) {
			sf::Vector2i temp_position = current_node->body_part.getPosition();
			current_node->body_part.setPosition(previous_position);
			previous_position = temp_position;
			current_node = current_node->next;
		}
	}

	bool SingleLinkedList::processNodeCollision()
	{
		if (head_node == nullptr) return false;

		sf::Vector2i predicted_position = head_node->body_part.getNextPosition();

		Node* cur_node = head_node->next;
		while (cur_node != nullptr) {
			if (cur_node->body_part.getPosition() == predicted_position) {
				return true; 
				
			}
			cur_node = cur_node->next;
			
		}
		return false;
	}
	void SingleLinkedList::removeNodeAtHead()
	{
		linked_list_size--;
		Node* cur_node = head_node;
		head_node = head_node->next;

		cur_node->next = nullptr;
		delete (cur_node);
	}

	void SingleLinkedList::removeAllNodes()
	{
		if (head_node == nullptr) return;

		while (head_node != nullptr) {
			removeNodeAtHead();
		}
	}
	std::vector<sf::Vector2i> SingleLinkedList::getNodesPositionList()
	{
		std::vector<sf::Vector2i> nodes_position_list;

		Node* cur_node = head_node;

		while (cur_node != nullptr)
		{
			nodes_position_list.push_back(cur_node->body_part.getPosition());
			cur_node = cur_node->next;
		}

		return nodes_position_list;
	}

	LinkedList::Node* SingleLinkedList::getHeadNode()
	{
		return head_node;
	}

	void SingleLinkedList::initializeNode(Node* new_node, Node* reference_node, Operation operation)
	{
		if (reference_node == nullptr)
		{
			new_node->body_part.initialize(node_width, node_height, default_position, default_direction);
			return;
		}

		sf::Vector2i position = getNewNodePosition(reference_node, operation);

		new_node->body_part.initialize(node_width, node_height, position, reference_node->body_part.getDirection());
	}

	void SingleLinkedList::insertNodeAtHead()
	{
		linked_list_size++;
		Node* new_node = createNode();

		if (head_node == nullptr)
		{
			head_node = new_node;
			initializeNode(new_node, nullptr, Operation::HEAD);
			return;
		}

		initializeNode(new_node, head_node, Operation::HEAD);
		new_node->next = head_node;
		head_node = new_node;
	}


	void SingleLinkedList::insertNodeAtIndex(int index)
	{
		if (index < 0 || index >= linked_list_size) return;

		if (index == 0)
		{
			insertNodeAtHead();
			return;
		}

		Node* new_node = createNode();
		if (!new_node) return;
		int current_index = 0;
		Node* cur_node = head_node;
		Node* prev_node = nullptr;

		while (cur_node != nullptr && current_index < index)
		{
			prev_node = cur_node;
			cur_node = cur_node->next;
			current_index++;
		}
		if (prev_node == nullptr) return;
		prev_node->next = new_node;
		new_node->next = cur_node;
		initializeNode(new_node, prev_node, Operation::TAIL);
		linked_list_size++;
		shiftNodesAfterInsertion(new_node, cur_node, prev_node);
	}


	void SingleLinkedList::shiftNodesAfterInsertion(Node* new_node, Node* cur_node, Node* prev_node)
	{
		if (!new_node || !cur_node || !prev_node) return;
		Node* next_node = cur_node;
		cur_node = new_node;

		while (cur_node != nullptr && next_node != nullptr)
		{
			cur_node->body_part.setPosition(next_node->body_part.getPosition());
			cur_node->body_part.setDirection(next_node->body_part.getDirection());

			prev_node = cur_node;
			cur_node = next_node;
			next_node = next_node->next;
		}

		if (cur_node != nullptr)  
		{
			initializeNode(cur_node, prev_node, Operation::TAIL);
		}
	}


	int SingleLinkedList::findMiddleNode()
	{
		if (!head_node) return 0;
		Node* slow = head_node;
		Node* fast = head_node;
		int midIndex = 0;  

		while (fast != nullptr && fast->next != nullptr) {
			slow = slow->next;
			fast = fast->next->next;
			midIndex++;
		}
		return midIndex;
	}


	void SingleLinkedList::insertNodeAtMiddle()
	{
		if (head_node == nullptr) {
			insertNodeAtHead();             
			return;
		}

		int midIndex = findMiddleNode();   
		insertNodeAtIndex(midIndex);                       
	}

	

	void SingleLinkedList::removeNodeAt(int index)
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
		removeNodeAtIndex(index);
	}

	void SingleLinkedList::removeNodeAtIndex(int index)
	{
		Node* cur_node = head_node;
		Node* prev_node = nullptr;
		int current_index = 0;

		while (cur_node != nullptr && current_index < index)
		{
			prev_node = cur_node;
			cur_node = cur_node->next;
			current_index++;
		}

		prev_node->next = cur_node->next;
		linked_list_size--;
		shiftNodesAfterRemoval(cur_node);
		delete (cur_node);
	}

	void SingleLinkedList::shiftNodesAfterRemoval(Node* cur_node)
	{
		sf::Vector2i position_to_set = cur_node->body_part.getPosition();
		Player::Direction direction_to_set = cur_node->body_part.getDirection();

		cur_node = cur_node->next;

		while (cur_node != nullptr)
		{
			sf::Vector2i prev_position = cur_node->body_part.getPosition();
			Player::Direction prev_direction = cur_node->body_part.getDirection();

			cur_node->body_part.setPosition(position_to_set);
			cur_node->body_part.setDirection(direction_to_set);

			position_to_set = prev_position;
			direction_to_set = prev_direction;

			cur_node = cur_node->next;
		}
	}

	void SingleLinkedList::removeNodeAtMiddle()
	{
		if (head_node == nullptr) return;
		int mid_index = findMiddleNode();
		removeNodeAt(mid_index);
	}
	
	void SingleLinkedList::removeNodeAtTail()
	{
		if (head_node == nullptr) return;
		linked_list_size--; 

		Node* cur_node = head_node;

		if (cur_node->next == nullptr)
		{
			removeNodeAtHead();
			return;
		}

		while (cur_node->next->next != nullptr)
		{
			cur_node = cur_node->next;
		}

		delete (cur_node->next);
		cur_node->next = nullptr; 
	}

	Node* SingleLinkedList::findNodeAtIndex(int index)
	{
		if (index < 0 || index >= linked_list_size) return nullptr;

		Node* cur_node = head_node;
		int current_index = 0;

		while (cur_node != nullptr && current_index < index)
		{
			cur_node = cur_node->next;
			current_index++;
		}

		return cur_node;
	}

	void SingleLinkedList::removeHalfNodes()
	{
		if (linked_list_size <= 1) return;
		int half_length = linked_list_size / 2;
		int new_tail_index = half_length - 1;

		Node* prev_node = findNodeAtIndex(new_tail_index);
		Node* cur_node = prev_node->next;

		while (cur_node != nullptr)
		{
			Node* node_to_delete = cur_node;
			cur_node = cur_node->next;

			delete (node_to_delete);
			linked_list_size--;
		}

		prev_node->next = nullptr;
	}

	Player::Direction SingleLinkedList::getReverseDirection(Player::Direction reference_direction)
	{
		switch (reference_direction)
		{
		case Player::Direction::UP:
			return Player::Direction::DOWN;
		case Player::Direction::DOWN:
			return Player::Direction::UP;
		case Player::Direction::LEFT:
			return Player::Direction::RIGHT;
		case Player::Direction::RIGHT:
			return Player::Direction::LEFT;
		default:
			return Player::Direction::RIGHT;
		}
	}

	void SingleLinkedList::reverseNodeDirections()
	{
		Node* curr_node = head_node;
		while (curr_node != nullptr)
		{
			curr_node->body_part.setDirection(getReverseDirection(curr_node->body_part.getPreviousDirection()));
			curr_node = curr_node->next;
		}
	}

	Player::Direction SingleLinkedList::reverse()
	{
		Node* cur_node = head_node;
		Node* prev_node = nullptr;
		Node* next_node = nullptr;
		while (cur_node != nullptr)
		{
			next_node = cur_node->next;
			cur_node->next = prev_node;
			prev_node = cur_node;
			cur_node = next_node;
		}
		head_node = prev_node;
		reverseNodeDirections();
		return head_node->body_part.getDirection();
	}

}