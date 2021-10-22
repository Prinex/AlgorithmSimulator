#pragma once

#include <iostream>
#include <iostream>
#include <map>																			// for connected nodes and edges
#include <tuple>			
#include <utility>																		// for representing an edge (std::pair)
#include <vector>																		// for storing neighbour nodes
#include <queue>
#include <climits>																		// for interpreting infinity (LLONG_MAX)
#include <memory>																		// used for smart pointers
#include <algorithm>																	// used for find function
#include <cmath>

typedef std::vector<int64_t> vect_int;													// alias for vector of ints
typedef std::pair<int64_t, int64_t> pair;												// alias for vector



class AStar
{
public:
	int rows = 23;
	int cols = 41;
	int64_t start;
	int64_t end;
	std::vector<std::vector<int64_t>> grid;
	std::map<int64_t, vect_int> edges;
	vect_int gScore;
	vect_int hScore;
	vect_int fScore;
	vect_int previous;
	vect_int Q;
	vect_int unpoppedQ;

public:
	/**
	 * ASTAR class constructor + initialization list
	 * input: the graph operated by dijkstra, the start and end nodes, and the instance of the window
	 * Initializes the edges of the graph, all costs of a node (f, g, h) are set to "infinity", and all nodes set to unvisited
	 */
	AStar(int64_t s, int64_t e) :
		start(s),
		end(e)
	{
		int size = rows * cols;															// size of nodes is rows by cols
		gScore = vect_int(size, LLONG_MAX);
		hScore = vect_int(size, LLONG_MAX);
		fScore = vect_int(size, LLONG_MAX);											// all nodes set to 'inf'
		previous = vect_int(size, LLONG_MAX);											// nothing visited
		// initializing the grid / graph cells with ints starting from 1 to 943
		int cellCount = 0;
		for (int i = 0; i < rows; i++)
		{
			std::vector<int64_t> t;
			for (int j = 0; j < cols; j++)
			{
				t.push_back(cellCount);
				cellCount++;
			}
			grid.push_back(t);
		}
		// initializing the edges according to the grid / 2d vector
		// the neighbours of a node include: left, right, up, bottom, left diagonal and right diagonal nodes
		// we have 8 directions in total in a square
		for (int64_t i = 0; i < grid.size(); i++)
		{
			for (int64_t j = 0; j < grid.at(i).size(); j++)
			{
				// combinations of columns
				if (i != grid.size() && j != grid.at(i).size() - 1)
					add_edge(grid.at(i).at(j), grid.at(i).at(j + 1));
				// combinations of rows
				if (i != grid.size() - 1 && j != grid.at(i).size())
					add_edge(grid.at(i).at(j), grid.at(i + 1).at(j));
				// combination of diagonals (left)
				if (((i - 1 >= 0 && j - 1 >= 0) && (i - 1 < grid.size() && j - 1 < grid.at(i).size())))
					add_edge(grid.at(i).at(j), grid.at(i - 1).at(j - 1));
				// combination of diagonals (right)
				if ((i - 1 >= 0 && i - 1 < grid.size()) && j + 1 < grid.at(i).size())
					add_edge(grid.at(i).at(j), grid.at(i - 1).at(j + 1));
			}
		}
	}
	void add_edge(int64_t from_node, int64_t to_node)
	{															                        // bidirectional
		edges[from_node].push_back(to_node);					                        // append the
		edges[to_node].push_back(from_node);					                        // connected nodes
	}
	/**
	 * VISUALIZE pure virtual function for BREADTH FIRST SEARCH
	 * input: the instance of the window
	 * output: a function printing the final form of the grid on the screen
	 * Finds the shortest path between 2 nodes specified
	 */
	std::tuple<vect_int, int64_t> AS()
	{
		for (auto key : edges)										                    // for each unvisited node
			Q.push_back(key.first);														// append it to the unvisited vector of nodes
		for (uint32_t i = 0; i < Q.size(); i++)											// for each unvisited node
		{
			if (Q.at(i) == start)														// if the current node is the start point
			{
				gScore.at(i) = 0;									                    // initialize the start point
				hScore.at(i) = 0;
				fScore.at(i) = 0;
			}
		}
		for (auto n : Q)																// make a vector of all 
			unpoppedQ.push_back(n);														// unvisited & visited nodes

		while (!Q.empty())
		{
			int c = findSmallestFNode();								                // find the smallest f cost node
			if (unpoppedQ.at(c) == end)													// destination reached
			{
				std::cout << "Destination reached" << std::endl;
				break;												                    // stop
			}
			int64_t current = unpoppedQ.at(c);											// the current node
			Q.erase(Q.begin() + getPopPosition(current));								// pop the visited node
			vect_int neighbours = getUnivisitedNodes(current);		                    // find all neighbours of the current visited node

			int64_t lastVisited = 0;
			for (auto neighbour : neighbours)						                    // for each neighbour found
			{
				int64_t tempG = GCost(current, neighbour);								// calculate the g cost
				if (tempG < gScore.at(getIndex(neighbour)))								// if G cost is less than current G cost
				{
					previous.at(getIndex(neighbour)) = current;							// record the previous visited node
					gScore.at(getIndex(neighbour)) = tempG;								// update the G cost of the node
					hScore.at(getIndex(neighbour)) = HCost(neighbour);					// update the H cost of the node 
					fScore.at(getIndex(neighbour)) = FCost(gScore.at(getIndex(neighbour)), hScore.at(getIndex(neighbour))); // update the F cost of the node
					if (std::find(Q.begin(), Q.end(), neighbour) == Q.end())			// if neighbour not in Q 
						Q.at(getIndex(neighbour)) = neighbour;							// append neighbour to Q
				}
				lastVisited = neighbour;												// record the last visited node

				if (lastVisited == end)													// destination reached
				{
					std::cout << "Destination reached" << std::endl;
					break;												                // stop
				}
			}
			if (lastVisited == end)														// destination reached
			{
				break;												                    // stop
			}
		}
		/// CONSTRUCT THE SOLUTION
		vect_int shortest_path;													        // build shortest path solution 
		shortest_path.insert(shortest_path.begin(), end);						        // insert the destination node
		int u = getIndex(end);													        // set u to destination
		while (previous.at(u) != LLONG_MAX)												// while the value in previous list is not null
		{
			shortest_path.insert(shortest_path.begin(), previous.at(u));		        // insert u at the beginning of the vector
			u = getIndex(previous.at(u));										        // u is now the value at previous[u]
		}
		std::tuple<vect_int, int64_t> solution										    // tuple for the shortest path +
		(shortest_path, fScore.at(end));												// final cost soulution	

		return solution;
	}
	/**
	* GCOST heuristic function
	* input: two integers representing the current node and neighbour node
	* output: distance from the starting node
	* It calculates the distance from the starting node
	* Note: Because I decided to use 8 directions this algorithm uses the diagonal distance
	* as heuristics (GCost)
	*/
	int64_t GCost(int64_t current, int64_t neighbour)
	{
		std::tuple<int, int> currentXY = FindWeight(current);
		int currentX = std::get<0>(currentXY);
		int currentY = std::get<1>(currentXY);

		std::tuple<int, int> neighbourXY = FindWeight(neighbour);
		int neighbourX = std::get<0>(neighbourXY);
		int neighbourY = std::get<1>(neighbourXY);

		int dx = std::abs(neighbourX - currentX);
		int dy = std::abs(neighbourY - currentY);

		int64_t G = 1 * (dx + dy) + (sqrt(2) - 2 * 1) * std::min(dx, dy);

		return G;
	}
	/**
	 * HCOST heuristic function
	 * input: a neighbour node
	 * output: the distance from the end node
	 * It calculates the distance from the end node
	 */
	int64_t HCost(int64_t point)
	{
		std::tuple<int, int> pointXY = FindWeight(point);
		int pointX = std::get<0>(pointXY);
		int pointY = std::get<1>(pointXY);

		std::tuple<int, int> endXY = FindWeight(end);
		int endX = std::get<0>(endXY);
		int endY = std::get<1>(endXY);

		int64_t H = (std::pow((double)(pointX - endX), 2) + std::pow((double)(pointY - endY), 2)) * 10;

		return H;
	}
	/**
	 * FCOST heuristic function
	 * input: two integers representing the current node a neighbour node
	 * output: the sum of G and H costs
	 * It calculates the total cost of G and H costs
	 */
	int64_t FCost(int64_t GCost, int64_t HCost)
	{
		return GCost + HCost;
	}
	// Note: Methods from below are also used in dijkstra
	/**
	 * FIND SMALLEST NODE
	 * input: none
	 * output: the integer index of the smallest node
	 * Find the smallest with the lowest
	 * cost from the current node to another
	 */
	int findSmallestFNode()
	{
		int64_t smallest = fScore.at(getIndex(Q.at(0)));								// initialize the smallest with the cost
																						// from the first node
		int result = getIndex(Q.at(0));													// initialize the result with the idx of 
																						// the first node
		for (uint32_t i = 0; i < fScore.size(); i++)						            // go trough all nodes's costs
		{
			if (fScore.at(i) < smallest)									            // if the cost is smaller than the current cost
			{
				int64_t node = unpoppedQ.at(i);											// current node
				if (std::find(Q.begin(), Q.end(), node) != Q.end())						// if the current node is in Q
				{
					smallest = fScore.at(i);									        // make the smallest the current cost
					result = getIndex(node);								            // make the result the idx of the current node
				}
			}
		}
		return result;
	}
	/**
	 * GET INDEX
	 * input: a node index represented as a char
	 * output: the numerical index of the node
	 * Finds the numerical idx of a node's neighbour
	 */
	int getIndex(int64_t neighbour)
	{
		for (uint32_t i = 0; i < unpoppedQ.size(); i++)								// go trough all nodes
		{
			if (neighbour == unpoppedQ.at(i))										// if neighbour found
				return i;																// return its index
		}
		std::cout << "Not found." << std::endl;											// display message
		return -1;																		// if not found return -1
	}
	/**
	 * GET POP POSITION
	 * input: a node
	 * output: index of the node to be popped
	 * out from the list
	 * Finds an index of a visited node to be
	 * to be popped out
	 */
	int getPopPosition(int64_t uNode)
	{
		int result = 0;																	// the index to be returned
		for (uint32_t i = 0; i < Q.size(); i++)									// go trough all unvisited nodes
		{
			if (Q.at(i) == uNode)												// if current node is the uNode
				result = i;																// update the result with the curr. idx.
		}
		return result;																	// return the index found
	}
	/**
	 * GET UNIVISITED NODES
	 * input: a node
	 * output: all unvisited neighbours
	 * Finds all unvisited neighbour nodes
	 * of another node
	 */
	vect_int getUnivisitedNodes(int64_t uNode)
	{
		vect_int resultList;															// unvisited neighbour nodes found
		vect_int allNeighbours = edges[uNode];											// all nodes connected to uNode
		for (auto neighbour : allNeighbours)											// go through all neighbour node
		{
			if (std::find(Q.begin(),												// if neighbour is unvisited
				Q.end(), neighbour) != Q.end())          					// append it to the vector of results
				resultList.push_back(neighbour);										//		
		}
		return resultList;																// return the neighbours found
	}
	/**
	 * FIND WEIGHT
	 * input: a 64-bit integer, a weight of an edge
	 * output: a tuple of 2 integers, representing the coordinate of the weight found
	 * according to the 2d vector / graph
	 * Finds the coordinates of weight of an edge and return its coordinates / indices
	 * as a tuple
	 */
	std::tuple<int, int> FindWeight(int64_t weight)
	{
		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid.at(i).size(); j++)
			{
				if (grid.at(i).at(j) == weight)
					return std::make_tuple(i, j);
			}
		}
		return std::make_tuple(-1, -1);
	}
};

