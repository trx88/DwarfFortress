#pragma once
#include <memory>
#include <unordered_map>
#include <string>

class MainView
{
private:
	std::unique_ptr<class MapSubView> mapSubView;
	std::unique_ptr<class StatsSubView> statsSubView;
	std::unique_ptr<class InventorySubView> inventorySubView;
	std::unique_ptr<class ActionsSubView> actionsSubView;
	std::unordered_map<int, std::string> cachedOutputBuffers;
public:
	MainView(std::shared_ptr<class World> world, std::shared_ptr<class Player> player);
	~MainView();
	void UpsertOutputBuffer(int id, std::string outputBuffer);
	void RenderSubViews();
	void SetConsoleSize(int consoleWidth, int consoleHeight);
};
