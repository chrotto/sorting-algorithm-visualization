#pragma once
#include "SortingAlgorithm.h"

class MergeSort : public SortingAlgorithm
{
public:
	MergeSort(vector<int> sortArray, int delay);

	void runSort();

private:
	void mergeSort(int lo, int hi);
	void merge(int lo, int mid, int hi);
};
