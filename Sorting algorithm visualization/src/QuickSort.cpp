#include "QuickSort.h"

QuickSort::QuickSort(vector<int> sortArray, int delay) : SortingAlgorithm(sortArray, delay, "Quick Sort")
{
	// Nothing to do
}

void QuickSort::runSort()
{
	quickSort(0, mSortArray.size() - 1);
}

void QuickSort::quickSort(int lo, int hi)
{
	int i = lo, j = hi, pivotIndex = lo + (hi - lo) / 2;
	int pivot = mSortArray[pivotIndex];
	updatePivot(pivotIndex);

	while (i <= j)
	{
		while (compare(i, pivotIndex, [](int a, int b) {return a < b; })) i++;
		while (compare(j, pivotIndex, [](int a, int b) {return a > b; })) j--;

		if (i <= j)
		{
			if (pivotIndex == i)
				pivotIndex = j;
			else if (pivotIndex == j)
				pivotIndex = i;
			swap(i, j);
			i++;
			j--;
		}
	}

	if(lo < j)
		quickSort(lo, j);
	if(i < hi)
		quickSort(i, hi);
}