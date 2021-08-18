#ifndef PATHFINDINGALGORITHMS_H_INCLUDED
#define PATHFINDINGALGORITHMS_H_INCLUDED

#include "Algorithms.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <map>																			// for connected nodes and edges
#include <tuple>			
#include <utility>																		// for representing an edge (std::pair)
#include <climits>																		// for interpreting infinity (LLONG_MAX)

typedef std::vector<int64_t> vect_int;													// alias for vector of ints
typedef std::pair<int64_t, int64_t> pair;												// alias for vector


class Dijkstra : public PathFindingAlgorithms
{
private:
	std::map<int64_t, vect_int> edges;
	std::map<pair, int64_t> weights;
	vect_int dist;
	vect_int previous;
	vect_int Q;
	vect_int unpoppedQ;
public:
	/**
	 * GRAPH class constructor + initialization list
	 * input: no. of vertices for the graph
	 * Initializes the graph,
	 */
	Dijkstra(std::vector<std::vector<Button>> g, int64_t s, int64_t e, sf::RenderWindow& win);
	/**
	 * ADD EDGE
	 * input: 2 nodes and a weight
	 * output: none
	 * Inserts an edge and its weigth
	 * to the graph
	 */
	int Dijkstra::Visualize(std::unique_ptr<Interface>& init);
	/**
	 * DIJKSTRA
	 * input: start node, end node
	 * output: shortest path from start to end
	 * Find the shortest path between 2 nodes specified
	 */
	void add_edge(int64_t from_node, int64_t to_node, int64_t weight);
	/**
	 * FIND SMALLEST NODE
	 * input: none
	 * output: the integer index of the smallest node
	 * Find the smallest with the lowest
	 * cost from the current node to another
	 */
	int findSmallestNode();
	/**
	 * GET INDEX
	 * input: a node index represented as a char
	 * output: the numerical index of the node
	 * Finds the numerical idx of a node's neighbour
	 */
	int getIndex(int64_t neighbour);
	/**
	 * GET POP POSITION
	 * input: a node
	 * output: index of the node to be popped
	 * out from the list
	 * Finds an index of a visited node to be
	 * to be popped out
	 */
	int getPopPosition(int64_t uNode);
	/**
	 * GET UNIVISITED NODES
	 * input: a node
	 * output: all unvisited neighbours
	 * Finds all unvisited neighbour nodes
	 * of another node
	 */
	vect_int getUnivisitedNodes(int64_t uNode);
};



#endif // PATHFINDINGALGORITHMS_H_INCLUDED
