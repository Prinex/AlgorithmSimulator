#pragma once

#include <iostream>
#include <map>																			// for connected nodes and edges
#include <tuple>			
#include <utility>																		// for representing an edge (std::pair)
#include <vector>																		// for storing neighbour nodes
#include <climits>																		// for interpreting infinity (LLONG_MAX)
#include <memory>																		// used for smart pointers
#include <algorithm>																	// used for find function

typedef std::vector<int64_t> vect_int;													// alias for vector of ints
typedef std::pair<int64_t, int64_t> pair;												// alias for vector


class Dijkstra
{
private:
	int rows = 23;
	int cols = 41;
	int64_t start;
	int64_t end;
	std::vector<std::vector<int64_t>> grid;
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
	Dijkstra(int64_t s, int64_t e) :
		start(s),
		end(e)
	{
		int size = rows * cols;															// size of nodes is rows by cols
		dist = vect_int(size, LLONG_MAX);												// all nodes set to 'inf'
		previous = vect_int(size, LLONG_MAX);											// nothing visited
		// initializing the grid / graph cells with ints starting from 1 to 943
		int cellCount = 1;
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
		// initializing the edges and the weights according to the grid / 2d vector
		for (int64_t i = 0; i < grid.size(); i++)
		{
			for (int64_t j = 0; j < grid.at(i).size(); j++)
			{
				// combinations of columns
				if (i != grid.size() && j != grid.at(i).size() - 1)
					add_edge(grid.at(i).at(j), grid.at(i).at(j + 1), grid.at(i).at(j));
				// combinations of rows
				if (i != grid.size() - 1 && j != grid.at(i).size())
					add_edge(grid.at(i).at(j), grid.at(i + 1).at(j), grid.at(i).at(j));
			}
		}
	}
	/**
	 * ADD EDGE
	 * input: 2 nodes and a weight
	 * output: none
	 * Inserts an edge and its weigth
	 * to the graph
	 */
	void add_edge(int64_t from_node, int64_t to_node, int64_t weight)
	{															                        // bidirectional
		edges[from_node].push_back(to_node);					                        // append the
		edges[to_node].push_back(from_node);					                        // connected nodes 
		weights[pair(from_node, to_node)] = weight;				                        // append the weigths for 
		weights[pair(to_node, from_node)] = weight;				                        // the edge
	}
	/**
	 * FIND SMALLEST NODE
	 * input: none
	 * output: the integer index of the smallest node
	 * Find the smallest with the lowest
	 * cost from the current node to another
	 */
	int findSmallestNode()
	{
		int64_t smallest = dist.at(getIndex(Q.at(0)));						            // initialize the smallest with the cost
																						// from the first node
		int result = getIndex(Q.at(0));										            // initialize the result with the idx of 
																						// the first node
		for (uint32_t i = 0; i < dist.size(); i++)							            // go trough all nodes's costs
		{
			if (dist.at(i) < smallest)										            // if the cost is smaller than the current cost
			{
				int64_t node = unpoppedQ.at(i);								            // current node
				if (std::find(Q.begin(), Q.end(), node) != Q.end())			            // if the current node is in Q
				{
					smallest = dist.at(i);									            // make the smallest the current cost
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
		for (uint32_t i = 0; i < unpoppedQ.size(); i++)									// go trough all nodes
		{
			if (neighbour == unpoppedQ.at(i))											// if neighbour found
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
		for (uint32_t i = 0; i < Q.size(); i++)											// go trough all unvisited nodes
		{
			if (Q.at(i) == uNode)														// if current node is the uNode
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
			if (std::find(Q.begin(),													// if neighbour is unvisited
				Q.end(), neighbour) != Q.end())											// append it to the vector of results
				resultList.push_back(neighbour);										//		
		}
		return resultList;																// return the neighbours found
	}
	/**
	 * DIJKSTRA
	 * input: start node, end node
	 * output: shortest path from start to end
	 * Find the shortest path between 2 nodes specified
	 */
	std::tuple<vect_int, int64_t> dijkstra()
	{
		for (auto key : edges)										                    // for each unvisited node
			Q.push_back(key.first);									                    // append it to the unvisited vector of nodes
		for (uint32_t i = 0; i < Q.size(); i++)						                    // for each unvisited node
		{
			if (Q.at(i) == start)									                    // if the current node is the start point
				dist.at(i) = 0;										                    // initialize the start point
		}
		for (auto n : Q)											                    // make a vector of all 
			unpoppedQ.push_back(n);									                    // unvisited & visited nodes
																						// GO TROUGH ALL VERTICES
		while (!Q.empty())											                    // while there are still unvisited nodes
		{
			int u = findSmallestNode();								                    // find the smallest node
			if (dist.at(u) == LLONG_MAX)							                    // if there is no route to destiantion
				break;												                    // stop
			if (unpoppedQ.at(u) == end)								                    // destination reached
				break;												                    // stop

			int64_t uNode = unpoppedQ.at(u);							                // the current node
			Q.erase(Q.begin() + getPopPosition(uNode));				                    // pop the visited node
			vect_int neighbours = getUnivisitedNodes(uNode);		                    // find all neighbours of the current visited node
			for (uint32_t v = 0; v < neighbours.size(); v++)		                    // for each neighbour found
			{
				int64_t alt = dist.at(u) + weights[pair(uNode, neighbours.at(v))];      // add distance of u, to cost 
																						// from u to neighbour; assign to alt

				if (alt < dist.at(getIndex(neighbours.at(v))))					        // if alt is less than neighbour distance 
				{
					dist.at(getIndex(neighbours[v])) = alt;						        // assign alt to neighbour distance
					previous[getIndex(neighbours[v])] = uNode;					        // assign u to previous[v]	
				}
			}
		}
		// CONSTRUCT THE SOLUTION
		vect_int shortest_path;													        // build shortest path solution 
		shortest_path.insert(shortest_path.begin(), end);						        // insert the destination node
		int u = getIndex(end);													        // set u to destination
		while (previous.at(u) != LLONG_MAX)											    // while the value in previous list is not null
		{
			shortest_path.insert(shortest_path.begin(), previous.at(u));		        // insert u at the beginning of the vector
			u = getIndex(previous.at(u));										        // u is now the value at previous[u]
		}
		std::tuple<vect_int, int64_t> solution										    // tuple for the shortest path +
		(shortest_path, dist.at(getIndex(end)));								        // final cost soulution	
		return solution;
	}
};

