#include "SortingAlgorithm.h"
#include <chrono>
#include <thread>

SortingAlgorithm::SortingAlgorithm(vector<int> sortArray, int delay, const string& name) : mSortArray(sortArray), mDelay(delay), mName(name)
{
	// Nothing to do
}

const string& SortingAlgorithm::getName() const
{
	return mName;
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

void SortingAlgorithm::updateValue(int index, int value)
{
	mValueUpdate.emit(index, value);
	this_thread::sleep_for(chrono::milliseconds(mDelay));
	mSortArray[index] = value;
}

void SortingAlgorithm::markGroup(int start, int end)
{
	mMarkGroup.emit(start, end);
}