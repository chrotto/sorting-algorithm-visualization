#include "Application.h"
#include <random>
#include <time.h>
#include "BubbleSort.h"
#include "SelectionSort.h"

const sf::Time Application::TimePerFrame = sf::seconds(1.0f / 60.0f);

Application::Application() : mWindow(sf::VideoMode(1920, 1080), "Sorting Algorithms Visualization"), mMax(20), mMaxColumns(5), mBorder(0.01)
{
	initializeRandomNumbers();
	registerVisualizers();

	mColumns = ceil((double)mVisualizers.size() / 2);
	mColumns = mColumns > mMaxColumns ? mMaxColumns : mColumns;
	mRows = ceil((double)mVisualizers.size() / mColumns);

	mWidth = 1.0f / mColumns - 2 * mBorder;
	mHeight = 1.0f / mRows - 2 * mBorder;
}

void Application::run()
{
	sf::Event event;
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate >= TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			while (mWindow.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					mWindow.close();
			}
		}
		render();
	}
}

void Application::render()
{
	mWindow.clear();
	int row = 0;
	int column = 0;
	sf::View view = mWindow.getView();
	for (auto& visualizer : mVisualizers)
	{
		if (column >= mColumns)
		{
			column = 0;
			++row;
		}
		double left = (mWidth * column + mBorder * column * 2) + mBorder;
		double top = (mHeight * row + mBorder * row * 2) + mBorder;
		++column;

		view.setViewport(sf::FloatRect(left, top, mWidth, mHeight));
		mWindow.setView(view);
		mWindow.draw(*visualizer);
	}
	mWindow.display();
}

void Application::registerVisualizers()
{
	mVisualizers.push_back(Visualizer::Ptr(new Visualizer(SortingAlgorithm::Ptr(new BubbleSort(mRandomNumbers, 50)), mRandomNumbers, mWindow)));
	mVisualizers.push_back(Visualizer::Ptr(new Visualizer(SortingAlgorithm::Ptr(new SelectionSort(mRandomNumbers, 50)), mRandomNumbers, mWindow)));
}

void Application::initializeRandomNumbers()
{
	srand(time(nullptr));
	for (int i = 0; i < mMax; i++)
		mRandomNumbers.push_back(rand() % 9 + 1);
}
