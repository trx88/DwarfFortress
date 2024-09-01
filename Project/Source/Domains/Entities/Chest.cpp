#include "Chest.h"

Chest::Chest(int id, EntityType type, int row, int column, std::vector<std::shared_ptr<class Item>> contents)
	: Entity(id, type, row, column)
{
	this->contents = contents;
}

Chest::~Chest()
{
}

std::vector<std::shared_ptr<class Item>> Chest::GetChestContents()
{
	return contents;
}
