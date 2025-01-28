// Include important C++ libraries here
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <iomanip> //To round time values

// Make code easier to type with "using namespace"
using namespace sf;

//Used for debugging and outputting messages to the console
using std::cout;


// Function declaration
void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

// Where is the player/branch? 
// Left or Right
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];


int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

	// Create a texture to hold a graphic on the GPU
	Texture textureBackground;
	Texture textureBackgroundDay;
	Texture textureBackgroundNight;

	// Load a graphic into the texture
	textureBackground.loadFromFile("graphics/background.png");
	textureBackgroundNight.loadFromFile("graphics/backgroundNight.png");
	textureBackgroundDay.loadFromFile("graphics/backgroundDay.png");

	// Create a sprite
	Sprite spriteBackground;

	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(0, 0);

	// Make a tree sprite
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	// Prepare the bee
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);
	spriteBee.setOrigin(30, 20);
	spriteBee.setScale(-1, 1);

	// Is the bee currently moving?
	bool beeActive = false;

	// How fast can the bee fly
	float beeSpeed = 0.0f;

	
	
	// Prepare the time replenisher
	Texture textureRep;
	textureRep.loadFromFile("graphics/block.png");
	Sprite spriteRep;
	spriteRep.setTexture(textureRep);
	spriteRep.setPosition(1920, 800);
	spriteRep.setOrigin(30, 20);
	spriteRep.setScale(-1, 1);

	// Is the replenisher currently moving?
	bool repActive = false;

	// How fast can the replenisher move
	float repSpeed = 0.0f;


	// Prepare the nest
	Texture textureNest;
	textureNest.loadFromFile("graphics/nest.png");
	Sprite spriteNest;
	spriteNest.setTexture(textureNest);
	spriteBee.setPosition(-400, -2000);
	spriteBee.setOrigin(30, 20);
	

	// Is the nest currently moving?
	bool NestActive = false;

	// How fast can the nest fall?
	float NestSpeed = 0.0f;



	
	
	// Prepare the shield
	Texture textureShield;
	textureShield.loadFromFile("graphics/shield.png");
	Sprite spriteShield;
	spriteShield.setTexture(textureShield);
	spriteBee.setPosition(-400, -2000);
	spriteBee.setOrigin(30, 20);


	// Is the shield currently moving?
	bool ShieldActive = false;

	// How fast can the shield fall?
	float ShieldSpeed = 0.0f;



	
	
	// make 3 cloud sprites from 1 texture
	Texture textureCloud;

	// Load 1 new texture
	textureCloud.loadFromFile("graphics/cloud.png");

	// 3 New sprites withe the same texture
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);

	// Position the clouds off screen
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 150);
	spriteCloud3.setPosition(0, 300);

	// Are the clouds currently on screen?
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	// How fast is each cloud?
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	// Variables to control time itself
	Clock clock;
	// Time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float totalTime = 0.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;


	//Time counter if the player gets stung
	float stungTime = 0.0f;
	
	//Did the player get stung?
	bool gotStung = false;

	//Did the player get the replensiher?
	bool gotRep = false;

	//Did the nest fall on the player's head?
	bool gotNest = false;

	//Did the player get the shield?
	bool gotShield = false;

	//Number that counts up to 5 when the player is blinded by the nest
	int blindCount = 5;

	//To disable input for the player
	bool giveInput = true;

	// Track whether the game is running
	bool paused = true;
	
	// Draw some text
	int score = 0;

	int lives = 2;

	float totalScore = 0;

	sf::Text messageText;
	sf::Text logText;
	sf::Text timeText;
	sf::Text totalText;
	sf::Text toscText;
	

	// We need to choose a font
	sf::Font font;
	font.loadFromFile("fonts/FUTURAM_.ttf");

	// Set the font to our message
	messageText.setFont(font);
	logText.setFont(font);
	timeText.setFont(font);
	totalText.setFont(font);
	toscText.setFont(font);


	// Assign the actual message
	messageText.setString("Press Enter to start!");
	logText.setString("Logs = 0");
	timeText.setString("Time: 0");
	totalText.setString("Total Time: 0");
	toscText.setString("Score: 0");
	

	// Make it really big
	messageText.setCharacterSize(75);
	logText.setCharacterSize(100);
	timeText.setCharacterSize(25);
	totalText.setCharacterSize(75);
	toscText.setCharacterSize(75);


	// Choose a color
	messageText.setFillColor(Color::White);
	logText.setFillColor(Color::White);
	timeText.setFillColor(Color::White);
	totalText.setFillColor(Color::White);
	toscText.setFillColor(Color::Yellow);
	

	// Position the text
	FloatRect textRect = messageText.getLocalBounds();

	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

	logText.setPosition(20, 20);

	timeText.setPosition(650, 1000);

	totalText.setPosition(20, 200);

	toscText.setPosition(500, 700);

	// Prepare 5 branches
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");

	// Set the texture for each branch sprite
	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);

		// Set the sprite's origin to dead center
		// We can then spin it round without changing its position
		branches[i].setOrigin(220, 20);
	}

	// Prepare the player
	Texture texturePlayer;
	Texture textureStungPlayer;
	Texture textureNestPlayer;
	Texture textureShieldPlayer;
	Texture textureBlockPlayer;

	texturePlayer.loadFromFile("graphics/player.png");
	textureStungPlayer.loadFromFile("graphics/playerStung.png");
	textureNestPlayer.loadFromFile("graphics/playerNest.png");
	textureShieldPlayer.loadFromFile("graphics/playerShield.png");
	textureBlockPlayer.loadFromFile("graphics/playerBlock.png");

	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);
	

	// The player starts on the left
	side playerSide = side::LEFT;

	// Prepare the gravestone
	Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 860);

	// Prepare the axe
	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	// Line the axe up with the tree
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	// Prepare the flying log
	Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);

	// Some other useful log related variables
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;
	
	// Control the player input
	bool acceptInput = false;

	// Prepare the sound
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);

	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);

	// Out of time
	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("sound/out_of_time.wav");
	Sound outOfTime;
	outOfTime.setBuffer(ootBuffer);

	//Stung by bee
	SoundBuffer stungBuffer;
	stungBuffer.loadFromFile("sound/stung.wav");
	Sound stung;
	stung.setBuffer(stungBuffer);


	//Blinded by nest
	SoundBuffer nestBuffer;
	nestBuffer.loadFromFile("sound/blind.wav");
	Sound nest;
	nest.setBuffer(nestBuffer);


	//Got the replenisher
	SoundBuffer repBuffer;
	repBuffer.loadFromFile("sound/replenish.wav");
	Sound rep;
	rep.setBuffer(repBuffer);

	//Got the shield
	SoundBuffer sgetBuffer;
	sgetBuffer.loadFromFile("sound/shieldGet.wav");
	Sound sget;
	sget.setBuffer(sgetBuffer);

	//Using the shield
	SoundBuffer sheldBuffer;
	sheldBuffer.loadFromFile("sound/shieldHeld.wav");
	Sound sheld;
	sheld.setBuffer(sheldBuffer);



	
	while (window.isOpen())
	{
		// score ++;
		Event event;
		while (window.pollEvent(event))
		{
			

			if (event.type == Event::KeyReleased && !paused)
			{
				// Listen for key presses again
				acceptInput = true;

				// hide the axe
				spriteAxe.setPosition(2000,
					spriteAxe.getPosition().y);
			}

		}

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;

			// Reset the time, scores, bee position, replenish position, nest position and player texture
			score = 0;
			timeRemaining = 6;
			totalTime = 0;
			blindCount = 5;
			
			//We set the positions far from the screen to prevent them from appearing at the start of the layout
			spriteBee.setPosition(-10000, 800);
			spriteRep.setPosition(10000, 800);
			spriteNest.setPosition(1250, -5000);
			spriteShield.setPosition(680, -5000);
			
			//Reset all elements and player texture to original state
			NestActive = false;
			stungTime = 0;
			gotStung = false;
			gotRep = false;
			gotNest = false;
			ShieldActive = false;
			gotShield = false;
			giveInput = true;
			
			spritePlayer.setTexture(texturePlayer);
			

			// Make all the branches disappear
			for (int i = 1; i < NUM_BRANCHES; i++)
			{
				branchPositions[i] = side::NONE;
			}

			// Make sure the gravestone is hidden
			spriteRIP.setPosition(675, 2000);

			// Move the player into position
			spritePlayer.setPosition(580, 720);

			acceptInput = true;


		}

		// Wrap the player controls to
		// Make sure we are accepting input
		if (acceptInput)
		{
			// More code here next...
			// First handle pressing the right cursor key
			if (Keyboard::isKeyPressed(Keyboard::Right) && (giveInput))
			{
				
				
				// Make sure the player is on the right
				playerSide = side::RIGHT;

				
				score++;

				// Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;

				spriteAxe.setPosition(AXE_POSITION_RIGHT,
					spriteAxe.getPosition().y);

				

				spritePlayer.setPosition(1200, 720);
				

				// update the branches
				updateBranches(score);

				// set the log flying to the left
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;


				acceptInput = false;

				// Play a chop sound
				chop.play();


				//Count up the blindCount if the player is blinded by the nest
				if (gotNest == true)
				{
					blindCount++;
				}

			}

			// Handle the left cursor key
			if (Keyboard::isKeyPressed(Keyboard::Left) && giveInput)
			{

				
				// Make sure the player is on the left
				playerSide = side::LEFT;

				score++;

				// Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;

				spriteAxe.setPosition(AXE_POSITION_LEFT,
					spriteAxe.getPosition().y);


				spritePlayer.setPosition(580, 720);
				

				// update the branches
				updateBranches(score);

				// set the log flying
				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;


				acceptInput = false;

				// Play a chop sound
				chop.play();


				//Count up the blindCount if the player is blinded by the nest
				if (gotNest == true)
				{
					blindCount++;
				}

			}




			// Handle the down key if the shield was obtained
			if (((Keyboard::isKeyPressed(Keyboard::Down)) && (giveInput)) && (gotShield))
			{
				gotStung = true;
				sheld.play();
				spritePlayer.setTexture(textureBlockPlayer);
			}
			
			//When down is released, stop the shield ability
			if ((event.type == Event::KeyReleased && event.key.code == Keyboard::Down) && (gotShield))
			{
				gotStung = false;
				spritePlayer.setTexture(textureShieldPlayer);
			}
		}



		//Change the background based on score to give a sense of time passing
		if ((score > 50) && (score < 100))
		{
			spriteBackground.setTexture(textureBackgroundNight);
		}
		else if (score >= 100)
		{
			spriteBackground.setTexture(textureBackgroundDay);
		}
		else
		{
			spriteBackground.setTexture(textureBackground);
		}


		/*
		****************************************
		Update the scene
		****************************************
		*/
		if (!paused)
		{

			// Measure time
			Time dt = clock.restart();





			// Subtract from the amount of time remaining
			timeRemaining -= dt.asSeconds();
			// size up the time bar
			timeBar.setSize(Vector2f(timeBarWidthPerSecond *
				timeRemaining, timeBarHeight));

			//Add time to the totalTime float to keep track of total time elapsed 
			totalTime += dt.asSeconds();


			if (timeRemaining <= 0.0f)
			{

				// Pause the game
				paused = true;

				// Change the message shown to the player
				messageText.setString("Out of time!!");

				//Reposition the text based on its new size
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top +
					textRect.height / 2.0f);

				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				// Play the out of time sound
				outOfTime.play();


			}


			// Setup the bee
			if ((!beeActive) && (score >= 25))
			{

				// How fast is the bee
				srand((int)time(0) * 10);
				beeSpeed = (rand() % 500) + 300;

				// How high is the bee
				float height = 800;
				spriteBee.setPosition(-100, height);
				beeActive = true;
				gotStung = false;

			}
			else
			{
				// Move the bee
				spriteBee.setPosition
				(spriteBee.getPosition().x + (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);


				//Mirror the bee spirte so it's facing the right direction when it moves back
				if (spriteBee.getPosition().x > 605)
				{
					spriteBee.setScale(1, 1);
					beeSpeed = -beeSpeed;
				}
				// Has the bee reached the left hand edge of the screen?
				else if ((spriteBee.getPosition().x < -100) || (spriteBee.getPosition().x > 2000))
				{
					// Set it up ready to be a whole new bee next frame
					beeActive = false;
					spriteBee.setScale(-1, 1);
					beeSpeed = beeSpeed;
				}

			}


			//Check if player has been stung by a bee
			if (((spriteBee.getPosition().x >= 600.0) && (playerSide == side::LEFT)) && (!gotStung))
			{

				stungTime = 0;
				stung.play();
				gotStung = true;
				giveInput = false;
				acceptInput = false;



			}

			//Player's input is disabled for 2 seconds after being stung by a bee
			if ((!giveInput) && (stungTime < 2))
			{
				spritePlayer.setTexture(textureStungPlayer);
				stungTime += dt.asSeconds();
				if (stungTime >= 2)
				{
					giveInput = true;
					acceptInput = true;
					
					stungTime = 0;
					gotStung = false;

					
					//Player returns to shield texture if they got it. Otherwise, its the regular texture
					if (gotShield)
					{
						spritePlayer.setTexture(textureShieldPlayer);
					}
					else
					{
						spritePlayer.setTexture(texturePlayer);
					}
				}

			}




			// Setup the replenisher
			if ((!repActive) && (score >= 100)) 
			{
				// How fast is the replenisher
				repSpeed = 300;
				// How high is the replenisher
				float height = 800;
				spriteRep.setPosition(2020, height);
				repActive = true;
			}
			else if (repActive) 
			{
				// Move the replenisher
				spriteRep.setPosition(spriteRep.getPosition().x + (-repSpeed * dt.asSeconds()), spriteRep.getPosition().y);

				// Mirror the rep sprite so it's facing the right direction when it moves back
				if (spriteRep.getPosition().x < 1275) 
				{
					spriteRep.setScale(1, 1);
					repSpeed = -repSpeed;
				}

				// Has the replenisher reached the right-hand edge of the screen?
				if (spriteRep.getPosition().x > 2021) 
				{
					// Set it up ready to be a whole new replenisher next frame
					repActive = false;
					spriteRep.setScale(-1, 1);
					repSpeed = -repSpeed;
				}
			}

			// Check if the player has got the replenisher
			if (((spriteRep.getPosition().x <= 1280.0) && (playerSide == side::RIGHT)) && (!gotRep)) 
			{
				timeRemaining = 8;
				rep.play();
				gotRep = true;
				repActive = false; 
			}

			//Place the replenisher off screen after being collected
			if (gotRep)
			{
				spriteRep.setPosition(-500, 2000);
			}



			






			// Setup the nest
			if ((!NestActive) && (score >= 50))
			{

				// How fast is the nest
				srand((int)time(0) * 10);
				NestSpeed = (rand() % 300) + 200;

				// How high is the nest
				float height = -500;
				spriteNest.setPosition(1250, height);
				NestActive = true;


			}
			else
			{
				// Move the Nest
				spriteNest.setPosition
				(spriteNest.getPosition().x, spriteNest.getPosition().y + (NestSpeed * dt.asSeconds()));


				// Has the nest gone past the player's head?
				if ((spriteNest.getPosition().y > 716))
				{
					// Set it up ready to be a whole new nest next frame
					NestActive = false;
				}

			}


			//Check if nest has landed on player's head. The player can't see the branches for 5 axe swings
			if ((((spriteNest.getPosition().y >= 710.0) && (spriteNest.getPosition().y <= 715.0)) && (playerSide == side::RIGHT)) && (!gotNest))
			{

				nest.play();
				blindCount = 0;
				spritePlayer.setTexture(textureNestPlayer);
				gotNest = true;

			}


			//The player no longer is blinded by the nest after 5 axe swings
			if ((blindCount == 5) && (gotNest))
			{
				gotNest = false;

				//Player returns to shield texture if they got it. Otherwise, its the regular texture
				if (stungTime == 0)
				{
					if (gotShield)
					{
						spritePlayer.setTexture(textureShieldPlayer);
					}
					else
					{
						spritePlayer.setTexture(texturePlayer);
					}
					
				}
				
					
				
			}
			
			




			
			//Spawn the shield power up
			if ((!ShieldActive) && (score >= 75))
			{


				ShieldSpeed = 300;

				// How high is the shield
				float height = -200;

				spriteShield.setPosition(620, height);
				ShieldActive = true;


			}
			else
			{
				// Move the Shield
				spriteShield.setPosition
				(spriteShield.getPosition().x, spriteShield.getPosition().y + (ShieldSpeed * dt.asSeconds()));




				// Has the shield gone past the player's head?
				if (spriteShield.getPosition().y > 716)
				{
					// Set it up ready to be a whole new shield next frame
					ShieldActive = false;
				}

			}

			//Check if shield has landed on player's head. The player can then then block a bee sting by pressing down
			if (((spriteShield.getPosition().y >= 715.0) && (playerSide == side::LEFT)) && (!gotShield))
			{
				//The player texture changes if they get the shield
				sget.play();
				spritePlayer.setTexture(textureShieldPlayer);
				gotShield = true;

			}
			
			
			

			

			

			// Manage the clouds
			// Cloud 1
			if (!cloud1Active)
			{

				// How fast is the cloud
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200);

				// How high is the cloud
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud1.setPosition(-200, height);
				cloud1Active = true;


			}
			else
			{

				spriteCloud1.setPosition(
					spriteCloud1.getPosition().x +
					(cloud1Speed * dt.asSeconds()),
					spriteCloud1.getPosition().y);

				// Has the cloud reached the right hand edge of the screen?
				if (spriteCloud1.getPosition().x > 1920)
				{
					// Set it up ready to be a whole new cloud next frame
					cloud1Active = false;
				}
			}
			// Cloud 2
			if (!cloud2Active)
			{

				// How fast is the cloud
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);

				// How high is the cloud
				srand((int)time(0) * 20);
				float height = (rand() % 300) - 150;
				spriteCloud2.setPosition(-200, height);
				cloud2Active = true;


			}
			else
			{

				spriteCloud2.setPosition(
					spriteCloud2.getPosition().x +
					(cloud2Speed * dt.asSeconds()),
					spriteCloud2.getPosition().y);

				// Has the cloud reached the right hand edge of the screen?
				if (spriteCloud2.getPosition().x > 1920)
				{
					// Set it up ready to be a whole new cloud next frame
					cloud2Active = false;
				}
			}

			if (!cloud3Active)
			{

				// How fast is the cloud
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);

				// How high is the cloud
				srand((int)time(0) * 30);
				float height = (rand() % 450) - 150;
				spriteCloud3.setPosition(-200, height);
				cloud3Active = true;


			}
			else
			{

				spriteCloud3.setPosition(
					spriteCloud3.getPosition().x +
					(cloud3Speed * dt.asSeconds()),
					spriteCloud3.getPosition().y);

				// Has the cloud reached the right hand edge of the screen?
				if (spriteCloud3.getPosition().x > 1920)
				{
					// Set it up ready to be a whole new cloud next frame
					cloud3Active = false;
				}
			}

			// Update the score text
			std::stringstream ss;
			ss << "Logs = " << score;
			logText.setString(ss.str());

			// Update the time text
			std::stringstream st;
			st << "Time: " << static_cast<int>(timeRemaining);//timeRemaining is shown as an int to only show the seconds remaining
			timeText.setString(st.str());


			// Update the total time text
			std::stringstream sl;
			sl << std::fixed << std::setprecision(3) << "Total Time: " << totalTime;
			totalText.setString(sl.str());

			//Calculate the total score (logs chopped * time passed)
			totalScore = score * totalTime;


			// Update the total score text
			std::stringstream ts;
			ts << std::fixed << std::setprecision(3) << "Total Score: " << totalScore;
			toscText.setString(ts.str());

			

			// update the branch sprites
			for (int i = 0; i < NUM_BRANCHES; i++)
			{

				float height = i * 150;

				if (branchPositions[i] == side::LEFT)
				{
					// Move the sprite to the left side
					branches[i].setPosition(610, height);
					// Flip the sprite round the other way
					branches[i].setOrigin(220, 40);
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT)
				{
					// Move the sprite to the right side
					branches[i].setPosition(1330, height);
					// Set the sprite rotation to normal
					branches[i].setOrigin(220, 40);
					branches[i].setRotation(0);

				}
				else
				{
					// Hide the branch
					branches[i].setPosition(3000, height);
				}
			}

			// Handle a flying log				
			if (logActive)
			{

				spriteLog.setPosition(
					spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
					spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));

				// Has the insect reached the right hand edge of the screen?
				if (spriteLog.getPosition().x < -100 ||
					spriteLog.getPosition().x > 2000)
				{
					// Set it up ready to be a whole new cloud next frame
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}

			// has the player been squished by a branch?
			if (branchPositions[5] == playerSide)
			{
				// death
				paused = true;
				acceptInput = false;

				// Draw the gravestone
				spriteRIP.setPosition(525, 760);

				// hide the player
				spritePlayer.setPosition(2000, 660);

				//Change the colour of the message
				messageText.setFillColor(Color::Red);

				// Change the text of the message
				messageText.setString("SQUISHED!! YOU DIED!! :(");

				// Center it on the screen
				FloatRect textRect = messageText.getLocalBounds();

				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);

				messageText.setPosition(1920 / 2.0f,
					1080 / 2.0f);

				// Play the death sound
				death.play();


			}

			


		}// End if(!paused)

		 /*
		 ****************************************
		 Draw the scene
		 ****************************************
		 */

		 // Clear everything from the last frame
		window.clear();

		// Draw our game scene here
		window.draw(spriteBackground);

		// Draw the clouds
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		
		//Make the branches visible again after 5 blind axe chops
		if (blindCount == 5)
		{
			// Draw the branches
			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				window.draw(branches[i]);
			}
		}
		

		// Draw the tree
		window.draw(spriteTree);
		// Draw the player
		window.draw(spritePlayer);

		// Draw the axe
		window.draw(spriteAxe);

		// Draraw the flying log
		window.draw(spriteLog);

		// Draw the gravestone
		window.draw(spriteRIP);


		
		// Draw the bee
		window.draw(spriteBee);


		
		//Draw the replenisher
		window.draw(spriteRep);
		

		
		// Draw the nest
		window.draw(spriteNest);

		
		//Draw the shield if it hasnt been received yet
		if (!gotShield)
		{
			window.draw(spriteShield);
		}

		// Draw the score
		window.draw(logText);

		// Draw the timebar
		window.draw(timeBar);

		// Draw the timeText
		window.draw(timeText);

		// Draw the totalText
		window.draw(totalText);

		


		if (paused)
		{
			// Draw our message
			window.draw(messageText);

			//Draw the total score
			window.draw(toscText);
		}

		// Show everything we just drew
		window.display();


	}

	return 0;
}

// Function definition
void updateBranches(int seed)
{
	// Move all the branches down one place
	for (int j = NUM_BRANCHES - 1; j > 0; j--) {
		branchPositions[j] = branchPositions[j - 1];
	}

	// Spawn a new branch at position 0
	// LEFT, RIGHT or NONE
	srand((int)time(0) + seed);
	int r = (rand() % 5);

	switch (r) 
	{
		case 0:
			branchPositions[0] = side::LEFT;
			break;

		case 1:
			branchPositions[0] = side::RIGHT;
			break;

		default:
			branchPositions[0] = side::NONE;
			break;
	}


}





