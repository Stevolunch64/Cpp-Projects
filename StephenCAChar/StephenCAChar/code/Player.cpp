#include "Player.h"
#include <cstdlib>  // For rand()
#include <ctime>    // For time()
#include<iostream> //For input

Player::Player(std::string typeID, int health, int speed, int x, int y, char symbol)
    : GameCharacter()  // Call the GameCharacter constructor
{
    srand(static_cast<unsigned int>(time(0)));//Use the time for random generation
    // Pass the arguments to its superclass' spawn() function
    spawn(typeID, health, speed, x, y, symbol);
}

// Function used to change the player's postion (based on user input)
void Player::update() 
{

    //Char used to move player
    char move;

    //Ask player to input direction
    cout << m_typeID << ", input a char for direction \n";
    cout << "N for North \n";
    cout << "S for South \n";
    cout << "E for East \n";
    cout << "W for West \n";
    cin>>move;
    
    //Move the player by one space based on their input
    switch (move) 
    {
        case 'N': //move up for north (increment y-value)
            m_y++;
            cout << m_typeID << " moved North" << endl;
            break;
        case 'S'://move down for south (decrement y-value)
            m_y--;
            cout << m_typeID << " moved South" << endl;
            break;
        case 'E'://move right for east (increment x-value)
            m_x++;
            cout << m_typeID << " moved East" << endl;
            break;
        case 'W'://move left for west (decrement x-value)
            m_x--;
            cout << m_typeID << " moved West" << endl;
            break;
        default://default case for when a direction is not inputted correctly
            cout << "That is not a direction" << endl;
            break;
    }

    // Check if the player goes beyond the board on the y axis
    if (m_y < 0 || m_y > 9)
    {
        m_y = (m_y < 0) ? 0 : 9;  // Set y to 0 if it's less than 0, or to 9 if it's greater than 9
        m_health -= m_speed * 2;  // Deduct health based on speed
        cout << m_typeID << " hit the y perimeter, health decreased to " << m_health << endl;
    }

    // Check if the player goes beyond the board on the x axis
    if (m_x < 0 || m_x > 9)
    {
        m_x = (m_x < 0) ? 0 : 9;  // Set x to 0 if it's less than 0, or to 9 if it's greater than 9
        m_health -= m_speed * 2;  // Deduct health based on speed
        cout << m_typeID << " hit the x perimeter, health decreased to " << m_health << endl;
    }

}


//Function to randomly generate a health value between 140 and 170
void Player::setHealth()
{
   m_health = rand() % 31 + 140; //140
   cout << m_typeID << "'s health is " << m_health << endl;
}

//Function to randomly generate a speed value between 2 and 4
void Player::setSpeed()
{
    m_speed = rand() % 4 + 2;
    cout << m_typeID << "'s speed is " << m_speed << endl;
}


