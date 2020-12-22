#pragma once


#include <vector>
#include <iostream>
#include <algorithm>


//	1. SELECT THE PIVOT ELEMENT (LAST, FIRST, MID)
//	2. Run a while loop which has the conditon of first >= last when the two pointers meet eachother
//	3. separate the elements that are less than the pivot and elements that are greater or equal to the pivot 
//  4. if l < pivot (found) and r >= pivot (found) swap l and r
//  5. if l == r swap this value with the pivot  

void Separate(std::vector<int>& sequence, int first, int last, int& pivot)
{
	pivot = (first + last) / 2;

	int left = 0;
	int right = 0;
	int l = first;
	int r = last;

	while (sequence.at(l) != sequence.at(r))
	{
		if (sequence.at(l) >= sequence.at(pivot))
		{
			left = l;
		}
		else 
		{
			++l;
		}
		if (sequence.at(r) < sequence.at(pivot))
		{
			right = r;
		}
		else
		{
			--r;
		}
		if (sequence.at(l) >= sequence.at(pivot) && sequence.at(r) < sequence.at(pivot))
		{
			std::swap(sequence.at(l), sequence.at(r));
		}
		if (l == r)
		{
			std::swap(sequence.at(l), sequence.at(pivot));
			pivot = l;
		}

		
	}
}

std::vector<int> QuickSort(std::vector<int>& sequence, int first, int last, int& pivot)
{
	if (first < last)
	{
		Separate(sequence, first, last, pivot);
		QuickSort(sequence, first, pivot - 1);
		QuickSort(sequence, pivot + 1, last);
	}

	return sequence;
}

  