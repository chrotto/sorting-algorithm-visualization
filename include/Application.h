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

	enum class ArrayStructure
	{
		Unsorted,
		Sorted,
		InverseSorted
	};

private:
	sf::RenderWindow mWindow;

	int mDelay;
	int mArraySize;

	ArrayStructure mArrayStructure;

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