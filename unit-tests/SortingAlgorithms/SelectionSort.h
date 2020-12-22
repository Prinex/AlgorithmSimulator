#pragma once

#include <vector>
#include <algorithm>

std::vector<int> SelectionSort(std::vector<int>& sequence)
{
	std::vector<int>::iterator min;

	for (std::vector<int>::iterator iti = sequence.begin(); iti != sequence.end(); iti = std::next(iti))
	{
		min = iti;
		for (std::vector<int>::iterator itj = std::next(iti); itj != sequence.end(); itj = std::next(itj))
		{
			if (*min > *itj)
			{
				min = itj;
			}
		}
		std::swap(*min, *iti);
	}
	return sequence;
}

