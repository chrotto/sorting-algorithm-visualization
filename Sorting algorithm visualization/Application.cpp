#include "Application.h"
#include <random>
#include <time.h>

const sf::Time Application::TimePerFrame = sf::seconds(1.0f / 60.0f);

Application::Application() : mWindow(sf::VideoMode(1920, 1080), "Sorting Algorithms Visualization"), mMax(15), mLastComparison(), mFirstComparison(true)
{
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

		mColumns.push_back(rect);
		numbers.push_back(randomNumber);
	}

	mAlgorithms.initialize(numbers, 300);
	mAlgorithms.mSwap.connect(this, &Application::onSwap);
	mAlgorithms.mComparison.connect(this, &Application::onComparison);

	mSortingThread = thread(&SortingAlogrithms::selectionSort, mAlgorithms);
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
					mSortingThread.join();
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
	for (auto col : mColumns)
		mWindow.draw(col);

	mWindow.display();
}

void Application::onSwap(int a, int b)
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

	//std::swap(mLastComparison.first, mLastComparison.second);
}

void Application::onComparison(int a, int b)
{
	if (!mFirstComparison)
	{
		mColumns[mLastComparison.first].setFillColor(sf::Color(50 + 20 * mColumns[mLastComparison.first].getSize().y, 100, 100));
		mColumns[mLastComparison.second].setFillColor(sf::Color(50 + 20 * mColumns[mLastComparison.second].getSize().y, 100, 100));
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
