#pragma once
#include <SFML/Graphics.hpp>
#include "Visualizer.h"
#include "SortingAlgorithms.h"

class Application
{
private:
	sf::RenderWindow mWindow;

	int mMax;
	vector<unique_ptr<Visualizer>> mVisualizers;

	static const sf::Time TimePerFrame;

public:
	Application();

	void run();

private:
	void render();
};

