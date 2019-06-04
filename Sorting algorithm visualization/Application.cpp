#include "Application.h"
#include <random>
#include <time.h>

const sf::Time Application::TimePerFrame = sf::seconds(1.0f / 60.0f);

Application::Application() : mWindow(sf::VideoMode(1920, 1080), "Sorting Algorithms Visualization"), mMax(50), mLastComparison()
{
	mFirstComparison[0] = false;
	mFirstComparison[1] = false;

	vector<int> numbers;
	srand(time(nullptr));

	float width = mWindow.getView().getSize().x / mMax;

	for (int i = 0; i < mMax; i++)
	{
		int randomNumber = rand() % 9 + 1;
		float height = mWindow.getView().getSize().y / 9 * randomNumber;

		sf::RectangleShape rect(sf::Vector2f(width, height));
		rect.setPosition(width * i, mWindow.getView().getSize().y - height);
		rect.setFillColor(sf::Color(50 + randomNumber * 20, 100, 100));
		rect.setOutlineColor(sf::Color(0, 0, 0));
		rect.setOutlineThickness(3.0f);

		mColumns[0].push_back(rect);
		mColumns[1].push_back(rect);
		numbers.push_back(randomNumber);
	}

	mAlgorithms[0].initialize(numbers, 100);
	mAlgorithms[0].mSwap.connect([this](int a, int b) {onSwap(0, a, b); });
	mAlgorithms[0].mComparison.connect([this](int a, int b) {onComparison(0, a, b); });

	mAlgorithms[1].initialize(numbers, 100);
	mAlgorithms[1].mSwap.connect([this](int a, int b) {onSwap(1, a, b); });
	mAlgorithms[1].mComparison.connect([this](int a, int b) {onComparison(1, a, b); });

	mSortingThreads[0] = thread(&SortingAlogrithms::bubbleSort, mAlgorithms[0]);
	mSortingThreads[1] = thread(&SortingAlogrithms::selectionSort, mAlgorithms[1]);
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
				{
					mSortingThreads[0].join();
					mSortingThreads[1].join();
					mWindow.close();
				}
			};
		}
		draw();
	}
}

void Application::draw()
{
	mWindow.clear();

	for (int i = 0; i < 2; i++)
	{
		sf::View view(mWindow.getDefaultView());
		view.setViewport(sf::FloatRect(0, 0 + i * 0.51, 1, 0.49));
		mWindow.setView(view);
		for (auto col : mColumns[i])
			mWindow.draw(col);
	}

	mWindow.display();
}

void Application::onSwap(int index, int a, int b)
{
	sf::RectangleShape& aRect = mColumns[index][a];
	sf::RectangleShape& bRect = mColumns[index][b];

	sf::Vector2f aPosition = aRect.getPosition();
	sf::Vector2f bPosition = bRect.getPosition();

	aRect.setPosition(bPosition.x, aPosition.y);
	bRect.setPosition(aPosition.x, bPosition.y);

	std::swap(mColumns[index][a], mColumns[index][b]);

	mLastComparison[index].first = mLastComparison[index].first == a ? b : mLastComparison[index].first == b ? a : mLastComparison[index].first;
	mLastComparison[index].second = mLastComparison[index].second == b ? a : mLastComparison[index].second == a ? b : mLastComparison[index].second;
}

void Application::onComparison(int index, int a, int b)
{
	if (!mFirstComparison[index])
	{
		mColumns[index][mLastComparison[index].first].setFillColor(sf::Color(50 + 20 * mColumns[index][mLastComparison[index].first].getSize().y, 100, 100));
		mColumns[index][mLastComparison[index].second].setFillColor(sf::Color(50 + 20 * mColumns[index][mLastComparison[index].second].getSize().y, 100, 100));
	}
	else
	{
		mFirstComparison[index] = false;
	}
	mColumns[index][a].setFillColor(sf::Color(120, 100, 20));
	mColumns[index][b].setFillColor(sf::Color(120, 100, 20));
	mLastComparison[index].first = a;
	mLastComparison[index].second = b;
}
