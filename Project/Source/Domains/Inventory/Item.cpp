#include "Item.h"

Item::Item(const std::string& name, ItemType type, int modifier, int stacks, bool equipped)
{
	this->name = name;
	this->type = type;
	this->modifier = modifier;
	this->stacks = stacks;
	this->equipped = equipped;
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

bool Item::IsEquipped() const
{
	return equipped;
}

void Item::SetStacks(int updatedStack)
{
	this->stacks = updatedStack;
}

void Item::SetEquipped(bool equipped)
{
	this->equipped = equipped;
}

bool operator==(const std::shared_ptr<Item>& first, const std::shared_ptr<Item>& second)
{
	return 
		first->GetName().compare(second->GetName()) == 0 &&
		first->GetType() == second->GetType() &&
		first->GetModifier() == second->GetModifier();
}
