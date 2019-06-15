#include "Application.h"
#include <random>
#include <time.h>

const sf::Time Application::TimePerFrame = sf::seconds(1.0f / 60.0f);

Application::Application() : mWindow(sf::VideoMode(1920, 1080), "Sorting Algorithms Visualization"), mMax(20)
{
	srand(time(nullptr));
	vector<int> randomNumbers;
	for (int i = 0; i < mMax; i++)
		randomNumbers.push_back(rand() % 9 + 1);

	mVisualizers.push_back(unique_ptr<Visualizer>(new Visualizer(SortingAlogrithms(), &SortingAlogrithms::bubbleSort, randomNumbers, mWindow)));
	mVisualizers.push_back(unique_ptr<Visualizer>(new Visualizer(SortingAlogrithms(), &SortingAlogrithms::selectionSort, randomNumbers, mWindow)));
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

	for (int i = 0; i < 2; i++)
	{
		sf::View view = mWindow.getView();
		view.setViewport(sf::FloatRect(0, 0 + 0.51 * i, 1, 0.49));
		mWindow.setView(view);
		mWindow.draw(*mVisualizers[i]);
	}
	mWindow.display();
}
