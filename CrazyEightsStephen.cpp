//Name: Stephen Lynch
//Date: 22/03/2024
//Function : Create a crazy eights type game in cpp


#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;



// Function to generate a random integer between min and max (inclusive)
//This is used to intially create the player(s) cards
int makeArray(int min, int max) 
{
    return min + rand() % (max - min + 1);
}


//Function for the main game for player 1
void P1Game(int array1[], int arraySize, int& middle)
{
		
	// Prints out P1's initial array (hand)
	cout << "Player 1's cards: ";
	for (int i = 0; i < arraySize; ++i) 
	{
		cout << array1[i] << " ";
	}


	// Asks player for action
	cout << "The number in the middle is: " << middle << endl;
	cout << "If you have a card that you can use, enter it here" << endl;
	cout << "Otherwise, enter a number greater  than 5" << endl;


	int drop;
	cin >> drop;


	// Check if the input is in the array
	bool found = false;

	//Its a loop because it checks if the inputted number is in each number in the array
	for (int i = 0; i < arraySize; ++i) 
	{
		// This statement is executed if the player's card is in the middle
		if ( (array1[i] == drop) && ( (drop == middle) || (drop % 2 == 0) || (drop == 3) ) ) 
		{
			found = true;
			
			//The matching number is removed and becomes zero
			middle = 1 + std::rand() % 5;
			
			array1[i] = 0; 
			break; //Break is used in the loop to exit early, and not loop again if the condition is met
		}
	}


	//This statement executes if the user input is NOT in the array, meaning it wont be executed if the bool found is true
	// New concept - You can declare a switch statement like this instead of found = false for example
	if (!found) 
	{	
		//A new number is added to the array (by changing a zero or 5 value)
		cout << "Card not found in the hand. Adding a new random card." << endl;
		int newNumber = makeArray(1, 5);
		cout << "New card added: " << newNumber << endl;
		for (int i = 0; i < arraySize; ++i) 
		{
			if ( (array1[i] == 0) || (array1[i] = 5) ) 
			{
				array1[i] = newNumber;
				break;
			}
		}
	} 
	else 
	{
		cout << "Card removed from the player's hand." << endl;
	}


	// Check if all numbers are removed
	bool allGone = true;

	for (int i = 0; i < arraySize; ++i) 
	{
		if (array1[i] != 0) 
		{
			allGone = false;
			break;
		}
	}

	// If allGone is true
	if (allGone) 
	{
		cout << "Player 1 wins! All of their cards are gone" << endl;
		
		// NEW CONCEPT - A cpp program can be exited with the use of the exit() function
		exit(0);
		
	}
			
					
}


//Function for the main game for player 2
void P2Game(int array2[], int arraySize, int& middle)
{
		
	//Loop continuously asks for input until all cards are removed
		

	// Prints out P2's initial array (hand)
	cout << "Player 2's cards: ";
	for (int i = 0; i < arraySize; ++i) 
	{
		cout << array2[i] << " ";
	}
	
	
	// Asks player for action
	cout << "The number in the middle is: " << middle << endl;
	cout << "If you have a card that you can use, enter it here" << endl;
	cout << "Otherwise, enter a number greater  than 5" << endl;
	
	
	int drop;
	cin >> drop;

		
		// Check if the input is in the array
		bool found = false;
		
		//Its a loop because it checks if the inputted number is in each number in the array
		for (int i = 0; i < arraySize; ++i) 
		{
			// This statement is executed if the player's card is in the middle
			if ( (array2[i] == drop) && ( (drop == middle) || (drop % 2 == 0) || (drop == 3) ) ) 
			{
				found = true;
				
				//The matching number is removed and becomes zero
				middle = 1 + std::rand() % 5;
				
				array2[i] = 0; 
				break;
			}
		}

		
		//This statement executes if the user input is NOT in the array, meaning it wont be executed if the bool found is true
		//New concept - for If statments, you can write bools as just "!found" and not as "found == false"
		if (!found) 
		{	
			//A new number is added to the array (by changing a zero or 5 value)
			cout << "Card not found in the hand. Adding a new random card." << endl;
			int newNumber = makeArray(1, 5);
			cout << "New card added: " << newNumber << endl;
			for (int i = 0; i < arraySize; ++i) 
			{
				if ( (array2[i] == 0) || (array2[i] = 5) ) 
				{
					array2[i] = newNumber;
					break;
				}
			}
		} 
		else 
		{
			cout << "Card removed from the player's hand." << endl;
		}


		// Check if all numbers are removed
		bool allGone = true;
		
		for (int i = 0; i < arraySize; ++i) 
		{
			if (array2[i] != 0) 
			{
				allGone = false;
				break;
			}
		}

		if (allGone) 
		{
			cout << "Player 2 wins! All of their cards are gone" << endl;
			exit(0);
			
		}
		
					
}


