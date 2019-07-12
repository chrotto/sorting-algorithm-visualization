#include "Application.h"
#include <random>
#include <time.h>
#include "BubbleSort.h"
#include "SelectionSort.h"

const sf::Time Application::TimePerFrame = sf::seconds(1.0f / 60.0f);

Application::Application() : mWindow(sf::VideoMode(1920, 1080), "Sorting Algorithms Visualization"), mMax(20), mMaxColumns(5), mBorder(10.0)
{
	mViewportSize.x = mViewportSize.y = (mWindow.getSize().x - (1.0 + mMaxColumns) * mBorder) / ((double)mMaxColumns * mWindow.getSize().x);
	mViewSize.x = mWindow.getSize().x * mViewportSize.x;
	mViewSize.y = mWindow.getSize().y * mViewportSize.y;

	sf::View view = mWindow.getView();
	view.setSize(mViewSize.x, mViewSize.y);
	view.setCenter(mViewSize.x / 2, mViewSize.y / 2);
	mWindow.setView(view);

	initializeRandomNumbers();
	registerVisualizers();

	mColumns = min((int)mVisualizers.size(), mMaxColumns);
	mRows = ceil((double)mVisualizers.size() / mColumns);
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
	mWindow.clear(sf::Color(100, 100, 100));
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
		double columnBorder = (mBorder / mWindow.getSize().x) * (column + 1.0);
		double rowBorder = (mBorder / mWindow.getSize().y) * (row + 1.0);
		float left = mViewportSize.x * column + columnBorder;
		float top = mViewportSize.y * row + rowBorder;
		++column;

		view.setViewport(sf::FloatRect(left, top, mViewportSize.x, mViewportSize.y));
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
