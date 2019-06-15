#include "Visualizer.h"

const sf::Time Visualizer::TimePerFrame = sf::seconds(1.0f / 60.0f);

Visualizer::Visualizer(SortingAlogrithms instance, void(SortingAlogrithms::*func)(), vector<int> randomNumbers, sf::RenderWindow& window) : mWindow(window), mAlgorithm(instance)
{
	mFirstComparison = false;

	float columnWidth = mWindow.getView().getSize().x / randomNumbers.size();

	for (int randomNumber : randomNumbers)
	{
		float columnHeight = mWindow.getView().getSize().y / 9 * randomNumber;
		mColumns.push_back(createColumn(columnWidth, columnHeight));
	}

	mAlgorithm.initialize(randomNumbers, 200);
	mAlgorithm.mSwap.connect(this, &Visualizer::onSwap);
	mAlgorithm.mComparison.connect(this, &Visualizer::onComparison);

	mSortingThread = thread(func, mAlgorithm);
}

Visualizer::~Visualizer()
{
	mSortingThread.join();
}

void Visualizer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto column : mColumns)
		target.draw(column, states);
}

void Visualizer::onSwap(int a, int b)
{
	sf::RectangleShape& aRect = mColumns[a];
	sf::RectangleShape& bRect = mColumns[b];

	sf::Vector2f aPosition = aRect.getPosition();
	sf::Vector2f bPosition = bRect.getPosition();

	aRect.setPosition(bPosition.x, aPosition.y);
	bRect.setPosition(aPosition.x, bPosition.y);

	std::swap(mColumns[a], mColumns[b]);

	mLastComparison.first = mLastComparison.first == a ? b : mLastComparison.first == b ? a : mLastComparison.first;
	mLastComparison.second = mLastComparison.second == b ? a : mLastComparison.second == a ? b : mLastComparison.second;
}

void Visualizer::onComparison(int a, int b)
{
	if (!mFirstComparison)
	{
		mColumns[mLastComparison.first].setFillColor(sf::Color(150, 50, 50));
		mColumns[mLastComparison.second].setFillColor(sf::Color(150, 50, 50));
	}
	else
	{
		mFirstComparison = false;
	}
	mColumns[a].setFillColor(sf::Color(120, 100, 20));
	mColumns[b].setFillColor(sf::Color(120, 100, 20));
	mLastComparison.first = a;
	mLastComparison.second = b;
}

sf::RectangleShape Visualizer::createColumn(float width, float height)
{
	sf::RectangleShape column(sf::Vector2f(width, height));
	column.setPosition(width * mColumns.size(), mWindow.getView().getSize().y - height);
	column.setFillColor(sf::Color(150, 50, 50));
	column.setOutlineColor(sf::Color(0, 0, 0));
	column.setOutlineThickness(2.0f);

	return column;
}
