#pragma once
#include <string>
#include <memory>

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
    bool equipped;
public:
    Item(const std::string& name, ItemType type, int modifier, int stacks, bool equipped = false);
    ~Item();
#pragma region Getters
    std::string GetName() const;
    ItemType GetType() const;
    int GetModifier() const;
    int GetStacks() const;
    bool IsEquipped() const;
#pragma endregion

#pragma region Setters
    void SetStacks(int updatedStack);
    void SetEquipped(bool equipped);
#pragma endregion

    friend bool operator==(const std::shared_ptr<Item>& first, const std::shared_ptr<Item>& second);
};
