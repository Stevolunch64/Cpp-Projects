#ifndef GAME_H
#define GAME_H
#include "GameCharacter.h"
#include "Enemy.h"
#include "Player.h"
#include <list>

class Game 
{
public:
	Game();
	//Functions that are found in the GameCharacter class and its subclasses (enemy and player)
	void init();
	void render();
	void update();
	void setSpeed();
	void setHealth();
	int getxPos();
	int getyPos();
	int getHealth();
	std::string getName();
	char getSymbol();
	void stats();
	
	//New functions for this game class
	void battle(); //Function to make a player and enemy battle if they land on the same space
	void clean(); //Function called to remove a character from the pointer list if their health is zero
	void displayBoard(); //Function to display a board as a 2d array with all characters on it
	bool getOver(); //Function to return the value of the isOver boolean (becomes true if the player is killed)
	bool titleMenu(); //Function to display a title screen and menu
	
	
	

private:
	//Player pointer object
	Player* pPlayer; //Player 
	
	//Enemy pointer objects
	Enemy* pEnemy1; //Enemy1
	Enemy* pEnemy2; //Enemy2
	Enemy* pEnemy3; //Enemy3
	Enemy* pEnemy4; //Enemy4

	list<GameCharacter*> lpGameCharacters; //a list of GameCharacter pointers for the player and enemies to go into

	char board[10][10];//Board is a 2d array of chars

	bool isOver = false; //bool that becomes true if the player is killed
	int input; //int that takes in the player's input during battle
	int healthDe; //Int that deducts health during battle
	

};
#endif
#pragma once