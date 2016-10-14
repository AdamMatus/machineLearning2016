#ifndef _CAR_HPP_
#define _CAR_HPP_

#include <SFML/Graphics.hpp>

#include <array>
#include <chrono>

class Car {
private:
	sf::Vector2f acceleration, velocity, position; //pix for sec
	sf::Vector2f size;
public:
	Car(float acc, sf::Vector2f pos = sf::Vector2f(0,0), sf::Vector2f siz = sf::Vector2f(50,50)); 

	const sf::Vector2f& getVelocity() const
	{
		return velocity;
	}
	const sf::Vector2f& getPosition() const
	{
		return position;
	}
	const sf::Vector2f& getSize() const
	{
		return size;
	}

	sf::Vector2f accelerate(std::chrono::milliseconds quantum_time, const sf::Vector2f& dir, const sf::Vector2f& acc = sf::Vector2f() );

};
#endif
