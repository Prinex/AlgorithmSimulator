#pragma once

#include <vector>
#include <algorithm>

std::vector<int> BubbleSort(std::vector<int>& sequence)
{
	for (unsigned int i = 0; i < sequence.size(); i++)
	{
		for (std::vector<int>::iterator itj = sequence.begin(); itj != sequence.end() - 1; itj = std::next(itj))
		{
			if (*itj > *std::next(itj))
				std::swap(*itj, *std::next(itj));
		}
	}
	return sequence;
}