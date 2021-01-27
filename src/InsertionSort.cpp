#include "InsertionSort.h"

InsertionSort::InsertionSort(vector<int> sortArray, int delay) : SortingAlgorithm(sortArray, delay, "Insertion Sort"), mArraySize(sortArray.size())
{
	// Nothing to do
}

void InsertionSort::runSort()
{
	for (int i = 1; i < mArraySize; i++)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			if (SortingAlgorithm::compare(j, j + 1, [](int a, int b) { return a > b; }))
				SortingAlgorithm::swap(j, j + 1);
			else
				break;
		}
	}
	markAsSorted();
}