#include "GnomeSort.h"

GnomeSort::GnomeSort(vector<int> sortArray, int delay) : SortingAlgorithm(sortArray, delay, "Gnome Sort")
{
	// Nothing to do
}

void GnomeSort::runSort()
{
	int i = 1;
	while (i < mSortArray.size())
	{
		if (i == 0)
			++i;
		if (compare(i, i - 1, [](int a, int b) {return a >= b; }))
		{
			i++;
		}
		else
		{
			swap(i, i - 1);
			i--;
		}
	}
	markAsSorted();
}