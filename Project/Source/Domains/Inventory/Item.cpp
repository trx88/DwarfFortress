#include "Item.h"

Item::Item(const std::string& name, ItemType type, int modifier, int stacks)
{
	this->name = name;
	this->type = type;
	this->modifier = modifier;
	this->stacks = stacks;
}

Item::~Item()
{
}

std::string Item::GetName() const
{
	return name;
}

ItemType Item::GetType() const
{
	return type;
}

int Item::GetModifier() const
{
	return modifier;
}

int Item::GetStacks() const
{
	return stacks;
}
