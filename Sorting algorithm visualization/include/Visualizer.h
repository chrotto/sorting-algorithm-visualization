#pragma once
#include <vector>
#include <list>
#include <thread>
#include <SFML/Graphics.hpp>
#include "SortingAlgorithm.h"
using namespace std;

class Visualizer : public sf::Drawable
{
public:
	typedef unique_ptr<Visualizer> Ptr;
private:
	sf::RenderWindow& mWindow;
	sf::RectangleShape mBackground;

	vector<sf::RectangleShape> mColumns;
	SortingAlgorithm::Ptr mAlgorithm;
	thread mSortingThread;

	pair<int, int> mLastComparison;
	bool mFirstComparison;
	int mLastPivotIndex;

	list<pair<int, int>> mGroups;

	sf::Font mFont;
	sf::Text mAlgorithmName;
	float mTitleHeight;

	static const sf::Time TimePerFrame;

public:
	Visualizer(SortingAlgorithm::Ptr instance, vector<int> randomNumbers, sf::RenderWindow& window);
	~Visualizer();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void onSwap(int a, int b);
	void onComparison(int a, int b);
	void onValueUpdate(int index, int value);
	void onGroupMark(int start, int end);
	void onPivotUpdate(int index);

	sf::RectangleShape createColumn(float width, float height, int columnPosition);
};