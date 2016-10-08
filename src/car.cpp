#include <cmath>
#include "../inc/car.hpp"

Car::Car(float acc, sf::Vector2f pos, sf::Vector2f siz) :
 	acceleration{acc, acc},
 	velocity{0, 0},
 	position{pos},
 	size{siz},
	inCon{false}
{}

sf::Vector2f Car::accelerate(std::chrono::milliseconds quantum_time,const sf::Vector2f& dir, const sf::Vector2f& acc) //acc is outside force
{
	velocity.x += dir.x*acceleration.x + acc.x;	
	velocity.y += dir.y*acceleration.y + acc.y;	

	position.x += (velocity.x + acc.x) * quantum_time.count()/1000;	
	position.y += (velocity.y + acc.y) * quantum_time.count()/1000;	

	return sf::Vector2f(position.x, position.y);
}


