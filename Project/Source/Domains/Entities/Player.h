#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player(int id, int type, int row, int column, int health, int armor, int damage);
	~Player();
};

