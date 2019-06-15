#pragma once
#include <vector>
#include <thread>
#include <SFML/Graphics.hpp>
#include "SortingAlgorithms.h"
using namespace std;

class Visualizer : public sf::Drawable
{
private:
	sf::RenderWindow& mWindow;

	vector<sf::RectangleShape> mColumns;
	SortingAlogrithms mAlgorithm;
	thread mSortingThread;

	pair<int, int> mLastComparison;
	bool mFirstComparison;

	static const sf::Time TimePerFrame;

public:
	Visualizer(SortingAlogrithms instance, void(SortingAlogrithms::*func)(), vector<int> randomNumbers, sf::RenderWindow& window);
	~Visualizer();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void onSwap(int a, int b);
	void onComparison(int a, int b);

	sf::RectangleShape createColumn(float width, float height);
};