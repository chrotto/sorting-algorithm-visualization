#pragma once
#include "SortingAlgorithm.h"

class BubbleSort : public SortingAlgorithm
{
private:
	int mArraySize;

public:
	BubbleSort(vector<int> sortArray, int delay);

	void runSort();
};