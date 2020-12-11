#pragma once
#include "SortingAlgorithm.h"

class BubbleSort : public SortingAlgorithm
{
public:
	BubbleSort(vector<int> sortArray, int delay);

	void runSort();
};