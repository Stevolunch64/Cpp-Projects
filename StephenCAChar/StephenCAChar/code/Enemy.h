#ifndef ENEMY_H
#define ENEMY_H
#include "GameCharacter.h"

class Enemy : public GameCharacter //Enemy class is a subclass to GameCharacter
{
public:
	Enemy(std::string typeID, int health, int speed, int x, int y, char symbol);
	virtual void update(); //Function to change the enemy's position
	virtual void setHealth(); //Function to randomly generate a health value
	virtual void setSpeed(); //Function to generate a random speed value
};
#endif
#pragma once
