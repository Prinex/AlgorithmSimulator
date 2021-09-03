#include "include/PathFindingAlgorithms.h"
#include "include/Interface.h"

DepthFirstSearch::DepthFirstSearch(std::vector<std::vector<Button>> g, int64_t s, int64_t e, sf::RenderWindow& win) :
	PathFindingAlgorithms(g, s, e, win)
{
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
	int h = grid.size();
	int l = grid.at(0).size();
	
	std::vector<std::tuple<int, int>> shortest_path;

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
		std::cout << grid.at(row).at(col).GetWeight() << " ";
		// color effect
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
		if (grid.at(row).at(col).GetWall() != true)
			shortest_path.push_back(std::make_tuple(row, col));

		if (grid.at(row).at(col).GetWeight() == end)
			break;

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