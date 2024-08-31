#pragma once
#include <memory>

enum class EntityType 
{
    Player = 0,
    Enemy = 1,
	Mountain = 2,
	Tree = 3,
    Chest = 4
};

class Entity
{
private:
	int id;
	int type;
	int row;
	int column;
protected:
	std::unique_ptr<class EntityStatsDataModel> statsData;
public:
	Entity();
	Entity(int id, int type, int row, int column);
	Entity(int id, int type, int row, int column, int health, int armor, int damage);
	virtual ~Entity(); //Should be virtual, since this class will be inherited.
	int GetId() const;
	int GetRow() const;
	int GetColumn() const;
	int GetType() const;
	char GetTileSymbol() const;
	void SetPosition(int newRow, int newColumn);
};

