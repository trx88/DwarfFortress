#include "Player.h"

Player::Player(int id, int type, int row, int column, int health, int armor, int damage) 
	: Entity(id, type, row, column, health, armor, damage)
{
	
}

Player::~Player()
{
}
