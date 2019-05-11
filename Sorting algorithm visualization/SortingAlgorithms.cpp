#include "SortingAlgorithms.h"
#include <iostream>
#include <chrono>
#include <thread>

void SortingAlogrithms::initialize(vector<int> numbers, int delay)
{
	mNumbers = numbers;
	mFinished = false;
	mDelay = delay;
}

void SortingAlogrithms::bubbleSort()
{
	bool sorted = false;
	int end = mNumbers.size();

	while (!sorted)
	{
		sorted = true;
		--end;
		for (int i = 0; i < end; i++)
		{
			mComparison.emit(i, i + 1);
			this_thread::sleep_for(chrono::milliseconds(mDelay));
			if (mNumbers[i] > mNumbers[i + 1])
			{
				sorted = false;
				swap(i, i + 1);
			}
		}
	}
	mFinished = true;
}

void SortingAlogrithms::selectionSort()
{
	int min;
	for (int i = 0; i < mNumbers.size() - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < mNumbers.size(); j++)
		{
			mComparison.emit(min, j);
			this_thread::sleep_for(chrono::milliseconds(mDelay));
			if (mNumbers[min] > mNumbers[j])
				min = j;
		}
		if (min != i)
			swap(min, i);
	}
}

bool SortingAlogrithms::isFinished() const
{
	return mFinished;
}

void SortingAlogrithms::swap(int a, int b)
{
	std::swap(mNumbers[a], mNumbers[b]);
	mSwap.emit(a, b);
}