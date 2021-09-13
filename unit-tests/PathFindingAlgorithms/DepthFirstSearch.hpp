#pragma once

#include <iostream>																		// for connected nodes and edges
#include <tuple>																		// used for node indices from a graph / grid
#include <stack>																		// dfs works according to a stack (LIFO)
#include <vector>																		// for storing neighbour nodes
#include <memory>																		// used for smart pointers
#include <algorithm>																	// used for find function

typedef std::vector<std::vector<bool>> vect2d_bool;										// alias for 2d vector of bools
typedef std::vector<int64_t> vect_int;													// alias for vector of ints
typedef std::pair<int64_t, int64_t> pair;												// alias for vector


class DepthFirstSearch
{
private:
	int rows = 4;																		// size of the
	int cols = 3;																		// grid / graph
	int64_t start;																		// start node
	int64_t end;																		// end node
	std::vector<std::vector<int64_t>> grid;												// the grid / graph
	std::stack<std::tuple<int, int>> s;													// dfs works according to a stack
	vect2d_bool visited;																// 2d vector for recording the visite and unvisited nodes
public:
	/**
	 * DEPTHFIRSTSEARCH class constructor + initialization list
	 * input: the start point and the end point for pathfinding
	 * Initializes the graph,
	 */
	DepthFirstSearch(int64_t s, int64_t e) :
		start(s),
		end(e)
	{
		// initializing the status of the nodes (visited / unvisited - true / false) - all are set to false
		for (int i = 0; i < rows; i++)
		{
			std::vector<bool> t;
			for (int j = 0; j < cols; j++)
			{
				t.push_back(false);
			}
			visited.push_back(t);
		}
		// initializing the edges and the weights according to the grid / 2d vector
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
	}
	/**
	 * FIND WEIGHT
	 * input: a 64-bit integer, a weight of an edge
	 * output: a tuple of 2 integers, representing the coordinate of the weight found
	 * according to the 2d vector / graph
	 * Finds the coordinated of weight of an edge and return its coordinates / indices
	 * as a tuple
	 */
	std::tuple<int, int> FindWeight(int64_t weight)
	{
		for (int32_t i = 0; i < grid.size(); i++)
		{
			for (int32_t j = 0; j < grid.at(i).size(); j++)
			{
				if (grid.at(i).at(j) == weight)
					return std::make_tuple(i, j);
			}
		}
		return std::make_tuple(-1, -1);
	}
	/**
	 * DFS
	 * input: none
	 * output: a vector of integers representing nodes of the shortest path
	 * Find the shortest path between two nodes
	 */
	vect_int DFS()
	{
		vect_int shortest_path;																	// store the shortest path here
		int h = grid.size();																	// bounds for the grid / graph
		int l = grid.at(0).size();

		std::tuple<int, int> idx = FindWeight(start);											// find the indices of the start node in the graph / grid
		s.push(idx);																			// push the start to the stack


		while (!s.empty())																		// while the s is not empty
		{
			std::tuple<int, int> u = s.top();													// get the top node 
			s.pop();																			// pop out the top node pushed to the stack
			int32_t row = std::get<0>(u);														// get the row index of u
			int32_t col = std::get<1>(u);														// get the column index of u

			if (row < 0 || col < 0 || row >= h || col >= l || visited.at(row).at(col))			// if the current node is not outside of the grid's / graph's bounds or if it's visited then  
				continue;																		// skip

			visited.at(row).at(col) = true;														// the current node becomes visited
			std::cout << grid.at(row).at(col) << " ";											// display the node to the console
			shortest_path.push_back(grid.at(row).at(col));										// add the node to the shortest path

			if (grid.at(row).at(col) == end)													// if destination reached 
				break;																			// stop

			// these directions from below works in all cases									
			s.push(std::make_tuple(row, col - 1)); // left										
			s.push(std::make_tuple(row + 1, col)); // down
			s.push(std::make_tuple(row, col + 1)); // right
			s.push(std::make_tuple(row - 1, col)); // up
		}
		return shortest_path;
	}
};
