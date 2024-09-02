#include "Chest.h"
#include "../../Domains/Inventory/Item.h"

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

nlohmann::json Chest::ChestToJSON()
{
	nlohmann::json jsonData;

	nlohmann::json jsonChestObject = nlohmann::json::object();
	jsonChestObject["type"] = static_cast<int>(GetType());
	jsonChestObject["column"] = static_cast<int>(GetColumn());
	jsonChestObject["row"] = static_cast<int>(GetRow());

	nlohmann::json jsonContentsObject = nlohmann::json::array();
	for (const auto& item : contents)
	{
		nlohmann::json jsonItemObject = nlohmann::json::object();
		jsonItemObject["name"] = item->GetName();
		jsonItemObject["type"] = static_cast<int>(item->GetType());
		jsonItemObject["modifier"] = item->GetModifier();
		jsonItemObject["stacks"] = item->GetStacks();

		jsonContentsObject.push_back(jsonItemObject);
	}

	jsonChestObject["contents"] = jsonContentsObject;

	return jsonChestObject;
}
