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

Car::Car(const Car& cr) :
	quantum_time{cr.quantum_time},
	acceleration{cr.acceleration},
	velocity{cr.velocity},
	position{cr.position},
	lastPosition{cr.lastPosition},
	start_position{cr.start_position},
	size{cr.size},
	onFinish{cr.onFinish}
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

void Car::getCPMovementInfo(CarPredictedMovementInfo& cpmi, Track& contextTrack) const
{
	Car contextCar(*this);	

	int cycle_index = 0;
	sf::Vector2f lastPosition= contextCar.getPosition();

	cycle_index +=	contextTrack.trackMoveUntilBarrier(contextCar, max_size_of_sight);
	cpmi.relPosVec1.x = contextCar.getPosition().x - lastPosition.x;
	cpmi.relPosVec1.y = contextCar.getPosition().y - lastPosition.y;

	lastPosition.x = contextCar.getPosition().x;
	lastPosition.y = contextCar.getPosition().y;

	contextTrack.trackMoveUntilBarrier(contextCar, max_size_of_sight - cycle_index);
	cpmi.relPosVec2.x = contextCar.getPosition().x - lastPosition.x;
	cpmi.relPosVec2.y = contextCar.getPosition().y - lastPosition.y;
	
	//computing end velocity versor
	auto endVelVer = contextCar.getVelocity();
	auto velAbsValue = std::sqrt(std::pow(endVelVer.x,2)+std::pow(endVelVer.y,2));
	endVelVer.x /= velAbsValue;
 	endVelVer.y /= velAbsValue;	
	cpmi.endVelVersor = endVelVer;

	cpmi.vectorToFinishBarrier = contextTrack.getVectorToLastFinishBarrier(*this);
}
