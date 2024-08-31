#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(int id, int type, int row, int column, int health, int armor, int damage);
	~Enemy();
};

