#pragma once
#include "Entity.h"
#include <vector>

class Chest : public Entity
{
private:
	std::vector<std::shared_ptr<class Item>> contents;
public:
	Chest(int id, EntityType type, int row, int column, std::vector<std::shared_ptr<class Item>> contents);
	~Chest();
	std::vector<std::shared_ptr<class Item>> GetChestContents();
};

