#include <cmath>
#include "../inc/car.hpp"

Car::Car(float acc) : acceleration{acc, acc}, velocity{0, 0}, size{50, 50} {}

sf::Vector2f Car::accelerate(std::chrono::milliseconds quantum_time,const sf::Vector2f& dir, const sf::Vector2f& acc) //acc is outside force
{
	velocity.x += (dir.x*acceleration.x + acc.x) * quantum_time.count()/1000;	
	velocity.y += (dir.y*acceleration.y + acc.y) * quantum_time.count()/1000;	

	position.x += (velocity.x + acc.x) * quantum_time.count();	
	position.y += (velocity.y + acc.y) * quantum_time.count();	

	return sf::Vector2f(position.x, position.y);
}


