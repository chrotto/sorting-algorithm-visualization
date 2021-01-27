#pragma once
#include "SortingAlgorithm.h"

class GnomeSort : public SortingAlgorithm
{
public:
	GnomeSort(vector<int> sortArray, int delay);

	void runSort();
};