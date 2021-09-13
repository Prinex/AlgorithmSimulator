#pragma once

#include <iostream>																		// for connected nodes and edges
#include <tuple>																		// used for node indices from a graph / grid
#include <queue>																		// dfs works according to a stack (LIFO)
#include <vector>																		// for storing neighbour nodes
#include <memory>																		// used for smart pointers
#include <algorithm>																	// used for find function
#include <map>

typedef std::vector<bool> vect_bool;													// alias for 2d vector of bools
typedef std::vector<int64_t> vect_int;													// alias for vector of ints
typedef std::pair<int64_t, int64_t> pair;												// alias for vector


class BreadthFirstSearch
{
private:
	int rows = 23;
	int cols = 41;
	int64_t start;
	int64_t end;
	std::vector<std::vector<int64_t>> grid;
	std::queue<int64_t> q;
	std::map<int64_t, vect_int> edges;
	vect_int dist;
	vect_int previous;
	vect_bool visited;
public:
	BreadthFirstSearch(int64_t s, int64_t e) :
		start(s),
		end(e)
	{
		int size = rows * cols;															// size of nodes is rows by cols
		dist = vect_int(size, LLONG_MAX);												// all nodes set to 'inf'
		previous = vect_int(size, LLONG_MAX);											// nothing visited												
		visited = vect_bool(size, false);
		// initializing the edges and the weights according to the grid / 2d vector
		int cellCount = 1;
		for (int i = 0; i < rows; i++)
		{
			std::vector<int64_t> t;
			for (int j = 0; j < cols; j++)
			{
				std::cout << cellCount << " ";
				t.push_back(cellCount);
				cellCount++;
			}
			std::cout << std::endl;
			grid.push_back(t);
		}
		// initializing the edges and the weights according to the grid / 2d vector
		for (int64_t i = 0; i < grid.size(); i++)
		{
			for (int64_t j = 0; j < grid.at(i).size(); j++)
			{
				// combinations of columns
				if (i != grid.size() && j != grid.at(i).size() - 1)
					add_edge(grid.at(i).at(j), grid.at(i).at(j + 1), LLONG_MAX);
				// combinations of rows
				if (i != grid.size() - 1 && j != grid.at(i).size())
					add_edge(grid.at(i).at(j), grid.at(i + 1).at(j), LLONG_MAX);
			}
		}
	}

	void add_edge(int64_t from_node, int64_t to_node, int64_t weight)
	{															                        // bidirectional
		edges[from_node].push_back(to_node);					                        // append the
		edges[to_node].push_back(from_node);					                        // connected nodes 
	}

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

	vect_int BFS()
	{
		visited.at(start) = true;														// set the start as visited
		dist.at(start) = 0;																// set the start node distance to be 0
		q.push(start);																	// push the start node to the queue

		while (!q.empty())																// while the queue is not empty
		{	
			int64_t u = q.front();														// get the front node of the queue
			q.pop();																	// pop out the top node pushed to the stack
			int64_t lastVisited = 0;													// a variable for helping to stop the inner loop 
			for (int i = 0; i < edges.at(u).size(); i++)								// for each neighbour of u
			{
				if (visited.at(edges.at(u).at(i)) == false)								// if neighbour of u is not visited
				{
					visited.at(edges.at(u).at(i)) = true;								// mark it as visited
					dist.at(edges.at(u).at(i)) = dist.at(u) + 1;						// calculate the distance from u to neighbour (+1 unit)
					previous.at(edges.at(u).at(i)) = u;									// save the current visited node
					q.push(edges.at(u).at(i));											// push the current neighbour from u to the queue
					lastVisited = edges.at(u).at(i);									// remember the last visited node
					if (lastVisited == end)												// if end node reached
						break;															// stop it
				}
			}
			if (lastVisited == end)														// if the last visited node is the end node
				break;																	// stop it
		}
		// CONSTRUCT THE SOLUTION
		vect_int shortest_path;													        // build shortest path solution 
		int64_t u = end;																// set u to destination
		shortest_path.insert(shortest_path.begin(), end);						        // insert the destination node
		while (previous.at(u) != LLONG_MAX)											    // while the value in previous list is not null
		{
			shortest_path.insert(shortest_path.begin(), previous.at(u));		        // insert u at the beginning of the vector
			u = previous.at(u);															// u is now the value at previous[u]
		}
		return shortest_path;
	}
};