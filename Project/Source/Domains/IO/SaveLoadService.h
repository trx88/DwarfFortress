#pragma once
#include <memory>

class SaveLoadService
{
public:
	SaveLoadService();
	~SaveLoadService();
	bool SaveToJSON(std::shared_ptr<class World> world, std::shared_ptr<class Player> player);
	[[deprecated("Not used, since there's LoadGame from Game can be used for this.")]]
	bool LoadFromJSON(std::shared_ptr<class World> world, std::shared_ptr<class Player> player);
};

