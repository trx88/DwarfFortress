#pragma once
class EntityStatsDataModel
{
private:
	int healthPoints;
	int armorPoints;
	int damage;
public:
	EntityStatsDataModel();
	EntityStatsDataModel(int healthPoints, int armorPoints, int damage);
	~EntityStatsDataModel();
#pragma region Getters
	int GetHealthPoints() const;
	int GetArmorPoints() const;
	int GetDamage() const;
#pragma endregion
#pragma region Setters
	void SetHealthPoints(int newHealth);
	void SetArmorPoints(int newArmor);
	void SetDamage(int newDamage);
#pragma endregion
};
