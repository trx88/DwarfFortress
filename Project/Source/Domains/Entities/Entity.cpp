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

std::string Entity::GetTileSymbolForPrint()
{
	switch (type)
	{
	case EntityType::Player:
	{
		return "\x1B[36mP";
	}break;
	case EntityType::Enemy:
	{
		return "\x1B[31mE";
	}break;
	case EntityType::Mountain:
	{
		return "\x1B[37mM";
	}break;
	case EntityType::Tree:
	{
		return "\x1B[32mT";
	}break;
	case EntityType::Chest:
	{
		return "\x1B[35mC";
	}break;
	default:
	{
		return "\x1B[31m?";
	}break;
	}
}

void Entity::SetPosition(int newRow, int newColumn)
{
	row = newRow;
	column = newColumn;
}

int Entity::GetHealth() const
{
	return statsData->GetHealthPoints();
}

int Entity::GetArmor() const
{
	return statsData->GetArmorPoints();
}

int Entity::GetDamage() const
{
	return statsData->GetDamage();
}

void Entity::UpdateHealth(int newHealth)
{
	statsData->SetHealthPoints(newHealth);
}

void Entity::UpdateArmor(int newArmor)
{
	statsData->SetArmorPoints(newArmor);
}

void Entity::UpdateDamage(int newDamage)
{
	statsData->SetDamage(newDamage);
}

nlohmann::json Entity::EntityToJSON()
{
	nlohmann::json jsonData;

	nlohmann::json jsonEntityObject = nlohmann::json::object();
	jsonEntityObject["type"] = static_cast<int>(GetType());
	jsonEntityObject["column"] = static_cast<int>(GetColumn());
	jsonEntityObject["row"] = static_cast<int>(GetRow());

	return jsonEntityObject;
}
