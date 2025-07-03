#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ZombieArena.h"
#include "Player.h"
#include "TextureHolder.h"
#include "Bullet.h"
#include "Pickup.h"
#include <iostream>

using namespace std;

int main()
{
	// Here is the instabce of TextureHolder
	TextureHolder holder;

	// The game will always be in one of four states 
	enum class State { PAUSED, LEVELING_UP, GAME_OVER, PLAYING};
	// Start with the GAME_OVER state
	State state = State::GAME_OVER;


	// Get the screen resolution and create an SFML window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(resolution.x, resolution.y),
		"Zombie Arena", Style::Fullscreen);

	// Create a an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	// Here is our clock for timing everything
	Clock clock;
	// How long has the PLAYING state been active
	Time gameTimeTotal;

	//Time variable used to increment bulletsSpare every 3 seconds (give player ammo)
	Time giveBulletTime;

	//Time variable to start at 5 seconds and decrement when the player is invincible
	Time inviTime;

	// Where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;
	// Where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;

	// Create an instance of the Player class
	Player player;

	// The boundaries of the arena
	IntRect arena;

	// Create the background
	VertexArray background;
	// Load the texture for our background vertex array
	Texture textureBackground = TextureHolder::GetTexture(
		"graphics/background_sheet.png");

	// Prepare for a horde of zombies
	int numZombies;
	int numZombiesAlive;
	Zombie* zombies = NULL;

	// 100 bullets should do
	Bullet bullets[100];
	int currentBullet = 0;
	int bulletsSpare = 24;
	int bulletsInClip = 6;
	int clipSize = 6;
	int fireRate = 1;
	// When was the fire button last pressed?
	Time lastPressed;

	// Hide the mouse pointer and replace it with crosshair
	window.setMouseCursorVisible(true);
	Sprite spriteCrosshair;
	Texture textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");
	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 25);

	// Create a couple of pickups
	Pickup healthPickup(1);
	Pickup ammoPickup(2);
	
	Pickup killerPickup(3);//New healthKiller pickup
	Pickup ratePickup(4);//New ratePickup pickup
	Pickup invinciblePickup(5);//New invincible pickup

	// About the game
	int score = 0;
	int hiScore = 0;

	//boolean to turn true if player is invincible
	bool isPower = false;

	//int that represents the maximum time the player is invincible
	int maxInvi;

	

	// For the home/game over screen
	Sprite spriteGameOver;
	Texture textureGameOver = TextureHolder::GetTexture("graphics/background.png");
	spriteGameOver.setTexture(textureGameOver);
	spriteGameOver.setPosition(0, 0);

	// Create a view for the HUD
	View hudView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	// Create a sprite for the ammo icon
	Sprite spriteAmmoIcon;
	Texture textureAmmoIcon = TextureHolder::GetTexture("graphics/ammo_icon.png");
	spriteAmmoIcon.setTexture(textureAmmoIcon);
	spriteAmmoIcon.setPosition(20, 980);

	// Load the fonts
	Font font;
	font.loadFromFile("fonts/zombiecontrol.ttf");

	Font howTo;
	howTo.loadFromFile("fonts/howTo.ttf");

	// Paused
	Text pausedText;
	pausedText.setFont(font);
	pausedText.setCharacterSize(155);
	pausedText.setFillColor(Color::White);
	pausedText.setPosition(400, 400);
	pausedText.setString("Press Enter \nto continue");

	// Game Over
	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(125);
	gameOverText.setFillColor(Color::White);
	gameOverText.setPosition(250, 850);
	gameOverText.setString("Press Enter to play");

	// Levelling up
	Text levelUpText;
	levelUpText.setFont(font);
	levelUpText.setCharacterSize(80);
	levelUpText.setFillColor(Color::White);
	levelUpText.setPosition(150, 250);
	std::stringstream levelUpStream;
	levelUpStream <<
		"1- Start with full health" <<
		"\n2- Increased clip size(next reload)" <<
		"\n3- Increased max health" <<
		"\n4- Increased run speed" <<
		"\n5- More and better health pickups" <<
		"\n6- More and better ammo pickups";
	levelUpText.setString(levelUpStream.str());

	//How to play text
	Text howToText;
	howToText.setFont(howTo);
	howToText.setCharacterSize(50);
	howToText.setFillColor(Color::White);
	howToText.setPosition(50, 50);
	std::stringstream howToStream;
	howToStream <<
		"Welcome to the game!" <<
		"\nShoot with left mouse" <<
		"\nMove with WASD keys" <<
		"\nGreen medkit gives health" <<
		"\nRed medkit removes health" <<
		"\nOrange pickup gives full auto fire rate" 
		"\nPink pickup gives invincibility for 5 seconds" <<
		"\n1 bullet is given every 5 secs";
	howToText.setString(howToStream.str());



	// Ammo
	Text ammoText;
	ammoText.setFont(font);
	ammoText.setCharacterSize(55);
	ammoText.setFillColor(Color::White);
	ammoText.setPosition(200, 980);

	// Score
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(55);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(20, 0);

	// Load the high score from a text file/
	std::ifstream inputFile("gamedata/scores.txt");
	if (inputFile.is_open())
	{
		inputFile >> hiScore;
		inputFile.close();
	}

	// Hi Score
	Text hiScoreText;
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(55);
	hiScoreText.setFillColor(Color::White);
	hiScoreText.setPosition(1200, 0);
	std::stringstream s;
	s << "Hi Score:" << hiScore;
	hiScoreText.setString(s.str());

	// Zombies remaining
	Text zombiesRemainingText;
	zombiesRemainingText.setFont(font);
	zombiesRemainingText.setCharacterSize(55);
	zombiesRemainingText.setFillColor(Color::White);
	zombiesRemainingText.setPosition(1300, 980);
	zombiesRemainingText.setString("Zombies: 100");

	// Wave number
	int wave = 0;
	Text waveNumberText;
	waveNumberText.setFont(font);
	waveNumberText.setCharacterSize(55);
	waveNumberText.setFillColor(Color::White);
	waveNumberText.setPosition(800, 980);
	waveNumberText.setString("Wave: 0");

	// Kill counter
	int kills = 0;
	Text killsText;
	killsText.setFont(font);
	killsText.setCharacterSize(55);
	killsText.setFillColor(Color::White);
	killsText.setPosition(800, 0);
	killsText.setString("Kills: 0");

	// Health bar
	RectangleShape healthBar;
	healthBar.setFillColor(Color::Red);
	healthBar.setPosition(450, 980);
		
	// When did we last update the HUD?
	int framesSinceLastHUDUpdate = 0;
	// What time was the last update
	Time timeSinceLastUpdate;
	// How often (in frames) should we update the HUD
	int fpsMeasurementFrameInterval = 1000;

	// Prepare the hit sound
	SoundBuffer hitBuffer;
	hitBuffer.loadFromFile("sound/hit.wav");
	Sound hit;
	hit.setBuffer(hitBuffer);

	// Prepare the splat sound
	SoundBuffer splatBuffer;
	splatBuffer.loadFromFile("sound/splat.wav");
	sf::Sound splat;
	splat.setBuffer(splatBuffer);

	// Prepare the shoot sound
	SoundBuffer shootBuffer;
	shootBuffer.loadFromFile("sound/shoot.wav");
	Sound shoot;
	shoot.setBuffer(shootBuffer);

	// Prepare the reload sound
	SoundBuffer reloadBuffer;
	reloadBuffer.loadFromFile("sound/reload.wav");
	Sound reload;
	reload.setBuffer(reloadBuffer);

	// Prepare the failed sound
	SoundBuffer reloadFailedBuffer;
	reloadFailedBuffer.loadFromFile("sound/reload_failed.wav");
	Sound reloadFailed;
	reloadFailed.setBuffer(reloadFailedBuffer);

	// Prepare the powerup sound
	SoundBuffer powerupBuffer;
	powerupBuffer.loadFromFile("sound/powerup.wav");
	Sound powerup;
	powerup.setBuffer(powerupBuffer);

	// Prepare the pickup sound
	SoundBuffer pickupBuffer;
	pickupBuffer.loadFromFile("sound/pickup.wav");
	Sound pickup;
	pickup.setBuffer(pickupBuffer);

	// Prepare the fireRate sound
	SoundBuffer rateBuffer;
	rateBuffer.loadFromFile("sound/blind.wav");
	Sound rateUp;
	rateUp.setBuffer(rateBuffer);

	//Prepare the health loss sound
	SoundBuffer lossBuffer;
	lossBuffer.loadFromFile("sound/health_loss.wav");
	Sound lossHealth;
	lossHealth.setBuffer(lossBuffer);


	//Prepare the invincible sound
	SoundBuffer inviBuffer;
	inviBuffer.loadFromFile("sound/invincible.wav");
	Sound inviOn;
	inviOn.setBuffer(inviBuffer);

	// The main game loop
	while (window.isOpen())
	{
		/*
		************
		Handle input
		************
		*/

		// Handle events
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				// Pause a game while playing
				if (event.key.code == Keyboard::Return &&
					state == State::PLAYING)
				{
					state = State::PAUSED;
				}

				// Restart while paused
				else if (event.key.code == Keyboard::Return &&
					state == State::PAUSED)
				{
					state = State::PLAYING;
					// Reset the clock so there isn't a frame jump
					clock.restart();
				}

				// Start a new game while in GAME_OVER state
				else if (event.key.code == Keyboard::Return &&
					state == State::GAME_OVER)
				{
					state = State::LEVELING_UP;
					wave = 0;
					
					//Reset score, kills and invincibility pickup
					score = 0;
					kills = 0;
					isPower = false;
					maxInvi = 5;
					inviTime = sf::seconds(0);
					

					// Prepare the gun and ammo for next game
					currentBullet = 0;
					bulletsSpare = 24;
					bulletsInClip = 6;
					clipSize = 6;
					fireRate = 2;

					// Reset the player's stats
					player.resetPlayerStats();
				}

				


				if (state == State::PLAYING)
				{
					// Reloading
					if (event.key.code == Keyboard::R)
					{
						if (bulletsSpare >= 0) // Changed to >= 0 to allow reloading with 0 spare
						{
							int bulletsToLoad = clipSize - bulletsInClip; // Calculate how many bullets to load

							if (bulletsSpare >= bulletsToLoad)
							{
								// Enough spare bullets to fill the clip
								bulletsInClip = clipSize;
								bulletsSpare -= bulletsToLoad;
							}
							else
							{
								// Not enough spare bullets to fill the clip
								bulletsInClip += bulletsSpare;
								bulletsSpare = 0;
							}
							reload.play();
						}
						else
						{
							// No spare bullets
							reloadFailed.play();
						}
					}
				}

			}
		}// End event polling


		 // Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Handle controls while playing
		if (state == State::PLAYING)
		{
			// Handle the pressing and releasing of the WASD keys
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player.moveUp();
			}
			else
			{
				player.stopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player.moveDown();
			}
			else
			{
				player.stopDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				player.moveLeft();
			}
			else
			{
				player.stopLeft();
			}

			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				player.moveRight();
			}
			else
			{
				player.stopRight();
			}

			// Fire a bullet
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{

				if (gameTimeTotal.asMilliseconds()
					- lastPressed.asMilliseconds()
					> 1000 / fireRate && bulletsInClip > 0)
				{

					// Pass the centre of the player and the centre of the crosshair
					// to the shoot function
					bullets[currentBullet].shoot(
						player.getCenter().x, player.getCenter().y,
						mouseWorldPosition.x, mouseWorldPosition.y);

					currentBullet++;
					if (currentBullet > 99)
					{
						currentBullet = 0;
					}
					lastPressed = gameTimeTotal;
					shoot.play();
					bulletsInClip--;
				}

			}// End fire a bullet

		}// End WASD while playing

		// Handle the levelling up state
		if (state == State::LEVELING_UP)
		{
			// Increase fire rate based on round
			fireRate = 2 + wave;
			player.changeSprite(fireRate, isPower);

			//Remove the invincibility power up as the wave has now ended
			isPower = false;
			inviTime = sf::seconds(0);

			// Despawn every pickup so they're fresh for a new round
			healthPickup.despawn();
			ammoPickup.despawn();
			killerPickup.despawn();
			ratePickup.despawn();
			invinciblePickup.despawn();
			
			// Handle the player levelling up

			
			if (event.key.code == Keyboard::Num1)//Player now can start with max health
			{
				
				player.fullHealth();
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num2)
			{
				// Increase clip size
				clipSize += clipSize;
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num3)
			{
				// Increase health
				player.upgradeHealth();
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num4)
			{
				// Increase speed
				player.upgradeSpeed();
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num5)
			{
				healthPickup.upgrade();
				state = State::PLAYING;
			}

			if (event.key.code == Keyboard::Num6)
			{
				ammoPickup.upgrade();
				ratePickup.upgrade();//Increase rate of ammo pickup
				state = State::PLAYING;
			}

			if (state == State::PLAYING)
			{
				// Increase the wave number
				wave++;

				
				

				// Prepare thelevel
				
				//Level starts off BIG in wave 1, then gets smaller with each wave
				if (wave <= 5)
				{
					//Make the arena smaller by 500x500 multiplied by the wave value
					arena.width = 3000 - (500 * wave);
					arena.height = 3000 - (500 * wave);

					// Create a horde of zombies that starts off as 30 minus 5*wave value
					numZombies = 30 - (5* wave);

				}
				else //Once wave 6 starts, the arena remains at a small size, while number of zombies increment with each wave
				{
					arena.width = 500;
					arena.height = 500;
					numZombies++;
				}
				
				arena.left = 0;
				arena.top = 0;


				//The background arena changes between 3 different versions each round
				//The value of the modulus of 3 with the wave number -1 is used
				switch ((wave - 1) % 3)
				{
				case 0:
					textureBackground = TextureHolder::GetTexture("graphics/background_sheet.png");
					break;
				case 1:
					textureBackground = TextureHolder::GetTexture("graphics/background_sheet2.png");
					break;
				case 2:
					textureBackground = TextureHolder::GetTexture("graphics/background_sheet3.png");
					break;
				}

				// Pass the vertex array by reference 
				// to the createBackground function
				int tileSize = createBackground(background, arena);

				// Spawn the player in the middle of the arena
				player.spawn(arena, resolution, tileSize);

				// Configure the pick-ups
				healthPickup.setArena(arena);
				ammoPickup.setArena(arena);
				killerPickup.setArena(arena);
				ratePickup.setArena(arena);
				invinciblePickup.setArena(arena);

				
				// Delete the previously allocated memory (if it exists)
				delete[] zombies;
				zombies = createHorde(numZombies, arena);
				numZombiesAlive = numZombies;

				// Play the powerup sound
				powerup.play();

				// Reset the clock so there isn't a frame jump
				clock.restart();
			}
		}// End levelling up

		 /*
		 ****************
		 UPDATE THE FRAME
		 ****************
		 */
		if (state == State::PLAYING)
		{
			// Update the delta time
			Time dt = clock.restart();
			// Update the total game time
			gameTimeTotal += dt;

			//Update the giveBulletTime
			giveBulletTime += dt;

			//Reduce the invincibility time if the wave is at least 5
			if (wave >= 5)
			{
				maxInvi = 2;
			}

			//If the player is invincible, enseure that they are while the inviTime is less than maxInvi
			if ((isPower) && (inviTime.asSeconds() < maxInvi))
			{
				//Increment inviTime while it is less than 5 seconds
				inviTime += dt;

				//Play invincible sound to inform player that they are invincible
				inviOn.play();
			
			}
			else if ((isPower) && (inviTime.asSeconds() >= maxInvi))//Stop the invincibility when inviTime reaches maxInvi
			{
				//Set isPower to false and reset inviTime to 0 seconds
				isPower = false;
				inviTime = sf::seconds(0);

				//Change the player's sprite back to its original one
				player.changeSprite(fireRate, isPower);
			}

			
			//Give the player 1 bullet every 3 seconds
			if (giveBulletTime.asSeconds() >= 3)
			{
				bulletsSpare++;

				//Bring the time back to 0 to reset the bullet clock
				giveBulletTime = sf::Time::Zero;
			}

			// Make a decimal fraction of 1 from the delta time
			float dtAsSeconds = dt.asSeconds();
			
			int secPassed = dt.asMilliseconds();
			cout << secPassed << endl;

			// Where is the mouse pointer
			mouseScreenPosition = Mouse::getPosition();

			// Convert mouse position to world coordinates of mainView
			mouseWorldPosition = window.mapPixelToCoords(
				Mouse::getPosition(), mainView);

			// Set the crosshair to the mouse world location
			spriteCrosshair.setPosition(mouseWorldPosition);

			// Update the player
			player.update(dtAsSeconds, Mouse::getPosition());

			// Make a note of the players new position
			Vector2f playerPosition(player.getCenter());

			// Make the view centre around the player				
			mainView.setCenter(player.getCenter());

			// Loop through each Zombie and update them
			for (int i = 0; i < numZombies; i++)
			{
				if (zombies[i].isAlive())
				{
					zombies[i].update(dt.asSeconds(), playerPosition);
				}
			}

			// Update any bullets that are in-flight
			for (int i = 0; i < 100; i++)
			{
				if (bullets[i].isInFlight())
				{
					bullets[i].update(dtAsSeconds);
				}
			}

			
			/*if () % 10 == 0)
			{
				bulletsSpare++;
			}*/

			// Update the pickups
			healthPickup.update(dtAsSeconds);
			ammoPickup.update(dtAsSeconds);
			killerPickup.update(dtAsSeconds);
			ratePickup.update(dtAsSeconds);
			invinciblePickup.update(dtAsSeconds);

			// Collision detection
			// Have any zombies been shot?
			for (int i = 0; i < 100; i++)
			{
				for (int j = 0; j < numZombies; j++)
				{
					if (bullets[i].isInFlight() && 
						zombies[j].isAlive())
					{
						if (bullets[i].getPosition().intersects
							(zombies[j].getPosition()))
						{
							// Stop the bullet
							bullets[i].stop();

							// Register the hit and see if it was a kill
							if (zombies[j].hit(isPower)) {
								// Not just a hit but a kill too
								score += 10;
								if (score >= hiScore)
								{
									hiScore = score;
								}

								numZombiesAlive--;
								kills++;

								// When all the zombies are dead (again)
								if (numZombiesAlive <= 0) {
									state = State::LEVELING_UP;
								}
							}	

							// Make a splat sound
							splat.play();
							
						}
					}

				}
			}// End zombie being shot

			// Have any zombies touched the player			
			for (int i = 0; i < numZombies; i++)
			{	
				//Collision detection is now based on the playeer's smaller floatrect
				if (player.giveHitPosition().intersects
					(zombies[i].getPosition()) && zombies[i].isAlive())
				{

					//Kill the zombie if the player is invincible
					if (isPower)
					{
						zombies[i].hit(isPower);
						numZombiesAlive--;
						kills++;
						splat.play();

						// When all the zombies are dead (again)
						if (numZombiesAlive <= 0) {
							state = State::LEVELING_UP;
						}
					}
					else //Player takes damage is theyre not invincible
					{
						if (player.hit(gameTimeTotal))
						{
							// More here later
							hit.play();
						}

						if (player.getHealth() <= 0)
						{
							state = State::GAME_OVER;

							std::ofstream outputFile("gamedata/scores.txt");
							outputFile << hiScore;
							outputFile.close();

						}
					}
					
					
				}
			}// End player touched

			// Has the player touched health pickup
			if (player.getPosition().intersects
				(healthPickup.getPosition()) && healthPickup.isSpawned())
			{
				player.increaseHealthLevel(healthPickup.gotIt());
				// Play a sound
				pickup.play();
				
			}

			// Has the player touched ammo pickup
			if (player.getPosition().intersects
				(ammoPickup.getPosition()) && ammoPickup.isSpawned())
			{
				bulletsSpare += ammoPickup.gotIt();
				// Play a sound
				reload.play();
				
			}


			// Has the player touched health killer
			if (player.getPosition().intersects
			(killerPickup.getPosition()) && killerPickup.isSpawned())
			{
				killerPickup.gotIt();

				//Set player's health to 0 (they have been poisoned)
				player.setHealth();
				// Play a sound
				lossHealth.play();

			}


			// Has the player touched fire rate increaser
			if (player.getPosition().intersects
			(ratePickup.getPosition()) && ratePickup.isSpawned())
			{
				ratePickup.gotIt();
				
				//Increase fire rate to super speed
				fireRate = 100;

				//Change the player's sprite so it showcases that they have automatic fire
				player.changeSprite(fireRate, isPower);
				// Play a sound
				rateUp.play();

			}

			// Has the player touched invincible pickup
			if (player.getPosition().intersects
			(invinciblePickup.getPosition()) && invinciblePickup.isSpawned())
			{
				invinciblePickup.gotIt();

				//Increase fire rate to super speed
				isPower = true;

				//Change the player's sprite so it showcases that they have automatic fire
				player.changeSprite(fireRate, isPower);
				

			}

			

			// size up the health bar
			healthBar.setSize(Vector2f(player.getHealth() * 3, 70));

			// Increment the amount of time since the last HUD update
			timeSinceLastUpdate += dt;
			// Increment the number of frames since the last HUD calculation
			framesSinceLastHUDUpdate++;
			// Calculate FPS every fpsMeasurementFrameInterval frames
			if (framesSinceLastHUDUpdate > fpsMeasurementFrameInterval)
			{

				// Update game HUD text
				std::stringstream ssAmmo;
				std::stringstream ssScore;
				std::stringstream ssHiScore;
				std::stringstream ssWave;
				std::stringstream ssZombiesAlive;
				std::stringstream ssKills;

				// Update the ammo text
				ssAmmo << bulletsInClip << "/" << bulletsSpare;
				ammoText.setString(ssAmmo.str());

				// Update the score text
				ssScore << "Score:" << score;
				scoreText.setString(ssScore.str());

				// Update the high score text
				ssHiScore << "Hi Score:" << hiScore;
				hiScoreText.setString(ssHiScore.str());

				// Update the wave
				ssWave << "Wave:" << wave;
				waveNumberText.setString(ssWave.str());

				// Update the high score text
				ssZombiesAlive << "Zombies:" << numZombiesAlive;
				zombiesRemainingText.setString(ssZombiesAlive.str());

				// Update the kill counter
				ssKills << "Kills:" << kills;
				killsText.setString(ssKills.str());

				framesSinceLastHUDUpdate = 0;
				timeSinceLastUpdate = Time::Zero;
			}// End HUD update

		}// End updating the scene

		 /*
		 **************
		 Draw the scene
		 **************
		 */

		if (state == State::PLAYING)
		{
			window.clear();

			// set the mainView to be displayed in the window
			// And draw everything related to it
			window.setView(mainView);

			// Draw the background
			window.draw(background, &textureBackground);

			// Draw the zombies
			for (int i = 0; i < numZombies; i++)
			{
				window.draw(zombies[i].getSprite());
			}

			for (int i = 0; i < 100; i++)
			{
				if (bullets[i].isInFlight())
				{
					window.draw(bullets[i].getShape());
				}
			}

			// Draw the player
			window.draw(player.getSprite());

			// Draw the pickups is currently spawned
			if (ammoPickup.isSpawned())
			{
				window.draw(ammoPickup.getSprite());
			}
			
			if (healthPickup.isSpawned())
			{
				window.draw(healthPickup.getSprite());
			}
			
			if (killerPickup.isSpawned())
			{
				window.draw(killerPickup.getSprite());
			}
			
			if (ratePickup.isSpawned())
			{
				window.draw(ratePickup.getSprite());
			}
			
			if (invinciblePickup.isSpawned())
			{
				window.draw(invinciblePickup.getSprite());
			}

			//Draw the crosshair
			window.draw(spriteCrosshair);

			// Switch to the HUD view
			window.setView(hudView);

			// Draw all the HUD elements
			window.draw(spriteAmmoIcon);
			window.draw(ammoText);
			window.draw(scoreText);
			window.draw(hiScoreText);
			window.draw(healthBar);
			window.draw(waveNumberText);
			window.draw(zombiesRemainingText);
			window.draw(killsText);
		}

		if (state == State::LEVELING_UP)
		{
			window.draw(spriteGameOver);
			window.draw(levelUpText);
		}

		if (state == State::PAUSED)
		{
			window.draw(pausedText);
		}

		

		if (state == State::GAME_OVER)
		{
			window.draw(spriteGameOver);
			window.draw(gameOverText);
			window.draw(scoreText);
			window.draw(hiScoreText);
			window.draw(howToText);
		}

		window.display();

	}// End game loop

	return 0;
}