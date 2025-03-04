#include "Game.h"
#include<iostream> //For input
Game::Game()

{
	
}

void Game::init()
{
	cout << "Initializing the game..." << endl;
	
	//Create  Player and Enemy objects based on their pointers (1 player and 4 enemies)
	pPlayer = new Player("Terry", 1, 50, 3, 3, 'T');
	pEnemy1 = new Enemy("Barry", 1, 55, 4, 4, 'b');
	pEnemy2 = new Enemy("Harry", 1, 45, 5, 5, 'h');
	pEnemy3 = new Enemy("Larry", 1, 60, 6, 6, 'l');
	pEnemy4 = new Enemy("Mary", 1, 41, 7, 7, 'm');
	

	// Add character pointers to the character list
	lpGameCharacters.push_back(pPlayer);
	lpGameCharacters.push_back(pEnemy1);
	lpGameCharacters.push_back(pEnemy2);
	lpGameCharacters.push_back(pEnemy3);
	lpGameCharacters.push_back(pEnemy4);
	
}

//Loop through the list of charcater pointers to set their health
void Game::setHealth() 
{
	//Use an iterator that increments to loop through every character in the list
	list<GameCharacter*>::const_iterator iter;
	for (iter = lpGameCharacters.begin(); iter != lpGameCharacters.end(); ++iter)
	{
		(*iter)->setHealth();//Call the setHealth() function for each iteration in the GameCharacter list

	}
}


//Loop through the list of charcater pointers to set their speed
void Game::setSpeed()
{	
	//Use an iterator that increments to loop through every character in the list
	list<GameCharacter*>::const_iterator iter;
	for (iter = lpGameCharacters.begin(); iter != lpGameCharacters.end(); ++iter)
	{
		(*iter)->setSpeed();//Call the setSpeed() function for each iteration in the GameCharacter list

	}
}

//Loop through the list of charcater pointers to state their current position
void Game::render()
{
	//Use an iterator that increments to loop through every character in the list
	list<GameCharacter*>::const_iterator iter;
	for (iter = lpGameCharacters.begin(); iter != lpGameCharacters.end(); ++iter)
	{
		(*iter)->render();//Call the render() function for each iteration in the GameCharacter list

	}
}

//Function to display the board to the console
void Game::displayBoard()
{
	// Initialize the board with empty spaces (represented by '-')
	for (int i = 0; i < 10; i++) 
	{
		for (int j = 0; j < 10; j++)
		{
			board[i][j] = '-';
		}
	}

	// Loop through the list of character pointer objects
	std::list<GameCharacter*>::const_iterator iter;
	for (iter = lpGameCharacters.begin(); iter != lpGameCharacters.end(); ++iter)
	{
		//Place the character's symbol on the board based on their x and y position 
		board[(*iter)->getyPos()][(*iter)->getxPos()] = (*iter)->getSymbol();
	}
	

	//board[0][0] = '@'; test co-ordinate to find out where the origin is
	
	// Display the board with the origin on the bottom left (like a cartesian plane)
	for (int i = 0; i < 10; i++)  // Start from the bottom row (i = 0 is the bottom)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << board[9 - i][j] << " ";  // Reverse the row index to display with the origin on the bottom left
		}
		cout << endl;
	}

	
}


//Loop through the list of charcater pointers to change their position
void Game::update()
{
	//Use an iterator that increments to loop through every character in the list
	list<GameCharacter*>::const_iterator iter;
	for (iter = lpGameCharacters.begin(); iter != lpGameCharacters.end(); ++iter)
	{
		(*iter)->update();//Call the update() function for each iteration in the GameCharacter list

	}
}

