#ifndef PATHFINDINGALGORITHMS_H_INCLUDED
#define PATHFINDINGALGORITHMS_H_INCLUDED

#include "Algorithms.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Dijkstra : public PathFindingAlgorithms
{
public:
	Dijkstra(sf::RenderWindow& win);
	int Visualize(std::unique_ptr<Interface>& init);
};

#endif // PATHFINDINGALGORITHMS_H_INCLUDED
