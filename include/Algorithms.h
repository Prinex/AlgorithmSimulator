#ifndef ALGORITHMS_H_INCLUDED
#define ALGORITHMS_H_INCLUDED



#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

// NOTE: sf:: prefix is SFML and everything after it are defined in the SFML/... .hpp files 
 
// Forward declaration
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
	sf::RenderWindow& window;						// initializes the window
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
	 *  of the sorting algorithms and param init 
	 *  which is what I described about win param from SortingAlgorithms constructor 
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






#endif // ALGORITHMS_H_INCLUDED
