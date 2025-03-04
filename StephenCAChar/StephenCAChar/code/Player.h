#ifndef PLAYER_H
#define PLAYER_H
#include "GameCharacter.h"

class Player : public GameCharacter //Player class is a subclass to GameCharacter class
{
public:
	Player(std::string typeID, int health, int speed, int x, int y, char symbol);
	virtual void update();
	virtual void setHealth(); //Function to randomly generate a health value
	virtual void setSpeed(); //Function to generate a random speed value 
};
#endif
#pragma once