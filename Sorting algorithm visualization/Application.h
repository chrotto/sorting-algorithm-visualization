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
	vector<sf::RectangleShape> mColumns;
	SortingAlogrithms mAlgorithms;
	thread mSortingThread;

	pair<int, int> mLastComparison;
	bool mFirstComparison;

	static const sf::Time TimePerFrame;

public:
	Application();

	void run();

private:
	void draw();
	void onSwap(int a, int b);
	void onComparison(int a, int b);
};