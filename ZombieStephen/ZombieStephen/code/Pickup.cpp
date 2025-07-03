#include "Pickup.h"
#include "TextureHolder.h"

Pickup::Pickup(int type)
{
	// Store the type of this pickup
	m_Type = type;

	switch (m_Type)
	{
		case 1://type 1 is the health pickup
			m_Sprite = Sprite(TextureHolder::GetTexture(
				"graphics/health_pickup.png"));

			// How much is pickup worth
			m_Value = HEALTH_START_VALUE;

			//How long the pickup will stay on screen/wait
			m_SecondsToLive = START_WAIT_TIME;
			m_SecondsToWait = START_SECONDS_TO_LIVE;

			break;
		case 2://type 2 is the ammo pickup
			m_Sprite = Sprite(TextureHolder::GetTexture(
				"graphics/ammo_pickup.png"));

			// How much is pickup worth
			m_Value = AMMO_START_VALUE;

			//How long the pickup will stay on screen/wait
			m_SecondsToLive = START_WAIT_TIME;
			m_SecondsToWait = 5;

			break;
		case 3://type 3 is the health killer pickup
			
			m_Sprite = Sprite(TextureHolder::GetTexture(
				"graphics/health_killer.png"));

			//How long the pickup will stay on screen/wait
			//Health killer lasts a long time on screen to act as a nuisance to the player
			m_SecondsToLive = 20;
			m_SecondsToWait = 5;
			
			break;
		case 4://type 4 is the fire rate increase pickup
			
			m_Sprite = Sprite(TextureHolder::GetTexture(
				"graphics/rate_increase.png"));

			//How long the pickup will stay on screen/wait
			m_SecondsToLive = 5;
			m_SecondsToWait = 5;
			
			break;
		case 5://type 5 is the invincible pickup
			m_Sprite = Sprite(TextureHolder::GetTexture(
				"graphics/invincible.png"));

			//How long the pickup will stay on screen/wait
			m_SecondsToLive = 2;
			m_SecondsToWait = 15;
			
			break;
	}

	
	m_Sprite.setOrigin(25, 25);

	
}

void Pickup::setArena(IntRect arena)
{

	// Copy the details of the arena to the pickup's m_Arena
	m_Arena.left = arena.left + 50;
	m_Arena.width = arena.width - 50;
	m_Arena.top = arena.top + 50;
	m_Arena.height = arena.height - 50;

	spawn();
}

void Pickup::spawn()
{
	// Spawn at a random location
	srand((int)time(0) / m_Type);
	int x = (rand() % m_Arena.width);
	srand((int)time(0) * m_Type);
	int y = (rand() % m_Arena.height);

	// Not currently spawned
	//m_Spawned = false;
	m_SecondsSinceSpawn = 0;
	m_Spawned = true;
	
	m_Sprite.setPosition(x, y);
}

FloatRect Pickup::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite Pickup::getSprite()
{
	return m_Sprite;
}

bool Pickup::isSpawned()
{
	return m_Spawned;
}

int Pickup::gotIt()
{
	m_Spawned = false;
	m_SecondsSinceDeSpawn = 0;
	return m_Value;
}

void Pickup::update(float elapsedTime)
{
	if (m_Spawned)
	{
		m_SecondsSinceSpawn += elapsedTime;
	}
	else
	{
		m_SecondsSinceDeSpawn += elapsedTime;
	}


	// Do we need to hide a pickup?
	if (m_SecondsSinceSpawn > m_SecondsToLive && m_Spawned)
	{
		// Revove the pickup and put it somewhere else
		m_Spawned = false;
		m_SecondsSinceDeSpawn = 0;
	}

	// Do we need to spawn a pickup
	if (m_SecondsSinceDeSpawn > m_SecondsToWait && !m_Spawned)
	{
		// spawn the pickup and reset the timer
		spawn();
	}

}

void Pickup::upgrade()//function called to upgrade the pickups after a round (only for health and ammo)
{
	if (m_Type == 1)
	{
		m_Value += (HEALTH_START_VALUE * .5);
	}
	else if(m_Type == 2)
	{
		m_Value += (AMMO_START_VALUE * .5);
	}
	

	// Make them more frequent and last longer
	m_SecondsToLive += (START_SECONDS_TO_LIVE / 10);
	m_SecondsToWait -= (START_WAIT_TIME / 10);
}

//Function to despawn a pickup at the end of a round so pickups are fresh for a new round
void Pickup::despawn() 
{
	m_Spawned = false;
	m_SecondsSinceDeSpawn = 0;
}
