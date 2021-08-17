#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

std::vector<int> InsertionSort(std::vector<int>& sequence)
{
	std::vector<int>::iterator iti;
	int j;
	int leftmost;
	
	// prevent segmentation fault due to algorithm starting to sort from positon 1
	if (sequence.size() == 0)
		return sequence;
	for (iti = sequence.begin() + 1; iti != sequence.end(); iti = std::next(iti))
	{
		j = std::distance(sequence.begin(), std::prev(iti));
		leftmost = *iti;
		
		while (j >= 0 && sequence.at(j) > leftmost)
		{
			sequence.at(j + 1) = sequence.at(j);
			--j;
		}
		sequence.at(j + 1) = leftmost;
	}
	return sequence;
}

