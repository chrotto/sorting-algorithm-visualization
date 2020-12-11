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
	static const sf::Color COLUMN_IDLE_COLOR;
	static const sf::Color COMPARE_COLOR;
	static const sf::Color PIVOT_COLOR;

	sf::Vector2f mViewSize;
	sf::RectangleShape mBackground;

	vector<unique_ptr<sf::RectangleShape>> mColumns;
	SortingAlgorithm::Ptr mAlgorithm;
	thread mSortingThread;

	pair<sf::RectangleShape*, sf::RectangleShape*> mLastComparison;
	sf::RectangleShape* mPivotColumn;

	sf::Font mFont;
	sf::Text mAlgorithmName;

public:
	Visualizer(SortingAlgorithm::Ptr instance, vector<int> randomNumbers, const sf::Vector2f viewSize);
	~Visualizer();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void onSwap(int a, int b);
	void onComparison(int a, int b);
	void onValueUpdate(int index, int value);
	void onPivotUpdate(int index);

	sf::RectangleShape* createColumn(float width, float height, int index);
};