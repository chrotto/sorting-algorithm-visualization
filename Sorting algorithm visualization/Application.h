#pragma once
#include <SFML/Graphics.hpp>
#include "Visualizer.h"

class Application
{
private:
	sf::RenderWindow mWindow;

	int mMax;
	int mMaxColumns;
	int mColumns;
	int mRows;
	const double mBorder;
	double mWidth, mHeight;
	vector<Visualizer::Ptr> mVisualizers;
	vector<int> mRandomNumbers;

	static const sf::Time TimePerFrame;

public:
	Application();

	void run();

private:
	void render();
	void registerVisualizers();
	void initializeRandomNumbers();
};