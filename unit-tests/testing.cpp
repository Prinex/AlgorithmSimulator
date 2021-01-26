#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "SortingAlgorithms/BubbleSort.h"
#include "SortingAlgorithms/SelectionSort.h"
#include "SortingAlgorithms/InsertionSort.h"
#include "SortingAlgorithms/QuickSort.h"
#include "SortingAlgorithms/MergeSort.h"
/*
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
		std::vector<int> sorted;

		WHEN( "the vector is empty")
		{
			THEN( "nothing happens")
			{
				REQUIRE(BubbleSort(seq).size() == 0);
			}
		}
		AND_WHEN( "the vector is not empty")
		{
			seq = fillUpVector(10, 150, 77);
			
			REQUIRE(seq.size() != 0);
			REQUIRE(seq.size() > 0);

			THEN( "sorting occurs")
			{
				sorted = BubbleSort(seq);
				REQUIRE(sorted.size() != 0);
				REQUIRE(sorted.size() > 0);
			}
		}
	}
}

SCENARIO( "Sorting with Bubble Sort")
{
	GIVEN( "some vectors with random values")
	{
		std::vector<int> seq = fillUpVector(-32, 77, 20);
		std::vector<int> sorted;
		std::vector<int> seqCpy;

		WHEN( "sorting a small-sized vector")
		{
			seqCpy = seq;
			std::sort(seqCpy.begin(), seqCpy.end());

			THEN( "returns the sorted vector")
			{
				sorted = BubbleSort(seq);
				REQUIRE(BubbleSort(seq) == seqCpy);
				REQUIRE(sorted.size() == 20);
				REQUIRE(sorted.size() == seqCpy.size());
			}
		}
		AND_WHEN( "sorting a big-sized vector")
		{
			seq = fillUpVector(-578, 877, 100);
			seqCpy = seq;
			std::sort(seqCpy.begin(), seqCpy.end());

			THEN( "returns the sorted vector")
			{
				sorted = BubbleSort(seq);
				REQUIRE(sorted == seqCpy);
				REQUIRE(sorted.size() == 100);
				REQUIRE(sorted.size() == seqCpy.size());
			}
		}
	}
}

SCENARIO( "Selection Sort can be used with an empty or non-empty vector")
{
	GIVEN( "An empty vector")
	{
		std::vector<int> seq;
		std::vector<int> sorted;

		REQUIRE(seq.size() == 0);

		WHEN( "the vector is empty")
		{
			THEN( "nothing happens")
			{
				REQUIRE(SelectionSort(seq).size() == 0);
			}
		}
		AND_WHEN( "vector is not empty")
		{
			seq = fillUpVector(50, 123, 78);

			REQUIRE(seq.size() != 0);
			REQUIRE(seq.size() > 0);

			THEN( "sorting occurs")
			{
				sorted = SelectionSort(seq);
				REQUIRE(sorted.size() != 0);
				REQUIRE(sorted.size() > 0);
			}
		}
	}
}

SCENARIO( "Sorting with Selection Sort")
{
	GIVEN( "some vectors with random values")
	{
		std::vector<int> seq = fillUpVector(-21, 87, 32);
		std::vector<int> sorted;
		std::vector<int> seqCpy;

		WHEN( "sorting a small-sized vector")
		{
			seqCpy = seq;
			std::sort(seqCpy.begin(), seqCpy.end());

			THEN( "returns the sorted vector")
			{
				sorted = SelectionSort(seq);
				REQUIRE(sorted == seqCpy);
				REQUIRE(sorted.size() == 32);
				REQUIRE(sorted.size() == seqCpy.size());
			}
		}
		AND_WHEN( "sorting a big-sized vector")
		{
			seq = fillUpVector(-378, 877, 250);
			seqCpy = seq;
			std::sort(seqCpy.begin(), seqCpy.end());

			THEN( "returns the sorted vector")
			{
				sorted = SelectionSort(seq);
				REQUIRE(sorted == seqCpy);
				REQUIRE(sorted.size() == 250); 
				REQUIRE(sorted.size() == seqCpy.size());
			}
		}
	}
}

SCENARIO( "Insertion Sort can be used with an empty or non-empty vector")
{
	GIVEN( "An empty vector")
	{
		std::vector<int> seq;
		std::vector<int> sorted;

		WHEN( "the vector is empty")
		{
			THEN( "nothing happens")
			{
				REQUIRE(InsertionSort(seq).size() == 0);
			}
		}
		AND_WHEN( "vector is not empty")
		{
			seq = fillUpVector(74, 95, 78);

			REQUIRE(seq.size() != 0);
			REQUIRE(seq.size() > 0);

			THEN( "sorting occurs")
			{
				sorted = InsertionSort(seq);
				REQUIRE(sorted.size() != 0);
				REQUIRE(sorted.size() > 0);
			}
		}
	}
}

SCENARIO( "Sorting with Insertion Sort")
{
	GIVEN( "some vectors with random values")
	{
		std::vector<int> seq = fillUpVector(-6, 171, 43);
		std::vector<int> sorted;
		std::vector<int> seqCpy;
		 
		WHEN( "sorting a small-sized vector")
		{
			seqCpy = seq;
			std::sort(seqCpy.begin(), seqCpy.end());

			THEN( "returns the sorted vector")
			{
				sorted = InsertionSort(seq);
				REQUIRE(sorted == seqCpy);
				REQUIRE(sorted.size() == 43); 
				REQUIRE(sorted.size() == seqCpy.size());
			}
		}
		AND_WHEN( "sorting a big-sized vector")
		{
			seq = fillUpVector(-378, 477, 98);
			seqCpy = seq;
			std::sort(seqCpy.begin(), seqCpy.end());

			THEN( "returns the sorted vector")
			{
				sorted = InsertionSort(seq);
				REQUIRE(sorted == seqCpy);
				REQUIRE(sorted.size() == 98);
				REQUIRE(sorted.size() == seqCpy.size());
			}
		}
	}
}

SCENARIO( "Merge Sort can be used with an empty or non-empty vector")
{
	GIVEN( "An empty vector")
	{
		std::vector<int> seq;
		std::vector<int> sorted;

		WHEN( "the vector is empty")
		{
			THEN( "nothing happens")
			{
				MSort(seq, 0, seq.size() - 1);
				REQUIRE(seq.size() == 0);
			}
		}
		AND_WHEN( "vector is not empty")
		{
			seq = fillUpVector(74, 95, 78);

			REQUIRE(seq.size() != 0);
			REQUIRE(seq.size() > 0);

			THEN( "sorting occurs")
			{
				MSort(seq, 0, seq.size() - 1);
				REQUIRE(seq.size() != 0);
				REQUIRE(seq.size() > 0);
			}
		}
	}
}

SCENARIO( "Sorting with Merge Sort")
{
	GIVEN( "some vectors with random values")
	{
		std::vector<int> seq = fillUpVector(-10, 200, 30);
		std::vector<int> seqCpy;

		WHEN( "sorting a small-sized vector")
		{
			seqCpy = seq;
			std::sort(seqCpy.begin(), seqCpy.end());

			THEN( "returns the sorted vector")
			{
				MSort(seq, 0, seq.size() - 1);
				REQUIRE(seq == seqCpy);
				REQUIRE(seq.size() == 30);
				REQUIRE(seq.size() == seqCpy.size());
			}
		}
		AND_WHEN( "sorting a big-sized vector")
		{
			seq = fillUpVector(-378, 1000, 289);
			seqCpy = seq;
			std::sort(seqCpy.begin(), seqCpy.end());

			THEN( "returns the sorted vector")
			{
				MSort(seq, 0, seq.size() - 1);
				REQUIRE(seq == seqCpy);
				REQUIRE(seq.size() == 289);
				REQUIRE(seq.size() == seqCpy.size());
			}
		}
	}
}

SCENARIO( "Quick Sort can be used with an empty or non-empty vector")
{
	GIVEN( "An empty vector")
	{
		std::vector<int> seq;
		std::vector<int> sorted;

		WHEN( "vector is empty")
		{
			THEN( "nothing happens")
			{
				MSort(seq, 0, seq.size() - 1);
				REQUIRE(seq.size() == 0);
			}
		}
		AND_WHEN( "vector is not empty")
		{
			seq = fillUpVector(-35, 375, 32);

			REQUIRE(seq.size() != 0);
			REQUIRE(seq.size() > 0);

			THEN( "sorting happens")
			{
				sorted = QuickSort(seq, 0, seq.size() - 1);
				REQUIRE(sorted.size() != 0);
				REQUIRE(sorted.size() > 0);
			}
		}
	}
}

SCENARIO( "Sorting with Quick Sort")
{
	GIVEN( "A some vectors with random values")
	{
		std::vector<int> seq = fillUpVector(-20, 100, 70);
		std::vector<int> sorted;
		std::vector<int> seqCpy;

		WHEN( "sorting a small-sized vector")
		{
			seqCpy = seq;
			std::sort(seqCpy.begin(), seqCpy.end());

			THEN( "returns the sorted vector")
			{
				REQUIRE(QuickSort(seq, 0, seq.size() - 1) == seqCpy);
				REQUIRE(seq.size() == 70);
				REQUIRE(seq.size() == seqCpy.size());
			}
		}
		AND_WHEN( "sorting a big-sized vector")
		{
			seq = fillUpVector(-7, 787, 327);
			seqCpy = seq;
			std::sort(seqCpy.begin(), seqCpy.end());

			THEN( "returns the sorted vector")
			{
				sorted = QuickSort(seq, 0, seq.size() - 1);
				REQUIRE(sorted == seqCpy);
				REQUIRE(seq.size() == 327); 
				REQUIRE(sorted.size() == seqCpy.size());
			}
		}
	}
}