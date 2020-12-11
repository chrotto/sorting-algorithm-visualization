#include "MergeSort.h"

MergeSort::MergeSort(vector<int> sortArray, int delay) : SortingAlgorithm(sortArray, delay, "Merge Sort")
{
	// Nothing to do
}

void MergeSort::runSort()
{
	mergeSort(0, mSortArray.size() - 1);
}

void MergeSort::mergeSort(int lo, int hi)
{
	if (lo < hi)
	{
		int mid = lo + (hi - lo) / 2;
		mergeSort(lo, mid);
		mergeSort(mid + 1, hi);
		merge(lo, mid, hi);
	}
}

void MergeSort::merge(int lo, int mid, int hi)
{
	int j = lo;
	vector<int> leftPartArray;
	while (j <= mid)
		leftPartArray.push_back(mSortArray[j++]);

	int i = 0, k = lo;
	while (k < j && j <= hi)
	{
		if (leftPartArray[i] <= mSortArray[j])
			SortingAlgorithm::updateValue(k++, leftPartArray[i++]);
		else
			SortingAlgorithm::updateValue(k++, mSortArray[j++]);
	}

	while (k < j)
		SortingAlgorithm::updateValue(k++, leftPartArray[i++]);
}