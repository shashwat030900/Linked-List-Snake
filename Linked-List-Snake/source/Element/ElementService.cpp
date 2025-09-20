#include "Element/ElementService.h"

namespace Element {
	ElementService::ElementService() {
	}
	ElementService::~ElementService() {
	}
	void ElementService::initialize() {
	}
	void ElementService::render() {
	}
	void ElementService::update() {
	}

	void ElementService::spawnObstacle(sf::Vector2i position, float cell_width, float cell_height)
	{
		Obstacle* obstacle = new Obstacle();
		obstacle->initialize(position, cell_width, cell_height);
		obstacle_list.push_back(obstacle);
	}
}
