#include "GameCharacter.h"
#include <cstdlib> // for rand()

//spawn() function is called when a character object is created
void GameCharacter::spawn(std::string typeID, int health, int speed, int x, int y, char symbol)
{
    m_typeID = typeID;
    m_health = health;
    m_speed = speed;
    m_x = x;
    m_y = y;
    m_symbol = symbol;
}

//function to print out the character's co-ordinates
void GameCharacter::render()
{
   cout << m_typeID << " is at (" << m_x << ", " << m_y << ")" << endl;
}

//function to update the character's position
void GameCharacter::update()
{
    // Virtual function does nothing in the superclass 
}

// function to output all stats relating to the character
void GameCharacter::stats()
{
    cout << "\n" << "Type: " << m_typeID << endl;
    cout << "Health: " << m_health << endl;
    cout << "Speed: " << m_speed << endl;
    cout << "Position: (" << m_x << ", " << m_y << ")" << "\n";
}

//Function to return true if the character is still alive
bool GameCharacter::isAlive() 
{
    return m_health > 0;
}

void GameCharacter::setHealth()
{
    // Virtual function does nothing in the superclass 
}


void GameCharacter::setSpeed()
{
    // Virtual function does nothing in the superclass 
}

//Function to return x position of character
int GameCharacter::getxPos()
{
    return m_x;
}

//Function to return y position of character
int GameCharacter::getyPos()
{
    return m_y;
}

//Function to return health value of character
int GameCharacter::getHealth()
{
    return m_health;
}

//Function to return name of character
std::string GameCharacter::getName()
{
    return m_typeID;
}

//Function to return name of character
char GameCharacter::getSymbol()
{
    return m_symbol;
}

//Function to kill a character by setting their health to zero
void GameCharacter::killChar()
{
    m_health = 0;
}


//Function to change the health value during battle
void GameCharacter::changeHealth(int healthDown)
{
    m_health = healthDown;
}