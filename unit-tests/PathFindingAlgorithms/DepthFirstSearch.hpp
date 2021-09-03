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
	int rows = 4;
	int cols = 3;
	int64_t start;
	int64_t end;
	std::vector<std::vector<int64_t>> grid;
	std::stack<std::tuple<int, int>> s;
	vect2d_bool visited;
public:
	DepthFirstSearch(int64_t s, int64_t e) :
		start(s),
		end(e)
	{
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

	vect_int DFS()
	{
		vect_int shortest_path;
		int h = grid.size();
		int l = grid.at(0).size();

		if (h == 0)
			return shortest_path;

		std::tuple<int, int> idx = FindWeight(start);
		s.push(idx);

		while (!s.empty())
		{
			std::tuple<int, int> u = s.top();
			s.pop();
			int32_t row = std::get<0>(u);
			int32_t col = std::get<1>(u);

			if (row < 0 || col < 0 || row >= h || col >= l || visited.at(row).at(col))
				continue;

			visited.at(row).at(col) = true;
			std::cout << grid.at(row).at(col) << " ";
			shortest_path.push_back(grid.at(row).at(col));

			if (grid.at(row).at(col) == end)
				break;

			// these directions from below works in all cases 
			s.push(std::make_tuple(row, col - 1)); // left
			s.push(std::make_tuple(row + 1, col)); // down
			s.push(std::make_tuple(row, col + 1)); // right
			s.push(std::make_tuple(row - 1, col)); // up
		}
		return shortest_path;
	}
};
