#include "include/PathFindingAlgorithms.h"
#include "include/Interface.h"

AStar::AStar(std::vector<std::vector<Button>> g, int64_t s, int64_t e, sf::RenderWindow& win) :
	Dijkstra(g, s, e, win)
{
	gScore = vect_int(size, LLONG_MAX);
	hScore = vect_int(size, LLONG_MAX);
	fScore = vect_int(size, LLONG_MAX);

	// initializing the edges according to the grid / 2d vector
	// the neighbours of a node include: left, right, up, bottom, left diagonal and right diagonal nodes
	// we have 8 directions in total in a square
	for (int64_t i = 0; i < grid.size(); i++)
	{
		for (int64_t j = 0; j < grid.at(i).size(); j++)
		{
			// combination of diagonals (left)
			if (((i - 1 >= 0 && j - 1 >= 0) && (i - 1 < grid.size() && j - 1 < grid.at(i).size())))
				add_edge(grid.at(i).at(j).GetWeight(), grid.at(i - 1).at(j - 1).GetWeight());
			// combination of diagonals (right)
			if ((i - 1 >= 0 && i - 1 < grid.size()) && j + 1 < grid.at(i).size())
				add_edge(grid.at(i).at(j).GetWeight(), grid.at(i - 1).at(j + 1).GetWeight());
		}
	}
}

int AStar::Visualize(std::unique_ptr<Interface>& init)
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

		for (auto neighbour : neighbours)						                    // for each neighbour found
		{
			int64_t tempG = GCost(current, neighbour);								// calculate the g cost
			if (tempG < gScore.at(neighbour))										// if G cost is less than current G cost
			{
				previous.at(neighbour) = current;									// record the previous visited node
				gScore.at(neighbour) = tempG;										// update the G cost of the node
				hScore.at(neighbour) = HCost(neighbour);							// update the H cost of the node 
				fScore.at(neighbour) = FCost(gScore.at(neighbour), hScore.at(neighbour)); // update the F cost of the node
				if (std::find(Q.begin(), Q.end(), neighbour) == Q.end())			// if neighbour not in Q 
					Q.at(neighbour) = neighbour;									// append neighbour to Q
			}
			lastVisited = neighbour;												// record the last visited node
			// visualizing effect of finding the neighbours of a node / cell
			weightIdx = FindWeight(neighbour);
			grid.at(std::get<0>(weightIdx)).at(std::get<1>(weightIdx)).SetShapeColor(sf::Color::Magenta);

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
	// CONSTRUCT THE SOLUTION
	vect_int shortest_path;													        // build shortest path solution 
	shortest_path.insert(shortest_path.begin(), end);						        // insert the destination node
	int u = end;																	 // set u to destination
	while (previous.at(u) != LLONG_MAX)											    // while the value in previous list is not null
	{
		shortest_path.insert(shortest_path.begin(), previous.at(u));		        // insert u at the beginning of the vector
		u = previous.at(u);															// u is now the value at previous[u]
	}
	std::tuple<vect_int, int64_t> solution										    // tuple for the shortest path +
	(shortest_path, fScore.at(end));												// final cost soulution

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

int64_t AStar::GCost(int64_t current, int64_t neighbour)
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

int64_t AStar::HCost(int64_t point)
{
	std::tuple<int, int> pointXY = FindWeight(point);
	int pointX = std::get<0>(pointXY);
	int pointY = std::get<1>(pointXY);

	std::tuple<int, int> endXY = FindWeight(end);
	int endX = std::get<0>(endXY);
	int endY = std::get<1>(endXY);

	int64_t H = (std::pow((double)(endX - pointX), 2) + std::pow((double)(endY - pointY), 2)) * 10;

	return H;
}

int64_t AStar::FCost(int64_t GCost, int64_t HCost)
{
	return GCost + HCost;
}

int AStar::findSmallestFNode()
{
	int64_t smallest = fScore.at(Q.at(0));											// initialize the smallest with the cost
																					// from the first node
	int result = Q.at(0);															// initialize the result with the idx of 
																					// the first node
	for (uint32_t i = 0; i < fScore.size(); i++)						            // go trough all nodes's costs
	{
		if (fScore.at(i) < smallest)									            // if the cost is smaller than the current cost
		{
			int64_t node = unpoppedQ.at(i);											// current node
			if (std::find(Q.begin(), Q.end(), node) != Q.end())						// if the current node is in Q
			{
				smallest = fScore.at(i);									        // make the smallest the current cost
				result = node;														// make the result the idx of the current node
			}
		}
	}
	return result;
}