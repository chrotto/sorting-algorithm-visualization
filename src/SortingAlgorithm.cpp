#include "SortingAlgorithm.h"
#include <chrono>
#include <thread>

SortingAlgorithm::SortingAlgorithm(vector<int> sortArray, int delay, const string& name) : mSortArray(sortArray), mDelay(delay), mName(name)
{
	// Nothing to do
}

void SortingAlgorithm::setDelay(int delay)
{
	unique_lock<mutex> lock(mWaitMutex);
	mDelay = delay;
	mConditionalWait.notify_one();
}

void SortingAlgorithm::wait()
{
	unique_lock<mutex> lock(mWaitMutex);
	mConditionalWait.wait_for(lock, chrono::milliseconds(mDelay), [this] {return mDelay == 0; });
}

const string& SortingAlgorithm::getName() const
{
	return mName;
}

void SortingAlgorithm::swap(int a, int b)
{
	mSwap.emit(a, b);
	wait();
	std::swap(mSortArray[a], mSortArray[b]);
}

bool SortingAlgorithm::compare(int a, int b, function<bool(int, int)> compare)
{
	mComparison.emit(a, b);
	wait();
	return compare(mSortArray[a], mSortArray[b]);
}

void SortingAlgorithm::updateValue(int index, int value)
{
	mValueUpdate.emit(index, value);
	wait();
	mSortArray[index] = value;
}

void SortingAlgorithm::updatePivot(int index)
{
	mPivotUpdate.emit(index);
}

void SortingAlgorithm::markAsSorted()
{
	for (int i = 0; i < mSortArray.size(); i++)
	{
		mSorted.emit(i);
		wait();
	}
}
