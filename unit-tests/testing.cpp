#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "SortingAlgorithms/BubbleSort.h"
#include "SortingAlgorithms/SelectionSort.h"
#include "SortingAlgorithms/InsertionSort.h"
/*
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
				REQUIRE(BubbleSort(seq).size() == 0);
			}
		}
		AND_WHEN( "vector is not empty")
		{
			seq = fillUpVector(10, 150, 77);
			
			REQUIRE(seq.size() != 0);
			REQUIRE(seq.size() > 0);

			THEN( "something happens, not returning 0")
			{
				REQUIRE(BubbleSort(seq).size() != 0);
				REQUIRE(BubbleSort(seq).size() > 0);
			}
		}
	}
}

SCENARIO( "Sorting with Bubble Sort")
{
	GIVEN( "A some vectors with random values")
	{
		std::vector<int> seq = fillUpVector(-32, 77, 20);
		std::vector<int> seqCpy;

		REQUIRE(seq.size() == 20);

		WHEN( "sorting a small-sized vector")
		{
			seqCpy = seq;
			std::sort(seqCpy.begin(), seqCpy.end());

			THEN( "returns the sorted vector")
			{
				REQUIRE(BubbleSort(seq) == seqCpy);
			}
		}
		AND_WHEN( "sorting a big-sized vector")
		{
			seq = fillUpVector(-578, 877, 100);
			seqCpy = seq;
			std::sort(seqCpy.begin(), seqCpy.end());

			THEN( "returns the sorted vector")
			{
				REQUIRE(seq.size() == 100);
				REQUIRE(BubbleSort(seq) == seqCpy);
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
			REQUIRE(seq.size() > 0);

			THEN( "something happens, not returning 0")
			{
				REQUIRE(SelectionSort(seq).size() != 0);
				REQUIRE(SelectionSort(seq).size() > 0);
			}
		}
	}
}

SCENARIO( "Sorting with Selection Sort")
{
	GIVEN("A some vectors with random values")
	{
		std::vector<int> seq = fillUpVector(-25, 47, 32);
		std::vector<int> seqCpy;

		REQUIRE(seq.size() == 32);

		WHEN("sorting a small-sized vector")
		{
			seqCpy = seq;
			std::sort(seqCpy.begin(), seqCpy.end());
			THEN("returns the sorted vector")
			{
				REQUIRE(SelectionSort(seq) == seqCpy);
			}
		}
		AND_WHEN("sorting a big-sized vector")
		{
			seq = fillUpVector(-432, 563, 89);
			seqCpy = seq;
			std::sort(seqCpy.begin(), seqCpy.end());

			THEN("returns the sorted vector")
			{
				REQUIRE(seq.size() == 89);
				REQUIRE(SelectionSort(seq) == seqCpy);
			}
		}
	}
}

SCENARIO( "Insertion Sort can be used with an empty or non-empty vector")
{
	GIVEN( "An empty vector")
	{
		std::vector<int> seq;

		REQUIRE(seq.size() == 0);

		WHEN( "vector is empty")
		{
			THEN( "nothing happens, returning 0")
			{
				REQUIRE(InsertionSort(seq).size() == 0);
			}
		}
		AND_WHEN( "vector is not empty")
		{
			seq = fillUpVector(10, 150, 20);

			REQUIRE(seq.size() != 0);
			REQUIRE(seq.size() > 0);

			THEN( "something happens, not returning 0")
			{
				REQUIRE(InsertionSort(seq).size() != 0);
				REQUIRE(InsertionSort(seq).size() > 0);
			}
		}
	}
}

SCENARIO( "Sorting with Insertion Sort")
{
	GIVEN("A some vectors with random values")
	{
		std::vector<int> seq = fillUpVector(-47, 68, 40);
		std::vector<int> seqCpy;

		REQUIRE(seq.size() == 40);

		WHEN("sorting a small-sized vector")
		{
			seqCpy = seq;
			std::sort(seqCpy.begin(), seqCpy.end());
			THEN("returns the sorted vector")
			{
				REQUIRE(InsertionSort(seq) == seqCpy);
			}
		}
		AND_WHEN("sorting a big-sized vector")
		{
			seq = fillUpVector(-4, 789, 252);
			seqCpy = seq;
			std::sort(seqCpy.begin(), seqCpy.end());

			THEN("returns the sorted vector")
			{
				REQUIRE(seq.size() == 252);
				REQUIRE(InsertionSort(seq) == seqCpy);
			}
		}
	}
}

SCENARIO( "Merge Sort can be used with an empty or non-empty vector")
{
	GIVEN( "An empty vector")
	{
		std::vector<int> seq;

		REQUIRE(seq.size() == 0);

		WHEN( "vector is empty")
		{
			THEN( "nothing happens, returning 0")
			{
				REQUIRE(InsertionSort(seq).size() == 0);
			}
		}
		AND_WHEN( "vector is not empty")
		{
			seq = fillUpVector(-20, 220, 25);

			REQUIRE(seq.size() != 0);
			REQUIRE(seq.size() > 0);

			THEN( "something happens, not returning 0")
			{
				REQUIRE(InsertionSort(seq).size() != 0);
				REQUIRE(InsertionSort(seq).size() > 0);
			}
		}
	}
}

SCENARIO( "Sorting with Merge Sort")
{
	GIVEN( "A some vectors with random values")
	{
		std::vector<int> seq = fillUpVector(-20, 100, 70);
		std::vector<int> seqCpy;

		REQUIRE(seq.size() == 70);

		WHEN( "sorting a small-sized vector")
		{
			seqCpy = seq;
			std::sort(seqCpy.begin(), seqCpy.end());
			THEN( "returns the sorted vector")
			{
				REQUIRE(InsertionSort(seq) == seqCpy);
			}
		}
		AND_WHEN( "sorting a big-sized vector")
		{
			seq = fillUpVector(-4, 777, 321);
			seqCpy = seq;
			std::sort(seqCpy.begin(), seqCpy.end());

			THEN( "returns the sorted vector")
			{
				REQUIRE(seq.size() == 321);
				REQUIRE(InsertionSort(seq) == seqCpy);
			}
		}
	}
}
