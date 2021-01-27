#include "Application.h"
#include <random>
#include <time.h>
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "GnomeSort.h"
#include <ImGui/imgui.h>
#include <ImGui-SFML/imgui-SFML.h>

const sf::Time Application::TimePerFrame = sf::seconds(1.0f / 60.0f);

Application::Application()
	: mWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Sorting Algorithms Visualization"),
	mDelay(10),
	mArraySize(10),
	mArrayStructure(ArrayStructure::Unsorted),
	mRandomNumbers(mArraySize)
{
	ImGui::SFML::Init(mWindow);

	float screenWidth = static_cast<float>(mWindow.getSize().x);

	mGrid.columns = 4;
	mGrid.rows = 3;
	mGrid.border = 8.0f;
	mGrid.columnSize = (screenWidth - mGrid.border * (mGrid.columns + 1)) / (4 * screenWidth);
	mGrid.rowSize = mGrid.columnSize;
}

Application::~Application()
{
	ImGui::SFML::Shutdown();
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
				ImGui::SFML::ProcessEvent(event);
				if (event.type == sf::Event::Closed)
					mWindow.close();
			}
		}

		ImGui::SFML::Update(mWindow, TimePerFrame);
		showConfigurationWindow();

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

	ImGui::SFML::Render(mWindow);

	mWindow.display();
}

void Application::registerVisualizers()
{
	const sf::Vector2f viewSize = mWindow.getView().getSize();
	mVisualizers.push_back(Visualizer::Ptr(new Visualizer(SortingAlgorithm::Ptr(new BubbleSort(mRandomNumbers, mDelay)), mRandomNumbers, viewSize)));
	mVisualizers.push_back(Visualizer::Ptr(new Visualizer(SortingAlgorithm::Ptr(new SelectionSort(mRandomNumbers, mDelay)), mRandomNumbers, viewSize)));
	mVisualizers.push_back(Visualizer::Ptr(new Visualizer(SortingAlgorithm::Ptr(new InsertionSort(mRandomNumbers, mDelay)), mRandomNumbers, viewSize)));
	mVisualizers.push_back(Visualizer::Ptr(new Visualizer(SortingAlgorithm::Ptr(new MergeSort(mRandomNumbers, mDelay)), mRandomNumbers, viewSize)));
	mVisualizers.push_back(Visualizer::Ptr(new Visualizer(SortingAlgorithm::Ptr(new QuickSort(mRandomNumbers, mDelay)), mRandomNumbers, viewSize)));
	mVisualizers.push_back(Visualizer::Ptr(new Visualizer(SortingAlgorithm::Ptr(new GnomeSort(mRandomNumbers, mDelay)), mRandomNumbers, viewSize)));
}

void Application::initializeRandomNumbers()
{
	srand(time(nullptr));
	for (int& num : mRandomNumbers)
		num = rand() % 10 + 1;

	if (mArrayStructure == ArrayStructure::Sorted)
		sort(mRandomNumbers.begin(), mRandomNumbers.end());
	else if (mArrayStructure == ArrayStructure::InverseSorted)
		sort(mRandomNumbers.begin(), mRandomNumbers.end(), [](const int& a, const int& b) {return a > b; });
}

void Application::showConfigurationWindow()
{
	ImGui::Begin("Configuration");
	ImGui::SliderInt("Delay", &mDelay, 10, 5000, "%d ms");
	if (ImGui::SliderInt("Array size", &mArraySize, 10, 100))
		mRandomNumbers.resize(mArraySize);

	ImGui::Text("Array structure");
	if (ImGui::RadioButton("Unsorted", mArrayStructure == ArrayStructure::Unsorted))
		mArrayStructure = ArrayStructure::Unsorted;
	ImGui::SameLine();
	if (ImGui::RadioButton("Sorted", mArrayStructure == ArrayStructure::Sorted))
		mArrayStructure = ArrayStructure::Sorted;
	ImGui::SameLine();
	if (ImGui::RadioButton("Inverse sorted", mArrayStructure == ArrayStructure::InverseSorted))
		mArrayStructure = ArrayStructure::InverseSorted;

	if (ImGui::Button("Start"))
	{
		if (!mVisualizers.empty())
			mVisualizers.clear();
		initializeRandomNumbers();
		registerVisualizers();
	}
	ImGui::SameLine();
	if (ImGui::Button("Stop"))
	{
		mVisualizers.clear();
	}
	ImGui::End();
}
