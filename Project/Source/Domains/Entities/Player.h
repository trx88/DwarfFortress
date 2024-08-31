#pragma once
#include "Entity.h"
#include "../../DataModels/EntityStatsDataModel.h"
#include <boost/signals2/signal.hpp>

class Player : public Entity
{
public:
	Player(int id, int type, int row, int column, int health, int armor, int damage);
	~Player();
	void UpdateHealth(int newHealth);
	void UpdateArmor(int newArmor);
	void UpdateDamage(int newDamage);

	boost::signals2::signal<void(EntityStatsDataModel* entityStatsDataModel)> onPlayerStatsUpdated;
	void SignalPlayerStatsUpdate();
};

