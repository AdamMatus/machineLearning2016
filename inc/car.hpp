#ifndef _CAR_HPP_
#define _CAR_HPP_

#include <SFML/Graphics.hpp>

#include <array>
#include <chrono>

class Car {
private:
	const std::chrono::milliseconds quantum_time;
	sf::Vector2f acceleration, velocity, position, lastPosition; //pix for sec
	sf::Vector2f start_position;
	sf::Vector2f size;
	bool onFinish;
public:
	Car(float acc, sf::Vector2f pos = sf::Vector2f(0,0), sf::Vector2f siz = sf::Vector2f(50,50)); 

	void markAsFinished() { onFinish = true; }
	bool getFinishState() { return onFinish; }

	const sf::Vector2f& getVelocity() const
	{
		return velocity;
	}
	const sf::Vector2f& getPosition() const
	{
		return position;
	}
	const sf::Vector2f& getLastPosition() const
	{
		return lastPosition;
	}
	const sf::Vector2f& getSize() const
	{
		return size;
	}

	void resetCar()
	{
			onFinish = false;
			position = start_position;
			velocity = sf::Vector2f(0,0);
	}

	void accelerate(const sf::Vector2f& dir, const sf::Vector2f& acc = sf::Vector2f() );
	void calculateNewPosition();

};
#endif
