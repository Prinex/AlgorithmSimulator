#ifndef SORTINGALGORITHMS_H_INCLUDED
#define SORTINGALGORITHMS_H_INCLUDED


#include "Algorithms.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>



// child classes 
class BubbleSort : public SortingAlgorithms
{
public:
	BubbleSort(int min, int max, int els, sf::RenderWindow& win);
	int Sort(std::unique_ptr<Interface>& init);
};


class SelectionSort : public SortingAlgorithms
{
public:
	SelectionSort(int min, int max, int els, sf::RenderWindow& win);
	int Sort(std::unique_ptr<Interface>& init);
};


class InsertionSort : public SortingAlgorithms
{
public:
	InsertionSort(int min, int max, int els, sf::RenderWindow& win);
	int Sort(std::unique_ptr<Interface>& init);
};


class MergeSort : public SortingAlgorithms
{
public:
	MergeSort(int min, int max, int els, sf::RenderWindow& win);
	/** Here, merge sort is done in a recursive way.
	 *  Sort method will be just an entry point for the MSort method where all sorting steps occur
	 */
	int Sort(std::unique_ptr<Interface>& init);
	/** MSort will be used for the recursively 
	 *  @param init - a referenced object to the first initialization of the window object
	 *  @param first - a 64bit unsgined integer for omitting overflowing pointing to the first index of a sequence
	 *  @param last - a 64bit unsgined integer for omitting overflowing pointing to the last index of a sequence
	 *  @return back where it was called last time (menu feature / navigating)
	 */
	int MSort(std::unique_ptr<Interface>& init, unsigned long long int first, unsigned long long int last);
	/** Merge will to merge the two sides of the sequence (left and right)
	 *  @param init - a referenced object to the first initialization of the window object
	 *  @param first - a 64bit unsgined integer for omitting overflowing pointing to the first index of a sequence
	 *  @param mid - a 64bit unsgined integer for omitting overflowing pointing to the middle index of a sequence
	 *  @param last - a 64bit unsgined integer for omitting overflowing pointing to the last index of a sequence
	 *  @return back where it was called last time (menu feature / navigating)
	 */
	int Merge(std::unique_ptr<Interface>& init, unsigned long long int first, unsigned long long int mid, unsigned long long int last);
    
};


class QuickSort : public SortingAlgorithms
{
public:
	QuickSort(int min, int max, int els, sf::RenderWindow& win);
	int Sort(std::unique_ptr<Interface>& init);
};


class HeapSort : public SortingAlgorithms
{
public:
	HeapSort(int min, int max, int els, sf::RenderWindow& win);
	int Sort(std::unique_ptr<Interface>& init);
};


#endif // SORTINGALGORITHMS_H_INCLUDED
