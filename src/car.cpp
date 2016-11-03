#include <cmath>
#include "../inc/car.hpp"

Car::Car(float acc, sf::Vector2f pos, sf::Vector2f siz) :
	quantum_time(std::chrono::milliseconds(25)), 
 	acceleration{acc, acc},
 	velocity{0, 0},
 	position{pos},
	lastPosition{pos},
	start_position{pos},
 	size{siz},
	onFinish{false}
{}

void Car::accelerate(const sf::Vector2f& dir, const sf::Vector2f& acc) //acc is outside force
{
	velocity.x += dir.x*acceleration.x + acc.x;	
	velocity.y += dir.y*acceleration.y + acc.y;	
}

void Car::calculateNewPosition() // call only once in quantum time
{
	lastPosition = position;

	position.x += (velocity.x)* quantum_time.count()/1000;	
	position.y += (velocity.y)* quantum_time.count()/1000;	
}


