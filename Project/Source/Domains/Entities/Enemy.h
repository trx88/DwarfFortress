#pragma once
#include "Entity.h"
#include "../Inventory/Inventory.h"
#include <vector>
#include <nlohmann/json.hpp>

class Enemy : public Entity
{
private:
	std::unique_ptr<Inventory> inventory;
public:
	Enemy(int id, EntityType type, int row, int column, int health, int armor, int damage);
	~Enemy();
	Inventory* AccessInventory() { return inventory.get(); }
	std::vector<std::shared_ptr<Item>> DropItems();

	nlohmann::json EnemyToJSON();
};

