#pragma once
#include <string>

enum class ItemType {
    Potion = 0,
    Weapon = 1,
    Armor = 2
};

class Item
{
private:
    std::string name;
    ItemType type;
    int modifier;
    int stacks;
public:
    Item(const std::string& name, ItemType type, int modifier, int stacks);
    ~Item();
    std::string GetName() const;
    ItemType GetType() const;
    int GetModifier() const;
    int GetStacks() const;
};
