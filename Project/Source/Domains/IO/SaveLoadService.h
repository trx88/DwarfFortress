#pragma once
#include <memory>
class SaveLoadService
{
public:
	SaveLoadService();
	~SaveLoadService();
	bool SaveToJSON(std::shared_ptr<class World> world, std::shared_ptr<class Player> player);
	bool LoadFromJSON(std::shared_ptr<class World> world, std::shared_ptr<class Player> player);
};

