#include "Entity.h"
#include "../../DataModels/EntityStatsDataModel.h"

Entity::Entity() : id(-1), type(EntityType::Undefined), row(-1), column(-1)
{
	statsData = std::make_unique<EntityStatsDataModel>();
}

Entity::Entity(int id, EntityType type, int row, int column)
{
	this->id = id;
	this->type = type;
	this->row = row;
	this->column = column;
	statsData = std::make_unique<EntityStatsDataModel>();
}

Entity::Entity(int id, EntityType type, int row, int column, int health, int armor, int damage)
{
	this->id = id;
	this->type = type;
	this->row = row;
	this->column = column;
	statsData = std::make_unique<EntityStatsDataModel>(health, armor, damage);
}

Entity::~Entity()
{
}

int Entity::GetId() const
{
	return id;
}

int Entity::GetRow() const
{
	return row;
}

int Entity::GetColumn() const
{
	return column;
}

EntityType Entity::GetType() const
{
	return type;
}

char Entity::GetTileSymbol() const
{
	switch (type)
	{
		case EntityType::Player:
		{
			return 'P';
		}break;
		case EntityType::Enemy:
		{
			return 'E';
		}break;
		case EntityType::Mountain:
		{
			return 'M';
		}break;
		case EntityType::Tree:
		{
			return 'T';
		}break;
		case EntityType::Chest:
		{
			return 'C';
		}break;
		default:
		{
			return '?';
		}break;
	}
}

void Entity::SetPosition(int newRow, int newColumn)
{
	row = newRow;
	column = newColumn;
}
