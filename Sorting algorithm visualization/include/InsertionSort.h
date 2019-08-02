#pragma once
#include "SortingAlgorithm.h"

class InsertionSort : public SortingAlgorithm
{
private:
	int mArraySize;

public:
	InsertionSort(vector<int> sortArray, int delay);

	void runSort();
};