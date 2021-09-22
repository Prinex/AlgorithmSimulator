#ifndef PATHFINDINGALGORITHMS_H_INCLUDED
#define PATHFINDINGALGORITHMS_H_INCLUDED

#include "Algorithms.h"


class Dijkstra : public PathFindingAlgorithms
{
protected:
	vect_int dist;								// records distances between nodes
	vect_int previous;							// records previous visited nodes
	vect_int Q;									// records the unvisited nodes
	vect_int unpoppedQ;							// records all nodes
	int64_t lastVisited = 0;					// integer for recording the last visited node
public:
	/**
	 * DIJKSTRA class constructor + initialization list
	 * input: the graph operated by dijkstra, the start and end nodes, and the instance of the window
	 * Initializes the edges of the graph, all distances between nodes set to "infinity", and all nodes set to unvisited
	 */
	Dijkstra(std::vector<std::vector<Button>> g, int64_t s, int64_t e, sf::RenderWindow& win);
	/**
	 * VISUALIZE pure virtual function for DIJKSTRA
	 * input: the instance of the window
	 * output: a function printing the final form of the grid on the screen
	 * Finds the shortest path between 2 nodes specified
	 */
	int Visualize(std::unique_ptr<Interface>& init);
	/**
	 * ADD EDGE
	 * input: and the instance of the window
	 * output: none
	 * Inserts an edge and its weight to corresponing data structures
	 * to the graph
	 */
	void add_edge(int64_t from_node, int64_t to_node, int64_t weight);
	/**
	 * FIND SMALLEST NODE
	 * input: a source node, a destination node and a weight 
	 * output: an integer, i.e., index of the smallest node
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

class DepthFirstSearch : public PathFindingAlgorithms
{
private:
	std::stack<std::tuple<int, int>> s;				   // stack for nodes   
	vect2d_bool visited;							   // records the status of a node (visited / unvisited - true / false)
public:
	/**
	 * DEPTH FIRST SEARCH class constructor + initialization list
	 * input: the graph operated by dijkstra, the start and end nodes, and the instance of the window
	 * Initializes the edges of the graph, all distances between nodes set to "infinity", and all nodes set to unvisited
	 */
	DepthFirstSearch(std::vector<std::vector<Button>> g, int64_t s, int64_t e, sf::RenderWindow& win);
	/**
	 * VISUALIZE pure virtual function for BREADTH FIRST SEARCH
	 * input: the instance of the window
	 * output: a function printing the final form of the grid on the screen
	 * Finds the shortest path between 2 nodes specified
	 */
	int Visualize(std::unique_ptr<Interface>& init);
};

/**
 * note: bfs is really similar to dijkstra in finding the shortest path
 * in fact, bfs uses same approach as dijkstra, i.e., keeping count of 
 * previous visited nodes and distances from one node to another
 */ 
class BreadthFirstSearch : public Dijkstra
{
private:
	std::queue<int64_t> Q;								// records the unvisited nodes
	vect_bool visited;									// records the status of a node (visited / unvisited - true / false)
public:
	/**
	 * BREADTH FIRST SEARCH class constructor + initialization list
	 * input: the graph operated by dijkstra, the start and end nodes, and the instance of the window
	 * Sets all nodes to unvisited
	 */
	BreadthFirstSearch(std::vector<std::vector<Button>> g, int64_t s, int64_t e, sf::RenderWindow& win);
	/**
	 * VISUALIZE pure virtual function for BREADTH FIRST SEARCH
	 * input: the instance of the window
	 * output: a function printing the final form of the grid on the screen
	 * Finds the shortest path between 2 nodes specified
	 */
	int Visualize(std::unique_ptr<Interface>& init);
};

#endif // PATHFINDINGALGORITHMS_H_INCLUDED
