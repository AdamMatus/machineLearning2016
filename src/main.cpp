#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>

const auto basic_quantum_time = std::chrono::milliseconds(25);

int main(int argc, char *argv[])
{
	sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "Driving doggo rectangles.");
	mainWindow.setVerticalSyncEnabled(true);

	sf::Vector2<float> doggoSize = sf::Vector2<float>(50,50);
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

	auto frame_time_point = std::chrono::system_clock::now();
	while(mainWindow.isOpen())
	{
		sf::Event event;
		while(mainWindow.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				mainWindow.close();
		}

		sf::Vector2f doggoMovement;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			doggoMovement.y = -5;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			doggoMovement.y = 5;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			doggoMovement.x = 5;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			doggoMovement.x = -5;

		mainWindow.clear(sf::Color::Black);
		
		testDoggo.move(doggoMovement);
		mainWindow.draw(testDoggo);	
		
		mainWindow.display();

		auto diffDuration = basic_quantum_time -  std::chrono::duration_cast<std::chrono::milliseconds>(frame_time_point - std::chrono::system_clock::now());
		std::this_thread::sleep_for(diffDuration);
		frame_time_point = std::chrono::system_clock::now();
	}

	return 0;
}