//Function to start a battle
void Game::battle()
{
	
	//cout << "Battle function have been called!"; Test cout statement to ensure function calling
	
	//Loop through the list of GameCharacters
	for (list<GameCharacter*>::const_iterator iter = lpGameCharacters.begin(); iter != lpGameCharacters.end(); ++iter)
	{	
		//Create another enemy pointer object that is equal to the current enemy in the loop
		Enemy* enemy = dynamic_cast<Enemy*>(*iter);

		
		
		
		if (enemy != nullptr) // If the current character is an enemy
		{
			// Check if the player's position matches the enemy's position
			if ( (pPlayer->getxPos() == enemy->getxPos()) && (pPlayer->getyPos() == enemy->getyPos()) )
			{
				//State the player and enemy that are battling
				cout << pPlayer->getName() << " is battling " << enemy->getName() << "!" << endl;
				
				//Give the player the choice to fight or run away
				cout << "What do you want to do, " << pPlayer->getName() << "?" << endl;
				cout << "1. Fight!" << endl;
				cout << "2. Run away (you'll lose health if you choose this)" << endl;
				cin >> input;

				
				switch (input)
				{
					case 1://Player chooses to fight (by inputting 1)
						cout << "Let's fight!! " << endl;

						// Compare health values 

						//if player has more health
						if (pPlayer->getHealth() > enemy->getHealth())
						{
							//Player is given the choice whether to kill the enemy or show mercy (only deduct half their health)
							cout << pPlayer->getName() << " has more health! What do you want to do with " << enemy->getName() << "?" << endl;
							cout << "1. Kill them" << endl;
							cout << "2. Show mercy" << endl;
							cin >> input;

							if (input == 1)//Player chooses to kill enemy
							{
								enemy->killChar(); // Enemy loses and is killed
								cout << enemy->getName() << " has been defeated!" << endl;
								cout << "'HAHA! Justice for my precious cake!'" << endl;
							}
							else //Player chooses to show mercy (remove only half of enemies health)
							{
								//Deduct half the enemy's health and call the changeHealth function
								healthDe = enemy->getHealth()/2;
								enemy->changeHealth(healthDe);

								cout << "Your mercy leaves " << enemy->getName() << " still alive, but their health goes down to " << enemy->getHealth() << endl;
							}
							
							
						}
						else if (pPlayer->getHealth() < enemy->getHealth())//If enemy has more health
						{
							pPlayer->killChar(); // Player loses and is killed
							cout << pPlayer->getName() << " has been defeated!" << endl;
							cout << "'NOOO! First my cake has been destroyed and now me!!!'" << endl;
						}
						else
						{
							// It's a tie if health is equal
							cout << "It's a draw! Both have the same health!" << endl;
						}
						break; // Exit the loop after a battle occurs
					
					case 2://Player chooses to run away (by selecting 2)

						//Choosing to run away, which deducts 30 from the player's health
						cout << "\nYou decide to run away (scaredy cat)" << endl;

						healthDe = pPlayer->getHealth() - 30;
						pPlayer->changeHealth(healthDe);

						cout << "As a result, your health has gone down to: " << pPlayer->getHealth() << endl;

						break;
					default://If the player doesn't choose one of the options, they are killed instantly
						
						cout << "\nUm, that's not one of the options. You must die." << endl;
						pPlayer->killChar();
						break;
				}

				
				
			}
		}
	}
}


//Loop through the list of charcater pointers to output their stats
void Game::stats()
{	
	//Use an iterator that increments to loop through every character in the list
	list<GameCharacter*>::const_iterator iter;
	for (iter = lpGameCharacters.begin(); iter != lpGameCharacters.end(); ++iter)
	{
		(*iter)->stats();//Call the stats() function for each iteration in the GameCharacter list

	}
}


//Function to remove a character from the list if their health is zero
void Game::clean()
{
	list<GameCharacter*>::iterator iter = lpGameCharacters.begin(); // Initialize iterator to the start of the list

	// Loop through the entire character list
	while (iter != lpGameCharacters.end())
	{
		if (!(*iter)->isAlive())  // Check if character is dead
		{
			cout << (*iter)->getName() << " is dead, and will be removed from the game" << endl;

			// Check if the dead character is of type Player
			if (dynamic_cast<Player*>(*iter) != nullptr)
			{
				isOver = true; //isOver becomes true, declarig the end of the game
			}

			delete* iter;  // Free the memory
			iter = lpGameCharacters.erase(iter);  // Remove the pointer from the list

		}
		else
		{
			++iter;  // Only increment if we don't remove to move onto the next character
		}
	}
}

//Function to return the boolean isOver that becomes true if the player is killed
bool Game::getOver()
{ 
	return isOver; 
}

//Function to display a title screen and menu
bool Game::titleMenu()
{
	int input;

	//Player is given choice to play game, view story or view characters
	cout << "Welcome to the chase for the chocolate cake!" << endl;
	cout << "What would you like to do?" << endl;
	cout << "1. Play" << endl;
	cout << "2. Story" << endl;
	cout << "3. Characters" << endl;
	cin >> input;//Take in input


	switch(input)
	{
		case 1://1 will start the game
			return true;//Function returns true to start the game
			break;
		case 2://2 will output the story
			cout << "\nThis is the story" << endl;
			cout << "Terry has baked a delicious chocolate cake and left it on the windowsill to cool" << endl;
			cout << "However, 4 devious creatures sneakily started to munch down the cake!" << endl;
			cout << "Terry caught them in the midst of their heinous act and chased them into the forest" << endl;
			cout << "'GET BACK HERE YOU THIEVES! I SHALL HAVE MY REVENGE!'" << endl;
			cout << "It's now up to Terry (you) to catch and kill all the crooks to avenge his beloved chocolate cake \n" << endl;
			return false;
			break;
		case 3://3 will output character info
			cout << "\nHere are the characters\n" << endl;
			
			cout << "Terry (you): a cheerful chef with a passion for baking and will destroy anyone that dares ruin his craft" << endl;
			
			cout << "Barry: Rambunctious robber with a keen interest in pastries" << endl;
			cout << "Harry: Frivolous fraud with a sweet tooth for chocolate" << endl;
			cout << "Larry: Cunning criminal with a degree in desserts" << endl;
			cout << "Mary:  Rookie in the art of stealing cherished cuisine\n" << endl;
			return false;
			break;
		default://default case for any invalid input
			cout << "Invalid input" << endl;
			return false;
			break;
	}
	
}




