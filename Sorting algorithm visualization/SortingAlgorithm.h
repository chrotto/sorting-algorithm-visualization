#pragma once
#include <vector>
#include <memory>
#include "Signal.h"
using namespace std;

class SortingAlgorithm
{
public:
	typedef unique_ptr<SortingAlgorithm> Ptr;

	Signal<int, int> mSwap;
	Signal<int, int> mComparison;

private:
	vector<int> mSortArray;
	int mDelay;

public:
	SortingAlgorithm(vector<int> sortArray, int delay);

	virtual void runSort() = 0;

protected:
	void swap(int a, int b);
	bool compare(int a, int b, bool(*compare)(int, int));
};