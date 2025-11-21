#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Element/ElementData.h"
#include "Element/Obstacle.h"
#include "LinkedListLib/SingleLinked/SingleLinkedList.h"
#include "LinkedListLib/Node.h"

namespace Element
{
	class Obstacle;
	struct ElementData;

	class ElementService
	{
	private:
		std::vector<Obstacle*> obstacle_list;

		void spawnObstacle(sf::Vector2i position, float cell_width, float cell_height);
		
	public:
		ElementService();
		~ElementService();

		void initialize();
		void update();
		void render();

		void spawnElements(std::vector<ElementData>& element_data_list, float cell_width, float cell_height);
		std::vector<sf::Vector2i> getElementsPositionList();
		bool processElementsCollision(LinkedListLib::Node* head_node);
		bool checkSnakeHeadCollision(LinkedListLib::Node* head_node);
	};
}