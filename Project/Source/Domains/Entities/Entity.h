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
	virtual ~Entity(); //Virtual, since this class will be inherited.

#pragma region Getters
	int GetId() const;
	int GetRow() const;
	int GetColumn() const;
	EntityType GetType() const;
	char GetTileSymbol() const;
	std::string GetTileSymbolForPrint();
	int GetHealth() const;
	int GetArmor() const;
	int GetDamage() const;
#pragma endregion

#pragma region Setters
	void SetPosition(int newRow, int newColumn);
	virtual void UpdateHealth(int newHealth);
	virtual void UpdateArmor(int newArmor);
	virtual void UpdateDamage(int newDamage);
#pragma endregion

	nlohmann::json EntityToJSON();
};

