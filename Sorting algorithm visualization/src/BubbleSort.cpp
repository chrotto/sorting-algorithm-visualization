#include "BubbleSort.h"

BubbleSort::BubbleSort(vector<int> sortArray, int delay) : SortingAlgorithm(sortArray, delay, "Bubble Sort")
{
	// Nothing to do
}

void BubbleSort::runSort()
{
	bool sorted = false;
	int end = mSortArray.size();

	while (!sorted)
	{
		sorted = true;
		--end;
		for (int i = 0; i < end; i++)
		{
			if (SortingAlgorithm::compare(i, i + 1, [](int a, int b) {return a > b; }))
			{
				sorted = false;
				SortingAlgorithm::swap(i, i + 1);
			}
		}
	}
}