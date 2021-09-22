#include "include/PathFindingAlgorithms.h"
#include "include/Interface.h"


BreadthFirstSearch::BreadthFirstSearch(std::vector<std::vector<Button>> g, int64_t s, int64_t e, sf::RenderWindow& win) :
	Dijkstra(g, s, e, win)
{
	// initialize all nodes as not visited
	visited = vect_bool(size, false);
}

int BreadthFirstSearch::Visualize(std::unique_ptr<Interface>& init)
{
	visited.at(start) = true;
	dist.at(start) = 0;
	Q.push(start);

	while (!Q.empty())
	{
		int64_t u = Q.front();
		Q.pop();
		int64_t lastVisited = 0;

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

		for (int i = 0; i < edges.at(u).size(); i++)
		{
			weightIdx = FindWeight(u);
			bool isWall = grid.at(std::get<0>(weightIdx)).at(std::get<1>(weightIdx)).GetWall();
			if (visited.at(edges.at(u).at(i)) == false && isWall == false)
			{
				visited.at(edges.at(u).at(i)) = true;
				dist.at(edges.at(u).at(i)) = dist.at(u) + 1;
				previous.at(edges.at(u).at(i)) = u;
				Q.push(edges.at(u).at(i));
				lastVisited = edges.at(u).at(i);

				// visualizing effect of finding the neighbours of a node / cell
				weightIdx = FindWeight(edges.at(u).at(i));
				if (grid.at(std::get<0>(weightIdx)).at(std::get<1>(weightIdx)).GetWall() == false)
					grid.at(std::get<0>(weightIdx)).at(std::get<1>(weightIdx)).SetShapeColor(sf::Color::Magenta);
				if (lastVisited == end)
					break;
			}
		}
		if (lastVisited == end)
			break;
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
	std::tuple<vect_int, int64_t> solution										    // tuple for the shortest path +
	(shortest_path, dist.at(end));												    // final cost soulution

	if (std::get<1>(solution) != LLONG_MAX)											// DISPLAY THE SOLUTION in terminal if there is a route destination
	{																				// for each node 
		std::cout << "([";
		for (uint32_t i = 0; i < std::get<0>(solution).size(); i++)
		{
			weightIdx = FindWeight(std::get<0>(solution).at(i));
			grid.at(std::get<0>(weightIdx)).at(std::get<1>(weightIdx)).SetShapeColor(sf::Color::Yellow);
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

			std::cout << std::get<0>(solution).at(i);							    // display it 
			if (i != std::get<0>(solution).size() - 1)							    // don't print , at the end
				std::cout << ", ";												    //
		}
		std::cout << "]";														    //
		std::cout << ", " << std::get<1>(solution);								    // print the total cost
		std::cout << ")" << std::endl;											    //
	}
	return PrintPath(init);
}