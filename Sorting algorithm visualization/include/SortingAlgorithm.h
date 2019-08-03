#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Signal.h"
using namespace std;

class SortingAlgorithm
{
public:
	typedef unique_ptr<SortingAlgorithm> Ptr;

	Signal<int, int> mSwap;
	Signal<int, int> mComparison;
	Signal<int, int> mValueUpdate;
	Signal<int, int> mMarkGroup;
	Signal<int> mPivotUpdate;

protected:
	vector<int> mSortArray;

private:
	int mDelay;
	string mName;

public:
	SortingAlgorithm(vector<int> sortArray, int delay, const string& name);

	virtual void runSort() = 0;

	const string& getName() const;

protected:
	void swap(int a, int b);
	bool compare(int a, int b, bool(*compare)(int, int));
	void updateValue(int index, int value);
	void markGroup(int start, int end);
	void updatePivot(int index);
};