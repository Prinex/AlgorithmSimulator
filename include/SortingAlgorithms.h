#ifndef SORTINGALGORITHMS_H_INCLUDED
#define SORTINGALGORITHMS_H_INCLUDED


#include "Algorithms.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>



/* Down here are the child classes */
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
	int Sort(std::unique_ptr<Interface>& init);
	int MSort(std::unique_ptr<Interface>& init, unsigned long long int first, unsigned long long int last);
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
