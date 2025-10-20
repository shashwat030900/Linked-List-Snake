#pragma once
#include <SFML/System/Vector2.hpp>
#include "LinkedList/Node.h"
#include "Player/Direction.h"

namespace LinkedList
{
	enum class Operation
	{
		HEAD,
		MID,
		TAIL,
	};


	class SingleLinkedList
	{
	private:

		LinkedList::Node* head_node;
		float node_width;
		float node_height;

		sf::Vector2i default_position;
		Player::Direction default_direction;

		LinkedList::Node* createNode();
		sf::Vector2i getNewNodePosition(Node* reference_node, Operation operation);
		
		void removeNodeAtHead();
		
		

	public:

		void updateNodePosition();
		SingleLinkedList();
		~SingleLinkedList();
		void insertNodeAtTail();
		void  updateNodeDirection(Player::Direction direction_to_set);

		void initialize(float width, float height, sf::Vector2i position, Player::Direction direction);
		void render();
		bool processNodeCollision();
		void removeAllNodes();
		void removeNodeAtTail();
		void removeNodeAtMiddle(int position);
		void removeHalfNodes();
		void reverse();
		std::vector<sf::Vector2i> getNodesPositionList();
		LinkedList::Node* getHeadNode();
		int getLength();
		void initializeNode(Node* new_node, Node* reference_node, Operation operation);
	};
}