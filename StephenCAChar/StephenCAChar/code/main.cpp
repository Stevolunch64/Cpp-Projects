#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include <vector>
#include <list>


int main()
{
	// Create a 'Game' object to be used to call the functions to run the game
	Game Play;

	
	//bool that turns false when nighttime occurs (timeleft < 1)
	bool isDay = true;
	
	//Int that decrements after each turn. It is daytime for 5 turns and nightime for 5 turns 
	int timeLeft = 5;

	

	//Call the functions that set up the characters stats including health and speed
	while (!Play.titleMenu());//Keep showing the main menu function until it returns false, meaning the game has started
	Play.init();
	Play.setHealth();
	Play.setSpeed();
	Play.displayBoard();
	Play.render();

	//Run the game in a loop by repeatedly calling the functions in the game object
	cout << " \n Lets Start the Game! \n";
	for (int i = 0; i < 100; i++)
	{
		
		//The update, battle and clean functions are called repeatedly in the loop (to move characters, display the board and battle)
		Play.update();
		Play.battle();
		//Play.stats(); stats function is commented out for gameplay cleanliness, but will work if uncommented
		Play.clean();

		
		//dayTime is decremented after each turn from 5 to 0, then it becomes nighttime
		if(isDay)//isDay is true when it is daytime
		{
			//During the day, the player can see the board and know where everyone is
			Play.render();
			Play.displayBoard();
			
			timeLeft--;
			cout << "\nDay turns remaining: " << timeLeft << "\n" << endl;
			
			//When timeLeft reaches 0, it becomes nightTime (isDay is false) and the timeLeft countdown resets
			if(timeLeft < 1)
			{
				isDay = false;
				timeLeft = 5;
			}
			
		}
		else //The else statement is executed when isDay becomes false (meaning nighttime)
		{
			
			cout << "\nIt is night time now so you can't see anyone!\n" << endl;
			timeLeft--;//dayTime variable keeps getting decremented until 0
			cout << "Night turns remaining: " << timeLeft << endl;
			
			
			//isDay becomes true again after 5 turns in the night
			if (timeLeft < 1)
			{
				isDay = true;
				timeLeft = 5;
				cout << "\nCOCK-A-DOODLE-DOO! It's daytime again!" << endl;
				Play.displayBoard();
			}
		}

		
		
		
		//Checks if the player is dead, ends the game if they are
		if (Play.getOver())
		{
			cout << "YOU DIED! GAME OVER!" << endl;
			break;
		}
		

	}//end of for loop 100 times
	Play.getOver();
	
    
    return 0;
}
