#pragma once
#include <vector>
#include "Signal.h"
using namespace std;

class SortingAlogrithms
{
public:
	Signal<int, int> mSwap;
	Signal<int, int> mComparison;

private:
	vector<int> mNumbers;
	int mDelay;
	bool mFinished;

public:
	void initialize(vector<int> numbers, int delay = 500);

	void bubbleSort();
	void selectionSort();

	bool isFinished() const;

private:
	void swap(int a, int b);
};