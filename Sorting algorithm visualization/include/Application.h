#pragma once
#include <SFML/Graphics.hpp>
#include "Visualizer.h"

class Application
{
private:
	struct Grid
	{
		int columns;
		int rows;
		float columnSize;
		float rowSize;
		float border;
	};

private:
	sf::RenderWindow mWindow;

	int mDelay;
	int mArraySize;

	vector<Visualizer::Ptr> mVisualizers;
	vector<int> mRandomNumbers;

	Grid mGrid;

	static const sf::Time TimePerFrame;

public:
	Application();
	~Application();

	void run();

private:
	void render();
	void registerVisualizers();
	void initializeRandomNumbers();

	void showConfigurationWindow();
};