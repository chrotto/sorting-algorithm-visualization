#pragma once
#include "SortingAlgorithm.h"

class SelectionSort : public SortingAlgorithm
{
private:
	int mArraySize;

public:
	SelectionSort(vector<int> sortArray, int delay);

	void runSort();
};