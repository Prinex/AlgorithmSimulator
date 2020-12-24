#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "SortingAlgorithms/BubbleSort.h"
#include "SortingAlgorithms/SelectionSort.h"
/*
#include "SortingAlgorithms/InsertionSort.h"
#include "SortingAlgorithms/MergeSort.h"
#include "SortingAlgorithms/QuickSort.h"
#include "SortingAlgorithms/HeapSort.h"
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

/** fillUpVector function will generate a sequence between [min, max] of units
 *  @param min - a minimum integer number
 *  @param max - a maximum integer number
 *  @param units - the number of units to generate
 *  @return vector - a generated sequence
 */ 
std::vector<int> fillUpVector(int min, int max, int units)
{
	std::vector<int> seq;
	int unitGenerated = 0;
	srand(time(NULL));

	for (int i = 0; i < units; i++)
	{
		unitGenerated = rand() % max + min;
		seq.push_back(unitGenerated);
	}
	return seq;
}

SCENARIO( "Bubble Sort can be used with an empty or non-empty vector")
{
	GIVEN( "An empty vector")
	{
		std::vector<int> seq;
		
		REQUIRE(seq.size() == 0);

		WHEN( "vector is empty")
		{
			THEN( "nothing happens, returning 0")
			{
				REQUIRE(BubbleSort(seq).size() == seq.size());
			}
		}
		AND_WHEN( "vector is not empty")
		{
			seq = fillUpVector(10, 150, 77);
			
			REQUIRE(seq.size() != 0);
			REQUIRE(seq.size() >= 0);

			THEN( "something happens, not returning 0")
			{
				REQUIRE(BubbleSort(seq).size() == seq.size());
				REQUIRE(BubbleSort(seq).size() >= seq.size());
			}
		}
	}
}

SCENARIO( "Sorting with Bubble Sort")
{
	GIVEN( "A vector with random values")
	{
		std::vector<int> seq = fillUpVector(10, 100, 77);
		std::vector<int> seqCpy; 

		REQUIRE(seq.size() > 0);

		WHEN( "vector is not sorted")
		{
			seqCpy = seq;
			THEN( "returns the unsorted vector")
			{
				REQUIRE(BubbleSort(seq) != seqCpy);
			}
		}
		AND_WHEN( "the vector has been sorted")
		{
			std::sort(seq.begin(), seq.end());
			THEN( "returns the sorted vector")
			{
				REQUIRE(BubbleSort(seq) == seq);
			}
		}
	}
}


SCENARIO( "Selection Sort can be used with an empty or non-empty vector")
{
	GIVEN( "An empty vector")
	{
		std::vector<int> seq;

		REQUIRE(seq.size() == 0);

		WHEN( "vector is empty")
		{
			THEN( "nothing happens, returning 0")
			{
				REQUIRE(SelectionSort(seq).size() == seq.size());
			}
		}
		AND_WHEN( "vector is not empty")
		{
			seq = fillUpVector(10, 150, 77);

			REQUIRE(seq.size() != 0);
			REQUIRE(seq.size() >= 0);

			THEN( "something happens, not returning 0")
			{
				REQUIRE(SelectionSort(seq).size() == seq.size());
				REQUIRE(SelectionSort(seq).size() >= seq.size());
			}
		}
	}
}

SCENARIO( "Sorting with Selection Sort")
{
	GIVEN( "A vector with random values")
	{
		std::vector<int> seq = fillUpVector(10, 100, 77);
		std::vector<int> seqCpy;

		REQUIRE(seq.size() > 0);

		WHEN( "vector is not sorted")
		{
			seqCpy = seq;
			THEN( "returns the unsorted vector")
			{
				REQUIRE(SelectionSort(seq) != seqCpy);
			}
		}
		AND_WHEN( "the vector has been sorted")
		{
			std::sort(seq.begin(), seq.end());
			THEN( "returns the sorted vector")
			{
				REQUIRE(SelectionSort(seq) == seq);
			}
		}
	}
}