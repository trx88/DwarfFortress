#include "EntityStatsDataModel.h"

EntityStatsDataModel::EntityStatsDataModel() : healthPoints(0), armorPoints(0), damage(0)
{
}

EntityStatsDataModel::EntityStatsDataModel(int healthPoints, int armorPoints, int damage)
{
	this->healthPoints = healthPoints;
	this->armorPoints = armorPoints;
	this->damage = damage;
}

EntityStatsDataModel::~EntityStatsDataModel()
{
}

int EntityStatsDataModel::GetHealthPoints() const
{
	return healthPoints;
}

int EntityStatsDataModel::GetArmorPoints() const
{
	return armorPoints;
}

int EntityStatsDataModel::GetDamage() const
{
	return damage;
}

void EntityStatsDataModel::SetHealthPoints(int newHealth)
{
	healthPoints = newHealth;
}

void EntityStatsDataModel::SetArmorPoints(int newArmor)
{
	armorPoints = newArmor;
}

void EntityStatsDataModel::SetDamage(int newDamage)
{
	damage = newDamage;
}
