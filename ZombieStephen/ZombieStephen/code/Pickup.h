#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Pickup
{
private:
	//Start value for health pickups
	const int HEALTH_START_VALUE = 50;
	const int AMMO_START_VALUE = 12;
	
	//Pickups now spawn more frequently and stay on screen for longer
	const int START_WAIT_TIME = 10;
	const int START_SECONDS_TO_LIVE = 10;

	// The sprite that represents this pickup
	Sprite m_Sprite;

	// The arena it exists in
	IntRect m_Arena;

	// How much is this pickup worth?
	int m_Value;

	// What type of pickup is this? 
	// 1 = health, 2 = ammo, 3 = healthKiller , 4 = fire rate increase
	// healthKiller powerup completley drains the player's health, so if they take one it it's GAME OVER
	//Fire Rate increase powerup dramatically increases the fire rate, so the player has an automatic gun
	int m_Type;

	// Handle spawning and disappearing
	bool m_Spawned;
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDeSpawn;
	float m_SecondsToLive;
	float m_SecondsToWait;

	// Public prototypes go here
public:

	Pickup(int type);

	// Prepare a new pickup
	void setArena(IntRect arena);

	void spawn();

	// Check the position of a pickup
	FloatRect getPosition();

	// Get the sprite for drawing
	Sprite getSprite();

	// Let the pickup update itself each frame
	void update(float elapsedTime);

	// Is this pickup currently spawned?
	bool isSpawned();

	// Get the goodness from the pickup
	int gotIt();

	// Upgrade the value of each pickup
	void upgrade();

	//Function to despawn the pickup at the end of a round
	void despawn();

};



