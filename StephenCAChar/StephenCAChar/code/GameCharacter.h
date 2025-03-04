#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H
//Abstract GameCharacter


#include <iostream>
#include <string>
using namespace std;

class GameCharacter  //abstract class
{
protected:
	std::string m_typeID; //Charcater type identifier
	int m_health; // health is a random value
	int m_speed; // speed is a random value
	int m_x; //character's x position
	int m_y; //character's y position
	
	char m_symbol;//Character's symbol (used when the board is displayed)

public:
	void spawn(std::string typeID, int health, int speed, int x, int y, char symbol); // function called when a character is created
	void render(); // print to the screen the typeID and its x and y coords
	virtual void update(); //virtual function to move a character's position
	void stats(); // print all stats relating to the object
	bool isAlive(); //return true if its health is greater than 0
	void killChar(); //Function to set the health value of a character to 0
	
	virtual void setHealth(); //Function to randomly generate a health value at the start of the game
	virtual void setSpeed(); //Function to generate a random speed value

	int getxPos();//Function to return the x positon of a character
	int getyPos();//Function to return the y positon of a character

	int getHealth(); //Function to return health value of a character

	char getSymbol(); //Function to return a character's symbol
	
	std::string getName();//Function to return the name of a character (identifier)

	void changeHealth(int healthDown); //Function to change the value of health during battle

};
#endif
#pragma once
