#pragma once
#include <SFML/Graphics.hpp>
#include "Visualizer.h"

class Application
{
private:
	sf::RenderWindow mWindow;

	int mMax;
	const int mMaxColumns;
	int mColumns;
	int mRows;
	const double mBorder;
	sf::Vector2f mViewportSize;
	sf::Vector2f mViewSize;
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