#pragma once

enum class EntityType {
    Player = 0,
    Enemy = 1,
	Obstacle = 2,
    Chest = 3,
	Item = 4
};

class Entity
{
private:
	int id;
	int type;
	int row;
	int column;
public:
	Entity();
	Entity(int id, int type, int row, int column);
	virtual ~Entity(); //Should be virtual, since this class will be inherited.
	int GetId() const;
	int GetRow() const;
	int GetColumn() const;
	int GetType() const;
	char GetTileSymbol() const;
	void SetPosition(int newRow, int newColumn);
};

