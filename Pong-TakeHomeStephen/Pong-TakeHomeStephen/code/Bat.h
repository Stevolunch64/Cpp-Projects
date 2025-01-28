#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bat
{
private:
	Vector2f m_Position;

	// A RectangleShape object
	RectangleShape m_Shape;

	float m_Speed = 1000.0f;

	bool m_MovingRight = false;
	bool m_MovingLeft = false;


public:
	Bat(float startX, float startY, Color fillColor);

	FloatRect getPosition();

	RectangleShape getShape();

	void moveLeft();

	void moveRight();

	void stopLeft();

	void stopRight();

	void update(Time dt);

	//Change the height of the bat on the screen
	void changeHeight(float increaser);

	//Set the position of the bat on the screen
	void setPosition(float firstX, float firstY);

	//Change the width and height of the bat
	void changeSize(float width, float height);



};
