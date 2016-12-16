#include <controller.hpp>

#include "floatfann.h"

sf::Vector2f Controller::getDirInfo() const
{
	return dir;
}

//TODO this polimorfic design has no sense
void KeyboardController::move(Car& contextCar)
{
	updateDirInfoFromKeyboard();
	contextCar.accelerate(getDirInfo());
}
void ANNController::move(Car & contextCar, struct fann *ann, Track & contextTrack)
{
	updateDirInfoFromANN(ann, contextCar, contextTrack);
	contextCar.accelerate(getDirInfo());
}

//TODO
void ANNController::updateDirInfoFromANN(struct fann *ann, Car & contextCar, Track & contextTrack)
{	
		fann_type *calc_out;
		sf::Vector2f context_dir(0,0);
		fann_type input[10];

		CarPredictedMovementInfo normalizedContextCarPMI;
		contextCar.getNormalizedCPMovementInfo(normalizedContextCarPMI,contextTrack);
		input[0] = normalizedContextCarPMI.vectorToFinishBarrier.x;
		input[1] = normalizedContextCarPMI.vectorToFinishBarrier.y;
		input[2] = contextCar.getVelocity().x/contextCar.getAcceleration().x;
		input[3] = contextCar.getVelocity().y/contextCar.getAcceleration().y;
		input[4] = normalizedContextCarPMI.relPosVec1.x;
		input[5] = normalizedContextCarPMI.relPosVec1.y;
		input[6] = normalizedContextCarPMI.relPosVec2.x;
		input[7] = normalizedContextCarPMI.relPosVec2.y;
		input[8] = normalizedContextCarPMI.endVelVersor.x;
		input[9] = normalizedContextCarPMI.endVelVersor.y;

		calc_out = fann_run(ann, input);
		context_dir.x = calc_out[0];
		context_dir.y = calc_out[1];
		std::cout << "__pies__" << std::endl;
		for(int i=0; i<2; i++)
		{
			std::cout << calc_out[i];
			std::cout << " ";
		}
		std::cout << std::endl;

		setDir(context_dir);
}

void KeyboardController::updateDirInfoFromKeyboard()
{
	sf::Vector2f dir;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			dir.y = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::J))
			dir.y = 1;
		else 
			dir.y = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			dir.x = 1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::H))
			dir.x = -1;
		else
			dir.x = 0;

		setDir(dir);
}


