#ifndef _CAR_HPP_
#define _CAR_HPP_

#include <SFML/Graphics.hpp>

#include <array>
#include <chrono>

#include <track.hpp>

class Track;

struct CarPredictedMovementInfo;

class Car {
public:
	Car(float acc, sf::Vector2f pos = sf::Vector2f(0,0), sf::Vector2f siz = sf::Vector2f(50,50)); 
	Car(const Car&);

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
	const sf::Vector2f& getAcceleration() const
	{
		return acceleration;
	}

	void resetCar()
	{
			onFinish = false;
			position = start_position;
			velocity = sf::Vector2f(0,0);
	}

	void accelerate(const sf::Vector2f& dir, const sf::Vector2f& acc = sf::Vector2f() );
	void calculateNewPosition();
	void getCPMovementInfo(CarPredictedMovementInfo& ,const Track&) const; 
	void getNormalizedCPMovementInfo(CarPredictedMovementInfo& contextCarPMI,const Track& contextTrack) const;

	void setStartPosition(const sf::Vector2f& sp)
	{
		start_position = sp;
	}

private:
	static const int max_size_of_sight = 50; // maximium quantums of time for prediction
	const std::chrono::milliseconds quantum_time;
	sf::Vector2f acceleration, velocity, position, lastPosition; //pix for sec
	sf::Vector2f start_position;
	sf::Vector2f size;
	bool onFinish;

	const float max_vel; //speed limit

}; //~Car

struct CarPredictedMovementInfo
{
	sf::Vector2f relPosVec1;
	sf::Vector2f relPosVec2;
	sf::Vector2f endVelVersor;
	sf::Vector2f vectorToFinishBarrier;
};

#endif
