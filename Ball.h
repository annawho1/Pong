#pragma once
#include<SFML/Graphics.hpp>



class Ball {
private:
	sf::Vector2f m_Position;
	sf::RectangleShape m_Shape;
	float m_Speed = 400.0f;
	float m_DirectionX = .2f;
	float m_DirectionY = .2f;
public:
	Ball(float startX, float startY);
	sf::FloatRect getPosition();
	sf::RectangleShape getShape();
	float getXVelocity();
	void reboundSides();
	void reboundBatOrTop();
	void reboundBottom();
	void resetSpeed();
	void update(sf::Time dt);
};