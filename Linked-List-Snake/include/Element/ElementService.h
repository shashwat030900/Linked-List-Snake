#pragma once
#include <vector>
#include "Element/Obstacle.h"


namespace Element {

	class ElementService {
	
	public:
		ElementService();
		~ElementService();

		void initialize();
		void render();
		void update();
	
	
	
	
	
	private:

		std::vector<Obstacle*> obstacle_list;
		void spawnObstacle(sf::Vector2i position, float cell_width, float cell_height);
	
	
	
	
	
	
	
	
	
	
	
	};













}