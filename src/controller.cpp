#include <controller.hpp>

sf::Vector2f Controller::getDirInfo() const
{
	return dir;
}

void KeyboardController::move(Car& contextCar)
{
	updateDirInfoFromKeyboard();
	contextCar.accelerate(getDirInfo());
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


