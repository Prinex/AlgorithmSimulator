#pragma once

#include <vector>
#include <iostream>
#include <algorithm>


void Merge(std::vector<int>& sequence, int first, int mid, int last)
{
    int i, j, k;
    // for even and odd numbers
    int ls = mid - first + 1;
    int rs = last - mid;

    // left and right part of the sequence
    std::vector<int> leftSeq(ls);
    std::vector<int> rightSeq(rs);


    for (i = 0; i < ls; i++)
        leftSeq.at(i) = sequence.at(first + i);
    for (j = 0; j < rs; j++)
        rightSeq.at(j) = sequence.at(mid + 1 + j);

    // for even and odd numbers
    ls = mid - first + 1;
    rs = last - mid;

    leftSeq.resize(ls);
    rightSeq.resize(rs);

    // separating the sequence
    for (i = 0; i < ls; i++)
        leftSeq.at(i) = sequence.at(first + i);
    for (j = 0; j < rs; j++)
        rightSeq.at(j) = sequence.at(mid + 1 + j);

    i = 0;
    j = 0;
    k = first;

    // merging
    while (i < ls && j < rs)
    {
        if (leftSeq.at(i) <= rightSeq.at(j))
        {
            sequence.at(k) = leftSeq.at(i);
            i++;
        }
        else  
        {
            sequence.at(k) = rightSeq.at(j);
            j++;
        }
        k++;
    }
    // adding the numbers that are left either from left or right
    while (i < ls)
    {
        sequence.at(k) = leftSeq.at(i);
        i++;
        k++;
    }

    while (j < rs)
    {
        sequence.at(k) = rightSeq.at(j);
        j++;
        k++;
    }
}

void MSort(std::vector<int>& sequence, int first, int last)
{
    if (first < last)
    {
        int mid = (int)floor((first + last) / 2);

        MSort(sequence, first, mid);
        MSort(sequence, mid + 1, last);
        Merge(sequence, first, mid, last);
    }
}