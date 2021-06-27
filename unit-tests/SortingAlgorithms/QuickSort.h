#pragma once

#include <iostream>
#include <algorithm>
#include <vector>


std::vector<int> QuickSort(std::vector<int>& sequence, int left, int right)
{
	int p = (left + right) / 2;
	int pivot = sequence.at(p);										// median pivot
	int l = left;													// left marker
	int r = right;													// right marker

	while (l <= r)													// while the left marker is not beyond the
	{																// right marker or if they are at the same position
		while (sequence.at(l) < pivot)								// while the left marker is less
		{															// than the pivot
			l++;													// move the left marker to the right
		}
		while (sequence.at(r) > pivot)								// while the right marker is greater
		{															// than the pivot
			r--;													// move the right marker to the left
		}
		if (l <= r)													// if the left marker is not beyond the
		{															// right marker or if they are at the same position
			std::swap(sequence.at(l), sequence.at(r));				// swap the markers
			if (p == l)												// if the left marker ran into the pivot
			{
				p = r;
			}
			else if (p == r)				 						// if the right marker ran into the pivot
			{
				p = l;
			}
			l++;													// move the left marker to the right
			r--;													// move the right marker to the left
		}
	}
	if (left < r)													// recurse the left side of elements 
		QuickSort(sequence, left, r);								// less than the pivot
	if (l < right)													// recurse the right side of elements
		QuickSort(sequence, l, right);								// bigger than the pivot
	return sequence;												// return the sorted sequence
}
