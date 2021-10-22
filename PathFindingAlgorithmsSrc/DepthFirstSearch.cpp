#include "include/PathFindingAlgorithms.h"
#include "include/Interface.h"

DepthFirstSearch::DepthFirstSearch(std::vector<std::vector<Button>> g, int64_t s, int64_t e, sf::RenderWindow& win) :
	PathFindingAlgorithms(g, s, e, win)
{
	// initializing the status of the nodes (visited / unvisited - true / false) - all are set to false
	for (int i = 0; i < rows; i++)
	{
		std::vector<bool> t;
		for (int j = 0; j < columns; j++)
		{
			t.push_back(false);
		}
		visited.push_back(t);
	}
}

int DepthFirstSearch::Visualize(std::unique_ptr<Interface>& init)
{
	int h = grid.size();											// store the shortest path here
	int l = grid.at(0).size();										// bounds for the grid / graph
	
	std::vector<std::tuple<int, int>> shortest_path;				// vector for storing the shortest path

	std::tuple<int, int> idx = FindWeight(start);					// find the indices of the start node in the graph / grid
	s.push(idx);													// push the start to the stack

	while (!s.empty())												// while the s is not empty
	{
		std::tuple<int, int> u = s.top();							// get the top node of the stack
		s.pop();													// pop out the top node pushed to the stack
		int32_t row = std::get<0>(u);								// get the row index of u
		int32_t col = std::get<1>(u);								// get the column index of u

		if (row < 0 || col < 0 || row >= h || col >= l || visited.at(row).at(col))			// if the current node is not outside of the grid's / graph's bounds or if it's visited then
			continue;																		// skip it

		visited.at(row).at(col) = true;							    // the current node becomes visited
		std::cout << grid.at(row).at(col).GetWeight() << " ";	    // display the node to the console
		// color effect											    // add the node to the shortest path
		if (grid.at(row).at(col).GetWall() != true)
			grid.at(row).at(col).SetShapeColor(sf::Color::Magenta);
		// printing the grid
		window.clear(sf::Color::White);
		for (std::vector<std::vector<Button>>::iterator iti = grid.begin(); iti < grid.end(); iti = std::next(iti))
		{
			for (std::vector<Button>::iterator itj = iti->begin(); itj < iti->end(); itj = std::next(itj))
			{
				(*itj).Draw(window);
			}
		}
		window.display();
		
		// construct the "shortest path" at the same time
		if (grid.at(row).at(col).GetWall() != true)					// omit the walls
			shortest_path.push_back(std::make_tuple(row, col));		// append the current node to the shortest path

		if (grid.at(row).at(col).GetWeight() == end)				// if destination reached
			break;													// stop

		// these directions from below works in all cases 
		// follow these directions
		if (grid.at(row).at(col).GetWall() != true)
		{
			s.push(std::make_tuple(row, col - 1)); // left
			s.push(std::make_tuple(row + 1, col)); // down
			s.push(std::make_tuple(row, col + 1)); // right
			s.push(std::make_tuple(row - 1, col)); // up
		}
	}
	// color effect for the shortest path
	for (auto s : shortest_path)
	{
		grid.at(std::get<0>(s)).at(std::get<1>(s)).SetShapeColor(sf::Color::Yellow);
		window.clear(sf::Color::White);
		for (std::vector<std::vector<Button>>::iterator iti = grid.begin(); iti < grid.end(); iti = std::next(iti))
		{
			for (std::vector<Button>::iterator itj = iti->begin(); itj < iti->end(); itj = std::next(itj))
			{
				(*itj).Draw(window);
			}
		}
		window.display();
	}
	return PrintPath(init);
}