//Function for the main game for the computer
void ComGame(int array3[], int arraySize, int& middle)
{
		
	//Loop continuously asks for input until all cards are removed
		
	// Prints out the computer's initial array (hand)
	cout << "Computer's cards: ";
	for (int i = 0; i < arraySize; ++i) 
	{
		cout << array3[i] << " ";
	}
	
	
	// Asks player for action
	cout << "The number in the middle is: " << middle << endl;
	
	
	

		
		// Check if the input is in the array
		bool found = false;
		
		//Its a loop because it checks if the inputted number is in each number in the array
		for (int i = 0; i < arraySize; ++i) 
		{
			// This statement is executed if the player's card is in the middle
			if ((array3[i] == middle) || (array3[i] % 2 == 0) || (array3[i] == 3) ) 
			{
				found = true;
				
				//The matching number is removed and becomes zero
				middle = 1 + std::rand() % 5;
				
				array3[i] = 0; 
				break;
			}
		}

		
		//This statement executes if the user input is NOT in the array, meaning it wont be executed if the bool found is true
		if (!found) 
		{	
			//A new number is added to the array (by changing a zero or 5 value)
			cout << "Computer doesnt have a suitable card. Adding a new random card." << endl;
			int newNumber = makeArray(1, 5);
			cout << "New card added: " << newNumber << endl;
			for (int i = 0; i < arraySize; ++i) 
			{
				if ( (array3[i] == 0) || (array3[i] = 5) ) 
				{
					array3[i] = newNumber;
					break;
				}
			}
		} 
		else 
		{
			cout << "Card removed from the computer's hand." << endl;
		}


		// Check if all numbers are removed
		bool allGone = true;
		
		for (int i = 0; i < arraySize; ++i) 
		{
			if (array3[i] != 0) 
			{
				allGone = false;
				break;
			}
		}

		if (allGone) 
		{
			cout << "The computer wins! All of their cards are gone" << endl;
			exit(0);
		}
	
					
}


int main()
{
    string name; //Name inputted at start of program
    int choice; //First menu choice
    bool menu = true; //(used to loop menu in case of incorrect input)
	const int arraySize = 5; // Make the array size constant, so it doesnt go above 5
    int array1[arraySize]; //Cards for Player1
	int array2[arraySize]; //Cards for Player2
	int array3[arraySize]; //Cards for Computer
	int turn = 0; //Amount of turns the game has 
	double choice2; //Menu option to play against a player or computer

    // New concept: random number generator based on the time (for true randomness) 
    srand(static_cast<unsigned>(time(nullptr)));
	
	
    
	// middle card is a random number between 1 and 5, using a function bult into c++
	int middle = 1 + std::rand() % 5;
	
	//Player's name is asked for
	cout << "Enter your name: ";
    cin >> name;

    cout << "Welcome to Crazy Eights, " << name << "!" << endl;

	//Menu loops until game starts or exited
	//New concept - In a while loop, you can just write the name of the bool so it keeps looping until it becomes true/false
    while (menu) 
    {
        cout << "What do you want to do?" << endl;
        cout << "1. Play Game" << endl;
        cout << "2. Read Instructions" << endl;
        cout << "3. Check Leaderboard" << endl;
        cout << "4. Quit" << endl;
        cin >> choice;

        switch (choice)
        {
			//Where the main game takes place
            case 1:
			
			//Player gets choice to play against another player or computer
			cout << "Who do you want to play against?" << endl;
			cout << "1. VS 2 Player" << endl;
			cout << "2. VS Computer" << endl;
			cin >> choice2;
			
			if(choice2 == 1)
			{	
				// 2 Player game chosen
				 cout << "Let's Play 2 Players!" << endl;
				
				// Fill in Player 1's cards with random integers between 1 and 5
				for (int i = 0; i < arraySize; ++i) 
				{
					array1[i] = makeArray(1, 5);
				}
				
				
				// Fill in Player 2's cards with random integers between 1 and 5
				for (int i = 0; i < arraySize; ++i) 
				{
					array2[i] = makeArray(1, 5);
				}
                
				
				//Game asks for input from both players 10 times each
				do
				{
					turn++;	
					P1Game(array1, arraySize, middle);
					
					P2Game(array2, arraySize, middle);
					
				
				}while (turn < 11);
				
				
				//The game is a draw after each player gets 10 turns
				if(turn >= 9)
				{
					cout << "Time's up! It's a draw!" << endl;
				}
				
				
				menu = false; // Set menu to false to exit the loop
                
				break;

			}
			else if(choice2 == 2)
			{
				cout << "Let's Play VS COM!" << endl;
				
				// Fill in Player 1's cards with random integers between 1 and 5
				for (int i = 0; i < arraySize; ++i) 
				{
					array1[i] = makeArray(1, 5);
				}
				
				
				// Fill in the computer's cards with random integers between 1 and 5
				for (int i = 0; i < arraySize; ++i) 
				{
					array3[i] = makeArray(1, 5);
				}
                
				
				//Game asks for input from the player 10 times each
				do
				{
					turn++;	
					P1Game(array1, arraySize, middle);
					ComGame(array3, arraySize, middle);
					
				
				}while (turn < 11);
				
				
				if(turn >= 9)
				{
					cout << "Time's up! It's a draw!" << endl;
				}
				
				
				menu = false; // Set menu to false to exit the loop
                
				break;

			}
               
            
			
			
			//This case explains the game's rules
			case 2:
                cout << "Here's how to play this modified version of Crazy Eights." << "\n" << endl;
                cout << "A random number is drawn for the middle card." << endl;
                cout << "All players start with 5 cards with numbers from 1 to 5." << endl;
                cout << "If one of your cards matches the middle card , is an even number or if it's 3, place it." << endl;
				cout << "After placing down a card, the value of the middle card randomly changes" << endl;
                cout << "Otherwise, pick up another card." << endl;
                cout << "The game ends when a player has no cards left." << endl;
				cout << "Alternativley, the game becomes a draw if neither players gets rid of all their cards after 10 turns each." << "\n"  << endl;
                break;

			//This case showcases the leaderboard
            case 3:
                cout << "1st: Mary" << endl;
                cout << "2nd: Harry" << endl;
                cout << "3rd: Paul" << endl;
                break;

			//This case exists the game
            case 4:
                cout << "Game exited." << endl;
                menu = false; // Set menu to false to exit the loop
                break;
			//This case displays after an incorrect menu input
            default:
                cout << "Invalid choice. Please select a valid option." << endl;
        }
    }
	
	cout << "END OF CODE" <<endl;

    return 0;
}



