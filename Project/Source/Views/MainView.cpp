#include "MainView.h"
#include "MapSubView.h"
#include "StatsSubView.h"
#include <sstream>
#include <iostream>
#include <string>

MainView::MainView(std::shared_ptr<class World> world, std::shared_ptr<class Player> player)
{
	mapSubView = std::make_unique<MapSubView>(1, world);
	statsSubView = std::make_unique<StatsSubView>(2, player);

	mapSubView->onMapSubViewUpdated.connect([this](int id, std::string output) {UpsertOutputBuffer(id, output); });
	statsSubView->onStatsSubViewUpdated.connect([this](int id, std::string output) {UpsertOutputBuffer(id, output); });
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
