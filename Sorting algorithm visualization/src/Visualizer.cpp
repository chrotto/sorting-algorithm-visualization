#include "Visualizer.h"

const sf::Color Visualizer::COLUMN_IDLE_COLOR = sf::Color(150, 50, 50);
const sf::Color Visualizer::COMPARE_COLOR = sf::Color(120, 100, 20);
const sf::Color Visualizer::PIVOT_COLOR = sf::Color(250, 35, 225);

Visualizer::Visualizer(SortingAlgorithm::Ptr instance, vector<int> randomNumbers, const sf::Vector2f viewSize)
	: mViewSize(viewSize),
	mBackground(viewSize),
	mAlgorithm(move(instance)),
	mLastComparison(nullptr, nullptr),
	mPivotColumn(nullptr)
{
	mBackground.setFillColor(sf::Color::Black);

	mFont.loadFromFile("assets/OpenSans-SemiBold.ttf");
	mAlgorithmName.setFont(mFont);
	mAlgorithmName.setString(mAlgorithm->getName());
	mAlgorithmName.setCharacterSize(mViewSize.y / 15);
	const sf::FloatRect textBounds = mAlgorithmName.getLocalBounds();
	mAlgorithmName.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	mAlgorithmName.setPosition(mViewSize.x / 2.0f, (mAlgorithmName.getCharacterSize() + textBounds.top) / 2.0f);

	float columnWidth = mViewSize.x / randomNumbers.size();

	for (int randomNumber : randomNumbers)
	{
		float columnHeight = (mViewSize.y - mAlgorithmName.getCharacterSize()) / 10 * randomNumber;
		mColumns.push_back(unique_ptr<sf::RectangleShape>(createColumn(columnWidth, columnHeight, mColumns.size())));
	}

	mAlgorithm->mSwap.connect(this, &Visualizer::onSwap);
	mAlgorithm->mComparison.connect(this, &Visualizer::onComparison);
	mAlgorithm->mValueUpdate.connect(this, &Visualizer::onValueUpdate);
	mAlgorithm->mPivotUpdate.connect(this, &Visualizer::onPivotUpdate);

	mSortingThread = thread(&SortingAlgorithm::runSort, move(mAlgorithm));
}

Visualizer::~Visualizer()
{
	mSortingThread.join();
}

void Visualizer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mBackground);
	for (auto& column : mColumns)
		target.draw(*column, states);
	target.draw(mAlgorithmName);
}

void Visualizer::onSwap(int a, int b)
{
	sf::RectangleShape& colA = *mColumns[a];
	sf::RectangleShape& colB = *mColumns[b];

	sf::Vector2f aPosition = colA.getPosition();
	sf::Vector2f bPosition = colB.getPosition();

	colA.setPosition(bPosition.x, aPosition.y);
	colB.setPosition(aPosition.x, bPosition.y);

	std::swap(mColumns[a], mColumns[b]);
}

void Visualizer::onComparison(int a, int b)
{
	if (mLastComparison.first != nullptr)
	{
		mLastComparison.first->setFillColor(COLUMN_IDLE_COLOR);
		mLastComparison.second->setFillColor(COLUMN_IDLE_COLOR);
	}
	mLastComparison.first = &*mColumns[a];
	mLastComparison.second = &*mColumns[b];
	mColumns[a]->setFillColor(COMPARE_COLOR);
	mColumns[b]->setFillColor(COMPARE_COLOR);

	if (mPivotColumn)
		mPivotColumn->setFillColor(PIVOT_COLOR);
}

void Visualizer::onValueUpdate(int index, int value)
{
	sf::RectangleShape& column = *mColumns[index];
	const float height = (mViewSize.y - mAlgorithmName.getCharacterSize()) / 10 * value;
	column.setSize({ column.getSize().x, height });
	column.setPosition(column.getPosition().x, mViewSize.y - height);
}

void Visualizer::onPivotUpdate(int index)
{
	if (mPivotColumn)
		mPivotColumn->setFillColor(COLUMN_IDLE_COLOR);
	mPivotColumn = &*mColumns[index];
	mPivotColumn->setFillColor(PIVOT_COLOR);
}

sf::RectangleShape* Visualizer::createColumn(float width, float height, int index)
{
	sf::RectangleShape* column = new sf::RectangleShape({ width, height });
	column->setPosition(width * index, mViewSize.y - height);
	column->setFillColor(COLUMN_IDLE_COLOR);
	column->setOutlineColor(sf::Color(0, 0, 0));
	column->setOutlineThickness(-8.0f);

	return column;
}
