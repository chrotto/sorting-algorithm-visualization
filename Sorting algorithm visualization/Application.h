#pragma once
#include <vector>
#include <thread>
#include <SFML/Graphics.hpp>
#include "SortingAlgorithms.h"
using namespace std;

class Application
{
private:
	sf::RenderWindow mWindow;

	int mMax;
	vector<sf::RectangleShape> mColumns[2];
	SortingAlogrithms mAlgorithms[2];
	thread mSortingThreads[2];

	pair<int, int> mLastComparison[2];
	bool mFirstComparison[2];

	static const sf::Time TimePerFrame;

public:
	Application();

	void run();

private:
	void draw();
	void onSwap(int index, int a, int b);
	void onComparison(int index, int a, int b);
};