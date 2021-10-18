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
	void add_edge(int64_t from_node, int64_t to_node);
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
 * Notes about BFS:
 * BFS is really similar to dijkstra in finding the shortest path
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
	 * BREADTH FIRST SEARCH class constructor 
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

/**
 * Notes for AStar algorithm:
 * AStar is like an extension to Dijkstra
 * It uses heuristics to guide its search, i.e., calculating cost for a node / cell (G, F and H costs), 
 * achieving a better performance than Dijkstra
 */
class AStar : public Dijkstra
{
private:
	vect_int gScore;
	vect_int hScore;
	vect_int fScore;
public:
	/**
	 * ASTAR class constructor + initialization list
	 * input: the graph operated by dijkstra, the start and end nodes, and the instance of the window
	 * Initializes the edges of the graph, all costs of a node (f, g, h) are set to "infinity", and all nodes set to unvisited
	 */
	AStar(std::vector<std::vector<Button>> g, int64_t s, int64_t e, sf::RenderWindow& win);
	/**
	 * VISUALIZE pure virtual function for BREADTH FIRST SEARCH
	 * input: the instance of the window
	 * output: a function printing the final form of the grid on the screen
	 * Finds the shortest path between 2 nodes specified
	 */
	int Visualize(std::unique_ptr<Interface>& init);
	/**
	 * GCOST heuristic function 
	 * input: two integers representing the current node and neighbour node
	 * output: distance from the starting node
	 * It calculates the distance from the starting node
	 */
	int64_t GCost(int64_t current, int64_t neighbour);
	/**
	 * HCOST heuristic function
	 * input: a neighbour node
	 * output: the distance from the end node
	 * It calculates the distance from the end node
	 */
	int64_t HCost(int64_t point);
	/**
	 * FCOST heuristic function
	 * input: two integers representing the current node a neighbour node
	 * output: the sum of G and H costs
	 * It calculates the total cost of G and H costs
	 */
	int64_t FCost(int64_t GCost, int64_t HCost);
	/** 
	 * findSmallestFNode is adapted from Dijkstra
	 * It look for smallest F cost
	*/
	int findSmallestFNode();
};

#endif // PATHFINDINGALGORITHMS_H_INCLUDED
