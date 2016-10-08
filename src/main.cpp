#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include "../inc/car.hpp"

const auto basic_quantum_time = std::chrono::milliseconds(25);

int main(int argc, char *argv[])
{
	sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "Driving doggo rectangles.");
	mainWindow.setVerticalSyncEnabled(true);

	Car doggo(5);

	sf::RectangleShape testDoggo(doggo.getSize());
	testDoggo.setFillColor(sf::Color::Red);
	
	sf::Vector2<float> doggoStartPos;
	doggoStartPos.x	= static_cast<float>(mainWindow.getSize().x);
	doggoStartPos.y	= static_cast<float>(mainWindow.getSize().y);
	doggoStartPos.x /= 2;
	doggoStartPos.x -= doggo.getSize().x/2;
	doggoStartPos.y /= 2;
	doggoStartPos.y -= doggo.getSize().y/2;
	testDoggo.setPosition(doggoStartPos); 
	auto frame_time_point = std::chrono::system_clock::now();
	while(mainWindow.isOpen())
	{
		sf::Event event;
		while(mainWindow.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				mainWindow.close();
		}

		sf::Vector2f doggoDir;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			doggoDir.y = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			doggoDir.y = 1;
		else 
			doggoDir.y = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			doggoDir.x = 1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			doggoDir.x = -1;
		else
			doggoDir.x = 0;

		sf::Vector2f newPosition = doggo.accelerate(basic_quantum_time, doggoDir);

		mainWindow.clear(sf::Color::Black);
		
		testDoggo.setPosition(newPosition);
		mainWindow.draw(testDoggo);	
		
		mainWindow.display();

		auto diffDuration = basic_quantum_time -  std::chrono::duration_cast<std::chrono::milliseconds>(frame_time_point - std::chrono::system_clock::now());
		std::this_thread::sleep_for(diffDuration);
		frame_time_point = std::chrono::system_clock::now();
	}

	return 0;
}
