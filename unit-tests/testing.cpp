#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "SortingAlgorithms/BubbleSort.hpp"
#include "SortingAlgorithms/SelectionSort.hpp"
#include "SortingAlgorithms/InsertionSort.hpp"
#include "SortingAlgorithms/QuickSort.hpp"
#include "SortingAlgorithms/MergeSort.hpp"
#include "SortingAlgorithms/HeapSort.hpp"
#include "PathFindingAlgorithms/Dijkstra.hpp"
#include "PathFindingAlgorithms/DepthFirstSearch.hpp"
#include "PathFindingAlgorithms/BreadthFirstSearch.hpp"
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

// testing sorting algorithms
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
	GIVEN( "some vectors with random values")
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

SCENARIO( "Heap Sort can be used with an empty or non-empty vector")
{
	GIVEN( "An empty vector")
	{
		std::vector<int> seq;
		std::vector<int> sorted;

		WHEN( "vector is empty")
		{
			THEN( "nothing happens")
			{
				HeapSort(seq, seq.size() / 2 - 1, seq.size());
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
				sorted = HeapSort(seq, seq.size() / 2 - 1, seq.size());
				REQUIRE(sorted.size() != 0);
				REQUIRE(sorted.size() > 0);
			}
		}
	}
}

SCENARIO( "Sorting with Heap Sort")
{
	GIVEN( "some vectors with random values")
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
				REQUIRE(HeapSort(seq, seq.size() / 2 - 1, seq.size()) == seqCpy);
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
				sorted = HeapSort(seq, seq.size() / 2 - 1, seq.size());
				REQUIRE(sorted == seqCpy);
				REQUIRE(seq.size() == 327);
				REQUIRE(sorted.size() == seqCpy.size());
			}
		}
	}
}

// testing the pathfinding algorithms
SCENARIO( "Finding the shortest path using Dijkstra Algorithm")
{
	GIVEN( "some instances of the Dijkstra algorithm with different starting and ending points")
	{
		Dijkstra d = Dijkstra(1, 474);
		std::tuple<vect_int, int64_t> r = d.dijkstra();
		std::tuple<vect_int, int64_t> solution({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 64, 105, 146, 187, 228, 269, 310, 351, 392, 433, 474}, 33);

		WHEN( "Finding the shortest path of a short distance between two points")
		{
			THEN("returns the shortest path specifying the nodes and the total cost")
			{
				// checking if there are the same nodes
				for (uint32_t i = 0; i < std::get<0>(r).size(); i++)
					REQUIRE(std::get<0>(r).at(i) == std::get<0>(solution).at(i));
				// checking if the cost is the same
				REQUIRE(std::get<1>(r) == std::get<1>(solution));
			}
		}
		AND_WHEN( "Finding the shortest path of a long distance between two points")
		{
			d = Dijkstra(899, 47);
			std::tuple<vect_int, int64_t> r = d.dijkstra();
			std::tuple<vect_int, int64_t> solution({899, 858, 817, 776, 735, 694, 653, 612, 571, 530, 489, 448, 407, 366, 325, 284, 243, 202, 161, 120, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 
													68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47}, 52);
												
			THEN( "returns the shortest path specifying the nodes and the total cost")
			{
				// checking if there are the same nodes
				for (uint32_t i = 0; i < std::get<0>(r).size(); i++)
					REQUIRE(std::get<0>(r).at(i) == std::get<0>(solution).at(i));
				// checking if the cost is the same
				REQUIRE(std::get<1>(r) == std::get<1>(solution));
			}
		}
	}
} 

SCENARIO( "Finding the shortest path using Depth First Search Algorithm")
{
	GIVEN( "some instances of the Depth First Search algorithm with different starting and ending points")
	{
		DepthFirstSearch d = DepthFirstSearch(1, 3);
		vect_int r = d.DFS();
		vect_int solution = { 1, 2, 3};

		WHEN( "Finding the shortest path of a short distance between two points")
		{
			THEN("returns the shortest path specifying the nodes")
			{
				// check if there are the same amount of nodes
				REQUIRE(r.size() == solution.size());
				// checking if there are the same nodes
				for (uint32_t i = 0; i < solution.size(); i++)
					REQUIRE(r.at(i) == solution.at(i));
			}
		}
		AND_WHEN( "Finding the shortest path of a long distance between two points")
		{
			d = DepthFirstSearch(1, 10);
			vect_int r = d.DFS();
			vect_int solution = { 1, 2, 3, 6, 9, 12, 11, 8, 5, 4, 7, 10 };
			
			THEN( "returns the shortest path specifying the nodes")
			{
				// check if there are the same amount of nodes
				REQUIRE(r.size() == solution.size());
				// checking if there are the same nodes
				for (uint32_t i = 0; i < solution.size(); i++)
					REQUIRE(r.at(i) == solution.at(i));
			}
		}
	}
} 

SCENARIO( "Finding the shortest path using Breadth First Search Algorithm")
{
	GIVEN( "some instances of the Breadth First Search algorithm with different starting and ending points")
	{
		BreadthFirstSearch d = BreadthFirstSearch(1, 93);
		vect_int r = d.BFS();
		vect_int solution = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 52, 93 };
	

		WHEN( "Finding the shortest path of a short distance between two points")
		{
			THEN( "returns the shortest path specifying the nodes")
			{
				// check if there are the same amount of nodes
				REQUIRE(r.size() == solution.size());
				// checking if there are the same nodes
				for (uint32_t i = 0; i < solution.size(); i++)
					REQUIRE(r.at(i) == solution.at(i));
			}
		}
		AND_WHEN( "Finding the shortest path of a long distance between two points")
		{
			d = BreadthFirstSearch(903, 472);
			vect_int r = d.BFS();
			vect_int solution = { 903, 862, 821, 780, 739, 698, 657, 616, 575, 534, 493, 452, 453, 454, 455, 456, 457, 458, 459, 460, 461, 462, 463, 464, 465, 466, 467, 468, 469, 470, 471, 472 };

			THEN( "returns the shortest path specifying the nodes")
			{
				// check if there are the same amount of nodes
				REQUIRE(r.size() == solution.size());
				// checking if there are the same nodes
				for (uint32_t i = 0; i < solution.size(); i++)
					REQUIRE(r.at(i) == solution.at(i));
			}
		}
	}
}
