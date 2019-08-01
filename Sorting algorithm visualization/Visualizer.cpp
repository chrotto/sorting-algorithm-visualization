#include "Visualizer.h"

const sf::Time Visualizer::TimePerFrame = sf::seconds(1.0f / 60.0f);

Visualizer::Visualizer(SortingAlgorithm::Ptr instance, vector<int> randomNumbers, sf::RenderWindow& window)
	: mWindow(window),
	mBackground(window.getView().getSize()),
	mAlgorithm(move(instance)),
	mFirstComparison(false),
	mTitleHeight(30.0f)
{
	mBackground.setFillColor(sf::Color::Black);

	mFont.loadFromFile("Sansation.ttf");
	mAlgorithmName.setFont(mFont);
	mAlgorithmName.setString(mAlgorithm->getName());
	mAlgorithmName.setCharacterSize(20);
	mAlgorithmName.setOrigin(mAlgorithmName.getLocalBounds().width / 2.0f, mAlgorithmName.getLocalBounds().height / 2.0f);
	mAlgorithmName.setPosition(mWindow.getView().getSize().x / 2.0f, mAlgorithmName.getLocalBounds().height / 2.0f);

	float columnWidth = mWindow.getView().getSize().x / randomNumbers.size();

	for (int randomNumber : randomNumbers)
	{
		float columnHeight = (mWindow.getView().getSize().y - mTitleHeight) / 9 * randomNumber;
		mColumns.push_back(createColumn(columnWidth, columnHeight, mColumns.size()));
	}

	mAlgorithm->mSwap.connect(this, &Visualizer::onSwap);
	mAlgorithm->mComparison.connect(this, &Visualizer::onComparison);
	mAlgorithm->mValueUpdate.connect(this, &Visualizer::onValueUpdate);
	mAlgorithm->mMarkGroup.connect(this, &Visualizer::onGroupMark);

	mSortingThread = thread(&SortingAlgorithm::runSort, std::move(mAlgorithm));
}

Visualizer::~Visualizer()
{
	mSortingThread.join();
}

void Visualizer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mBackground);
	for (auto column : mColumns)
		target.draw(column, states);

	target.draw(mAlgorithmName, states);
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

void Visualizer::onValueUpdate(int index, int value)
{
	mColumns[index] = createColumn(mColumns[index].getSize().x, (mWindow.getView().getSize().y - mTitleHeight) / 9 * value, index);
	for (auto group : mGroups)
		if (group.first <= index && index <= group.second)
			mColumns[index].setFillColor(sf::Color(100 + group.first * 20, 150 + group.first, 100 + group.first * 20));
}

void Visualizer::onGroupMark(int start, int end)
{
	sf::Color mGroupColor = sf::Color(100 + start * 20, 150 + start, 100 + start * 20);
	mGroups.remove_if([start, end](const pair<int, int> group) { return group.first == start || group.second == end; });
	mGroups.push_back(pair<int, int>(start, end));

	for (int i = start; i <= end; i++)
		mColumns[i].setFillColor(mGroupColor);
}

sf::RectangleShape Visualizer::createColumn(float width, float height, int columnPosition)
{
	sf::RectangleShape column(sf::Vector2f(width, height));
	column.setPosition(width * columnPosition, mWindow.getView().getSize().y - height);
	column.setFillColor(sf::Color(150, 50, 50));
	column.setOutlineColor(sf::Color(0, 0, 0));
	column.setOutlineThickness(2.0f);

	return column;
}
