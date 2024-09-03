#pragma once
#include <memory>
#include <string>
#include <nlohmann/json.hpp>

enum class EntityType 
{
    Player = 0,
    Enemy = 1,
	Mountain = 2,
	Tree = 3,
    Chest = 4,
	Undefined = 5
};

class Entity
{
private:
	int id;
	EntityType type;
	int row;
	int column;
protected:
	std::unique_ptr<class EntityStatsDataModel> statsData;
public:
	Entity();
	Entity(int id, EntityType type, int row, int column);
	Entity(int id, EntityType type, int row, int column, int health, int armor, int damage);
	virtual ~Entity(); //Should be virtual, since this class will be inherited.
	int GetId() const;
	int GetRow() const;
	int GetColumn() const;
	EntityType GetType() const;
	char GetTileSymbol() const;
	std::string GetTileSymbolForPrint();
	void SetPosition(int newRow, int newColumn);
	int GetHealth() const;
	int GetArmor() const;
	int GetDamage() const;
	virtual void UpdateHealth(int newHealth);
	virtual void UpdateArmor(int newArmor);
	virtual void UpdateDamage(int newDamage);

	nlohmann::json EntityToJSON();
};

