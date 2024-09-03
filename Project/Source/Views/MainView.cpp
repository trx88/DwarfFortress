#include "MainView.h"
#include "MapSubView.h"
#include "StatsSubView.h"
#include "InventorySubView.h"
#include "ActionsSubView.h"
#include <sstream>
#include <iostream>
#include <string>
#include <windows.h>

MainView::MainView(std::shared_ptr<class World> world, std::shared_ptr<class Player> player)
{
	mapSubView = std::make_unique<MapSubView>(1, world);
	statsSubView = std::make_unique<StatsSubView>(2, player);
	inventorySubView = std::make_unique<InventorySubView>(3, player);
	actionsSubView = std::make_unique<ActionsSubView>(4, player);

	mapSubView->onMapSubViewUpdated.connect([this](int id, std::string output) {UpsertOutputBuffer(id, output); });
	statsSubView->onStatsSubViewUpdated.connect([this](int id, std::string output) {UpsertOutputBuffer(id, output); });
	inventorySubView->onInventorySubViewUpdated.connect([this](int id, std::string output) {UpsertOutputBuffer(id, output); });
	actionsSubView->onActionsSubViewUpdated.connect([this](int id, std::string output) {UpsertOutputBuffer(id, output); });

	SetConsoleSize(120, 120);
}

MainView::~MainView()
{
}

void MainView::UpsertOutputBuffer(int id, std::string outputBuffer)
{
	cachedOutputBuffers.insert_or_assign(id, outputBuffer);
	RenderSubViews();
}

void MainView::RenderSubViews()
{
	std::stringstream output;

	for (const auto& outputBuffer : cachedOutputBuffers)
	{
		output << outputBuffer.second;
	}

	std::cout << output.str();
}

void MainView::SetConsoleSize(int consoleWidth, int consoleHeight)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD bufferSize;
	bufferSize.X = consoleWidth;
	bufferSize.Y = consoleHeight;
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	SMALL_RECT windowSize;
	windowSize.Left = 0;
	windowSize.Top = 0;
	windowSize.Right = consoleWidth - 1;
	windowSize.Bottom = consoleHeight - 1;
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}
