#include "SelectionSort.h"

SelectionSort::SelectionSort(vector<int> sortArray, int delay) : SortingAlgorithm(sortArray, delay), mArraySize(sortArray.size())
{
	// Nothing to do
}

void SelectionSort::runSort()
{
	int min;
	for (int i = 0; i < mArraySize - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < mArraySize; j++)
		{
			if (SortingAlgorithm::compare(min, j, [](int a, int b) {return a > b; }))
				min = j;
		}
		if (min != i)
			SortingAlgorithm::swap(min, i);
	}
}