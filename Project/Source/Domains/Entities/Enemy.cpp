#include "Enemy.h"
#include "../../DataModels/EntityStatsDataModel.h"

Enemy::Enemy(int id, EntityType type, int row, int column, int health, int armor, int damage)
	: Entity(id, type, row, column, health, armor, damage)
{
}

Enemy::~Enemy()
{
}

nlohmann::json Enemy::EnemyToJSON()
{
	nlohmann::json jsonData;

	nlohmann::json jsonEnemyObject = nlohmann::json::object();
	jsonEnemyObject["type"] = static_cast<int>(GetType());
	jsonEnemyObject["column"] = static_cast<int>(GetColumn());
	jsonEnemyObject["row"] = static_cast<int>(GetRow());

	nlohmann::json jsonStatsObject = nlohmann::json::object();
	jsonStatsObject["health"] = static_cast<int>(statsData->GetHealthPoints());
	jsonStatsObject["armor"] = static_cast<int>(statsData->GetArmorPoints());
	jsonStatsObject["damage"] = static_cast<int>(statsData->GetDamage());
	jsonEnemyObject["stats"] = jsonStatsObject;

	return jsonEnemyObject;
}
