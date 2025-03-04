#include "Enemy.h"
#include <cstdlib>  // For rand()
#include <ctime>    // For time()


Enemy::Enemy(std::string typeID, int health, int speed, int x, int y, char symbol)
    : GameCharacter()  // Call the GameCharacter constructor
{
    srand(static_cast<unsigned int>(time(0)));//Use the time for random generation
    // Pass the arguments to the superclass spawn() function
    spawn(typeID, health, speed, x, y, symbol);
}

// Function used to move the enemy
void Enemy::update() 
{
    // Generate a random value between 1 and 10
    int randy = rand() % 10 + 1;

    //If the value for 'randy' is less or equal to 8, enemy moves 1 up or down
    if (randy <= 8) 
    {
        // A random value of 1 or -1 is added to the y value of the enemy to move them up or down 
        int upDown = rand() % 2 == 0 ? 1 : -1;  
        m_y += upDown;  //Add the random value to the y co-ordinate
        cout << m_typeID << "'s y-cordinate moved to " << m_y << endl;
    }
    else//Enemy does not move if a value of 9 or 10 is generated
    {
        cout << m_typeID << " does not move" << endl;
    }
    

    
    // Check if the enemy goes beyond the board on the y axis
    if (m_y < 0 || m_y > 9)
    {
        m_y = (m_y < 0) ? 0 : 9;  // Set y to 0 if it's less than 0, or to 9 if it's greater than 9
        m_health -= m_speed * 3;  // Deduct health based on speed
        cout << m_typeID << " hit the y perimeter, health decreased to " << m_health << endl;
    }
}

//Function to randomly generate a health value between 90 and 150
void Enemy::setHealth()
{
    m_health = rand() % 61 + 90;
    cout << m_typeID << "'s health is " << m_health << endl;
}

//Function to randomly generate a speed value between 1 and 3
void  Enemy::setSpeed()
{
   m_speed = rand() % 3 + 1;
   cout << m_typeID << "'s speed is " << m_speed << endl;
}
