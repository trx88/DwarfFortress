#pragma once
#include "Entity.h"
#include <nlohmann/json.hpp>

class Enemy : public Entity
{
public:
	Enemy(int id, EntityType type, int row, int column, int health, int armor, int damage);
	~Enemy();
	nlohmann::json EnemyToJSON();
};

