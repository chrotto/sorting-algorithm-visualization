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
	string mName;

public:
	SortingAlgorithm(vector<int> sortArray, int delay, const string& name);

	virtual void runSort() = 0;

	const string& getName() const;

protected:
	void swap(int a, int b);
	bool compare(int a, int b, bool(*compare)(int, int));
};