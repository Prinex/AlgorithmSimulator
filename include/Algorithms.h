#ifndef ALGORITHMS_H_INCLUDED
#define ALGORITHMS_H_INCLUDED


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <map>																			// for connected nodes and edges
#include <tuple>																		// used for graph's indices
#include <stack>																		// used for depth first search algorithm
#include <queue>																		// used for breadth first search algorithm
#include <utility>																		// for representing an edge (std::pair)
#include <climits>																		// for interpreting infinity (LLONG_MAX)

typedef std::vector<std::vector<bool>> vect2d_bool;										// alias for 2d vector of bools
typedef std::vector<bool> vect_bool;													// alias for vector of bools
typedef std::vector<int64_t> vect_int;													// alias for vector of ints
typedef std::pair<int64_t, int64_t> pair;												// alias for vector

// NOTE: sf:: is the namespace for all SFML functionalities declared in /include/SFML/... .hpp files 
 
// Forward declarations
class Button;
class Interface;

/**
 * Base class from which the sorting algorithms classes will inherit (Polymorphic class) 
 * The base class will allow us to create a sequence with n elements	
 */
class SortingAlgorithms
{
protected:
	std::vector<sf::RectangleShape> sequence;		// vector which will contain a randomized sequence
	std::vector<sf::RectangleShape> sequenceCpy;    // a copy of sequence used for interaction features
	sf::RenderWindow& window;						// initialization of the window
	int minimum, maximum;							// the range in which the elements will be randomized
	int elements;									// the number of elements which will be initialized

public:
	// SortingAlgorithms - default constructor
	SortingAlgorithms();

	/** SortingAlgorithms is a class constructor which initializes the sequence
	 *	@param min - the minimum value for randomizing
	 *  @param max - the maximum value for randomizing
	 *	@param els - the number of elements to generate
	 *	@param win - since the window will be initialized only once (singleton pattern); 
	 *				 it will be needed to pass on this object to almost every function that has graphics features
	 */
	SortingAlgorithms(int min, int max, int els, sf::RenderWindow& win);

	/** Sort is a pure virtual method for overriding the Sort method for different implementations 
	 *  of the sorting algorithms and param init which is what I described about win param from 
	 *  SortingAlgorithms constructor 
	 *	This pure virtual method can't be overriden with different number of parameters, but it can
	 *  be used as an entry point to an actual method with different no. of paramteres, e.g. merge
	 *  sort or quick sort
	 *  @param init - a referenced object to the first initialization of the window object
	 *  @return back where it was called last time (menu feature / navigating)
	 */
	virtual int Sort(std::unique_ptr<Interface>& init) = 0;

	/** IsSorted will check whether or not if the sequence is sorted
	 *  @return true if sorted, false otherwise
	 */
	bool IsSorted();

	// SortSeqCpy will sort the copied sequence which will be used for configuration bar features
	void SortSeq();

	/** Print method will print a sequence
	 *  @param init - a referenced object to the first initialization of the window object
	 *  @return back where it was called last time (menu feature / navigating)
	 */
	int Print(std::unique_ptr<Interface>& init);

	/** PrintSortedSeq will print the sorted sequence and it will color it with green color
	 *  @param init - a referenced object to the first initialization of the window object
	 *  @return back where it was called last time (menu feature / navigating)
	 */
	int PrintSortedSeq(std::unique_ptr<Interface>& init);
};

/** Base class from which the pathfinding algorithms classes will inherit (Polymorphic class)
 *  The base class will initialize a grid
 */
class PathFindingAlgorithms
{
protected:
	int rows = 23;							// size of the grid is rows x columns as specified : 
	int columns = 41;						// 23 x 41
	int size = rows * columns;				// size of grid / rows by columns
	int64_t start;		    				// start point
	int64_t end;      						// end point
	sf::RenderWindow& window;				// initialization of the window
	std::map<int64_t, vect_int> edges;		// this hmap will contain neighbours of a node
	std::map<pair, int64_t> weights;		// this hmap will contain the weights from a node to another
	std::tuple<uint32_t, uint32_t> weightIdx;	// a tuple used for getting the indices of a node from the graph / grid
	std::vector<std::vector<Button>> grid;	// the grid is a 2d vector of RectangleShape objects declared and defined in the Button class
											// each element of this vector will be initialized with "infinity" / maximum of a 64 bit integer
											// each element represent 1 unit in the grid / weighted graph 
public:
	// PathFindingAlgorithms is a class constructor which initializes the grid
	PathFindingAlgorithms(sf::RenderWindow& win);
	PathFindingAlgorithms(std::vector<std::vector<Button>> g, int64_t s, int64_t e, sf::RenderWindow& win);
	/** Visualize is a pure virtual method for overriding the Visualize method for different implementations
	 *  of the pathfinding algorithms and param init which is what I described about win param from
	 *  SortingAlgorithms constructor
	 *	This pure virtual method can't be overriden with different number of parameters, but it can
	 *  be used as an entry point to an actual method with different no. of paramteres (not needed)
	 *  @param init - a referenced object to the first initialization of the window object
	 *  @return back where it was called last time (menu feature / navigating)
	 */
	virtual int Visualize(std::unique_ptr<Interface>& init) = 0;
	/**
	 * FIND WEIGHT
	 * input: a 64-bit integer, a weight of an edge
	 * output: a tuple of 2 integers, representing the coordinate of the weight found
	 * according to the 2d vector / graph
	 * Finds the coordinated of weight of an edge and return its coordinates / indices
	 * as a tuple
	 */
	std::tuple<uint32_t, uint32_t> FindWeight(int64_t weight);
	/**
	 * PRINT PATH will print to the screen the final form of the graph / grid including the shortest path
	 * deduced by the algorithm to the screen
	 * This function has the role to print it continously, i.e., displayed, allowing the user to go back
	 * to a sub-menu
	 * @param init - a referenced object to the first initialization of the window object
	 * @return back where it was called last time (menu feature / navigating)
	 */
	int PrintPath(std::unique_ptr<Interface>& init);
};



#endif // ALGORITHMS_H_INCLUDED
	