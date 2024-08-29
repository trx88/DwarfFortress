#include "Entity.h"

Entity::Entity() : id(-1), type(-1), row(-1), column(-1)
{
}

Entity::Entity(int id, int type, int row, int column)
{
	this->id = id;
	this->type = type;
	this->row = row;
	this->column = column;
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

int Entity::GetType() const
{
	return type;
}

char Entity::GetTileSymbol() const
{
	switch (type)
	{
		case static_cast<int>(EntityType::Player):
		{
			return 'P';
		}break;
		case static_cast<int>(EntityType::Enemy):
		{
			return 'E';
		}break;
		case static_cast<int>(EntityType::Mountain):
		{
			return 'M';
		}break;
		case static_cast<int>(EntityType::Tree):
		{
			return 'T';
		}break;
		case static_cast<int>(EntityType::Chest):
		{
			return 'C';
		}break;
		case static_cast<int>(EntityType::Item):
		{
			return 'I';//PROBABLY NOT NEEDED
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
