#ifndef PATHFINDINGALGORITHMS_H_INCLUDED
#define PATHFINDINGALGORITHMS_H_INCLUDED

#include "Algorithms.h"




class Dijkstra : public PathFindingAlgorithms
{
private:
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
	int Visualize(std::unique_ptr<Interface>& init);
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
	 * input: a node index represented as an integer
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

// definitions of the below classes' methods are same as dijkstra's, e.g., 
// the constructor and the pure virtual method
class DepthFirstSearch : public PathFindingAlgorithms
{
private:
	std::stack<std::tuple<int, int>> s;
	vect2d_bool visited;
public:
	DepthFirstSearch(std::vector<std::vector<Button>> g, int64_t s, int64_t e, sf::RenderWindow& win);
	
	int Visualize(std::unique_ptr<Interface>& init);
};

#endif // PATHFINDINGALGORITHMS_H_INCLUDED
