#pragma once

#include <iostream>
#include <algorithm>
#include <vector>


void Heapify(std::vector<int>& A, int start, int end)
{
	int root = start;
	int temp = root;
	int child = 2 * root + 1;
	if (child < end && A.at(temp) < A.at(child))
		temp = child;
	if (child + 1 < end && A.at(temp) < A.at(child + 1))
		temp = child + 1;
	if (temp != root)
	{
		std::swap(A.at(root), A.at(temp));
		Heapify(A, temp, end);
	}
}

/**
 *  Call heapify once
 *  swap the first parent which has the
 *  greatest value with the last child
 *  leaf node
 */
std::vector<int> HeapSort(std::vector<int>& A, int start, int count)
{
	for (int i = start; i >= 0; i--)
		Heapify(A, i, count);
	int end = A.size() - 1;
	for (int i = end; i >= 0; i--)
	{
		std::swap(A.at(i), A.at(0));
		Heapify(A, 0, i);
	}
	return A;
}