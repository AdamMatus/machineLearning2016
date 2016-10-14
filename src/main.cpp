#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <thread>
#include <string>
#include <chrono>
#include "../inc/car.hpp"
#include "../inc/track.hpp"

const auto basic_quantum_time = std::chrono::milliseconds(25);

int main(int argc, char *argv[])
{
	auto winSize = sf::Vector2u(1400,900);
	sf::RenderWindow mainWindow(sf::VideoMode(winSize.x, winSize.y), "Driving doggo rectangles.");
	mainWindow.setVerticalSyncEnabled(true);

	sf::Font arial;
	if(!arial.loadFromFile("arial.ttf"))
	{
		return -1;
	}
	sf::Text doggoInfoText;
	doggoInfoText.setFont(arial);
	doggoInfoText.setCharacterSize(24);
	doggoInfoText.setColor(sf::Color::White);

	
	Track mainTrack(winSize, basic_quantum_time);

	auto testBarrier = sf::RectangleShape(sf::Vector2f(100, 50));
	testBarrier.setPosition(200,300);
	testBarrier.setFillColor(sf::Color::Green);

	mainTrack.add_barrier(testBarrier);

	auto doggoSize = sf::Vector2f(50,50);

	sf::RectangleShape testDoggo(doggoSize);
	testDoggo.setFillColor(sf::Color::Red);
	
	sf::Vector2<float> doggoStartPos;
	doggoStartPos.x	= static_cast<float>(mainWindow.getSize().x);
	doggoStartPos.y	= static_cast<float>(mainWindow.getSize().y);
	doggoStartPos.x /= 2;
	doggoStartPos.x -= doggoSize.x/2;
	doggoStartPos.y /= 2;
	doggoStartPos.y -= doggoSize.y/2;
	testDoggo.setPosition(doggoStartPos); 

	Car doggo(50, doggoStartPos, doggoSize);

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


		mainTrack.trackMove(doggo);
		doggo.accelerate(basic_quantum_time, doggoDir);
		auto newPosition = doggo.getPosition();

		std::string doggoMesg  = "Speed of doggo: " + std::to_string(doggo.getVelocity().x) + "x ";
	 	doggoMesg += std::to_string(doggo.getVelocity().y) + "y" + '\n';
		doggoMesg += "Position of doggo: " + std::to_string(newPosition.x) + "x ";
		doggoMesg += std::to_string(newPosition.y) + "y";

		doggoInfoText.setString(doggoMesg);

		mainWindow.clear(sf::Color::Black);
		
		testDoggo.setPosition(newPosition);

		mainWindow.draw(doggoInfoText);
		mainWindow.draw(testBarrier);
		mainWindow.draw(testDoggo);	
		
		mainWindow.display();

		auto diffDuration = basic_quantum_time -  std::chrono::duration_cast<std::chrono::milliseconds>(frame_time_point - std::chrono::system_clock::now());
		std::this_thread::sleep_for(diffDuration);
		frame_time_point = std::chrono::system_clock::now();
	}

	return 0;
}
