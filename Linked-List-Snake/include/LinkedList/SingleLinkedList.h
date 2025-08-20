#pragma once
#include <SFML/System/Vector2.hpp>
#include "LinkedList/Node.h"
#include "Player/Direction.h"

namespace LinkedList
{
	class SingleLinkedList
	{
	private:

		LinkedList::Node* head_node;
		float node_width;
		float node_height;

		sf::Vector2i default_position;
		Player::Direction default_direction;

		LinkedList::Node* createNode();

	public:


		SingleLinkedList();
		~SingleLinkedList();
		void createHeadNode();

		void initialize(float width, float height, sf::Vector2i position, Player::Direction direction);
		void render();
	};
}