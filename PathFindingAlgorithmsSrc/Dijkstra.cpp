#include "include/PathFindingAlgorithms.h"
#include "include/Interface.h"

Dijkstra::Dijkstra(std::vector<std::vector<Button>> g, int64_t s, int64_t e, sf::RenderWindow& win) :
	PathFindingAlgorithms(g, s, e, win)
{
	int size = rows * columns;														// size of nodes is rows by cols
	dist = vect_int(size, LLONG_MAX);												// all nodes set to 'inf'
	previous = vect_int(size, LLONG_MAX);											// nothing visited

	// initializing the edges and the weights according to the grid / 2d vector
	for (uint64_t i = 0; i < grid.size(); i++)
	{
		for (uint64_t j = 0; j < grid.at(i).size(); j++)
		{ 
			// combinations of columns
			if (i != grid.size() && j != grid.at(i).size() - 1)
				add_edge(grid.at(i).at(j).GetWeight(), grid.at(i).at(j + 1).GetWeight(), LLONG_MAX);
			// combinations of rows
			if (i != grid.size() - 1 && j != grid.at(i).size())
				add_edge(grid.at(i).at(j).GetWeight(), grid.at(i + 1).at(j).GetWeight(), LLONG_MAX);
		}
	}
}

int Dijkstra::Visualize(std::unique_ptr<Interface>& init)
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
		{
			std::cout << "There is no route to destination" << std::endl;
			break;												                    // stop
		}
		if (unpoppedQ.at(u) == end)													// destination reached
		{
			std::cout << "Destination reached" << std::endl;
			break;												                    // stop
		}
		
		int64_t uNode = unpoppedQ.at(u);							                // the current node
		Q.erase(Q.begin() + getPopPosition(uNode));				                    // pop the visited node
		vect_int neighbours = getUnivisitedNodes(uNode);		                    // find all neighbours of the current visited node

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

		for (uint32_t v = 0; v < neighbours.size(); v++)		                    // for each neighbour found
		{
			// this might be the problem with the cells
			// counting cells might need changed (from left to right to right to left)
			int64_t alt = dist.at(u) + 1;											// add distance of u, to cost (the cost is 1 unit from a cell to another)
																					// from u to neighbour; assign to alt

			if (alt < dist.at(getIndex(neighbours.at(v))))					        // if alt is less than neighbour distance 
			{
				dist.at(getIndex(neighbours[v])) = alt;						        // assign alt to neighbour distance
				previous.at(getIndex(neighbours[v])) = uNode;					    // assign u to previous[v]	
			}
			// visualizing effect of finding the neighbours of a node / cell
			weightIdx = FindWeight(neighbours.at(v));
			grid.at(std::get<0>(weightIdx)).at(std::get<1>(weightIdx)).SetShapeColor(sf::Color::Magenta);
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

void Dijkstra::add_edge(int64_t from_node, int64_t to_node, int64_t weight)
{															                        // bidirectional
	edges[from_node].push_back(to_node);					                        // append the
	edges[to_node].push_back(from_node);					                        // connected nodes 
	weights[pair(from_node, to_node)] = weight;				                        // append the weigths for 
	weights[pair(to_node, from_node)] = weight;				                        // the edge
}

int Dijkstra::findSmallestNode()
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

int Dijkstra::getIndex(int64_t neighbour)
{
	for (uint32_t i = 0; i < unpoppedQ.size(); i++)									// go trough all nodes
	{
		if (neighbour == unpoppedQ.at(i))											// if neighbour found
			return i;																// return its index
	}
	std::cout << "Not found." << std::endl;											// display message
	return -1;																		// if not found return -1
}

int Dijkstra::getPopPosition(int64_t uNode)
{
	int result = 0;																	// the index to be returned
	for (uint32_t i = 0; i < Q.size(); i++)											// go trough all unvisited nodes
	{
		if (Q.at(i) == uNode)														// if current node is the uNode
			result = i;																// update the result with the curr. idx.
	}
	return result;																	// return the index found
}

vect_int Dijkstra::getUnivisitedNodes(int64_t uNode)
{
	vect_int resultList;															// unvisited neighbour nodes found
	vect_int allNeighbours = edges[uNode];											// all nodes connected to uNode
	for (auto neighbour : allNeighbours)											// go through all neighbour node
	{
		std::tuple<uint32_t, uint32_t> weightIdx = FindWeight(neighbour);			// omit walls
		bool isWall = grid.at(std::get<0>(weightIdx)).at(std::get<1>(weightIdx)).GetWall(); // 
		if (std::find(Q.begin(),													// if neighbour is unvisited
			Q.end(), neighbour) != Q.end() && isWall == false)						// append it to the vector of results
			resultList.push_back(neighbour);										//		
	}
	return resultList;																// return the neighbours found
}