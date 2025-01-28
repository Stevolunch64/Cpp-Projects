#include "Ball.h"

// This the constructor function
Ball::Ball(float startX, float startY, float speed, Color fillColor)
{
	m_Position.x = startX;
	m_Position.y = startY;

	m_Shape.setSize(sf::Vector2f(10, 10));
	m_Shape.setPosition(m_Position);
	m_Shape.setFillColor(fillColor);

}

FloatRect Ball::getPosition()
{
	return m_Shape.getGlobalBounds();
}

RectangleShape Ball::getShape()
{
	return m_Shape;
}

float Ball::getXVelocity()
{
	return m_DirectionX;
}

void Ball::reboundSides()
{
	m_DirectionX = -m_DirectionX;
}

void Ball::reboundBatOrTop()
{
	m_DirectionY = -m_DirectionY;

}

void Ball::reboundBottom()
{
	m_Position.y = -50;
	m_Position.x = 500;
	m_DirectionY = -m_DirectionY;
}

void Ball::update(Time dt)
{
	// Update the ball position variables
	m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
	m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();

	// Move the ball and the bat
	m_Shape.setPosition(m_Position);
}

void Ball::setSpeed(float speed)//Allows the user to set the speed of ball
{
	m_Speed = speed;
}

void Ball::changeSpeed(float multiplier) //Allows the user to change the speed of ball
{
	m_Speed = m_Speed * multiplier;
}

//Allows the user to set the ball position
void Ball::setPosition(float firstX, float firstY) 
{
	m_Position.x = firstX;
	m_Position.y = firstY;
	m_Shape.setPosition(firstX, firstY);
}


//Returns the value of the speed of the ball
float Ball::getSpeed()
{
	return m_Speed;
}