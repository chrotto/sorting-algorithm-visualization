#include "Application.h"
#include <random>
#include <time.h>
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "GnomeSort.h"

const sf::Time Application::TimePerFrame = sf::seconds(1.0f / 60.0f);

Application::Application()
	: mWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Sorting Algorithms Visualization"),
	mArraySize(10),
	mRandomNumbers(mArraySize)
{
	initializeRandomNumbers();
	registerVisualizers();

	float screenWidth = static_cast<float>(mWindow.getSize().x);

	mGrid.columns = 4;
	mGrid.rows = 3;
	mGrid.border = 8.0f;
	mGrid.columnSize = (screenWidth - mGrid.border * (mGrid.columns + 1)) / (4 * screenWidth);
	mGrid.rowSize = mGrid.columnSize;
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
	sf::View view = mWindow.getView();

	float borderRatioX = mGrid.border / static_cast<float>(mWindow.getSize().x);
	float borderRatioY = mGrid.border / static_cast<float>(mWindow.getSize().y);
	float left = 0.0f, top = 0.0f;

	for (int i = 0; i < mVisualizers.size(); i++)
	{
		left = borderRatioX * (i % mGrid.columns + 1) + mGrid.columnSize * (i % mGrid.columns);
		top = borderRatioY * (i / mGrid.columns + 1) + mGrid.rowSize * (i / mGrid.columns);
		view.setViewport(sf::FloatRect(left, top, mGrid.columnSize, mGrid.rowSize));
		mWindow.setView(view);
		mWindow.draw(*mVisualizers[i]);
	}

	mWindow.display();
}

void Application::registerVisualizers()
{
	const sf::Vector2f viewSize = mWindow.getView().getSize();
	const int delay = 50;
	mVisualizers.push_back(Visualizer::Ptr(new Visualizer(SortingAlgorithm::Ptr(new BubbleSort(mRandomNumbers, delay)), mRandomNumbers, viewSize)));
	mVisualizers.push_back(Visualizer::Ptr(new Visualizer(SortingAlgorithm::Ptr(new SelectionSort(mRandomNumbers, delay)), mRandomNumbers, viewSize)));
	mVisualizers.push_back(Visualizer::Ptr(new Visualizer(SortingAlgorithm::Ptr(new InsertionSort(mRandomNumbers, delay)), mRandomNumbers, viewSize)));
	mVisualizers.push_back(Visualizer::Ptr(new Visualizer(SortingAlgorithm::Ptr(new MergeSort(mRandomNumbers, delay)), mRandomNumbers, viewSize)));
	mVisualizers.push_back(Visualizer::Ptr(new Visualizer(SortingAlgorithm::Ptr(new QuickSort(mRandomNumbers, delay)), mRandomNumbers, viewSize)));
	mVisualizers.push_back(Visualizer::Ptr(new Visualizer(SortingAlgorithm::Ptr(new GnomeSort(mRandomNumbers, delay)), mRandomNumbers, viewSize)));
}

void Application::initializeRandomNumbers()
{
	srand(time(nullptr));
	for (int& num : mRandomNumbers)
		num = rand() % 10 + 1;
}
