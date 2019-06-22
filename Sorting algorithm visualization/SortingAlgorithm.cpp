#include "SortingAlgorithm.h"
#include <chrono>
#include <thread>

SortingAlgorithm::SortingAlgorithm(vector<int> sortArray, int delay) : mSortArray(sortArray), mDelay(delay)
{
	// Nothing to do
}

void SortingAlgorithm::swap(int a, int b)
{
	mSwap.emit(a, b);
	this_thread::sleep_for(chrono::milliseconds(mDelay));
	std::swap(mSortArray[a], mSortArray[b]);
}

bool SortingAlgorithm::compare(int a, int b, bool(*compare)(int, int))
{
	mComparison.emit(a, b);
	this_thread::sleep_for(chrono::milliseconds(mDelay));
	return compare(mSortArray[a], mSortArray[b]);
}