#pragma once

#include <iostream>
#include <algorithm>
#include <vector>


std::vector<int> QuickSort(std::vector<int>& sequence, int left, int right)
{
	int pivot = (left + right) / 2;
	int l = left;
	int r = right;

	while (l <= r)
	{
		while (sequence.at(l) < sequence.at(pivot))
		{
			l++;
		}
		while (sequence.at(r) > sequence.at(pivot))
		{
			r--;
		}
		if (l <= r)
		{
			std::swap(sequence.at(l), sequence.at(r));
			if (pivot == l) pivot = r;
			else if (pivot == r) pivot = l;
			l++;
			r--;
		}
	}
	if (left < l)
		QuickSort(sequence, left, r);
	if (r < right)
		QuickSort(sequence, l, right);
	return sequence;
}
