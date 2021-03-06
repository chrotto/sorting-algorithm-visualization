#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <string>
#include <condition_variable>
#include "Signal.h"
using namespace std;

class SortingAlgorithm
{
public:
	typedef unique_ptr<SortingAlgorithm> Ptr;

	Signal<int, int> mSwap;
	Signal<int, int> mComparison;
	Signal<int, int> mValueUpdate;
	Signal<int> mPivotUpdate;
	Signal<int> mSorted;

protected:
	vector<int> mSortArray;

private:
	int mDelay;
	string mName;

	condition_variable mConditionalWait;
	mutex mWaitMutex;

public:
	SortingAlgorithm(vector<int> sortArray, int delay, const string& name);

	virtual void runSort() = 0;

	void setDelay(int delay);
	void wait();

	const string& getName() const;

protected:
	void swap(int a, int b);
	bool compare(int a, int b, function<bool(int, int)> compare);
	void updateValue(int index, int value);
	void updatePivot(int index);
	void markAsSorted();
};