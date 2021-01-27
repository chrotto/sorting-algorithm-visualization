#pragma once
#include "SortingAlgorithm.h"

class QuickSort : public SortingAlgorithm
{
public:
	QuickSort(vector<int> sortArray, int delay);

	void runSort();

private:
	void quickSort(int lo, int hi);
};

