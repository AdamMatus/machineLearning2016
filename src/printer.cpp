#include "../inc/printer.hpp"
#include <chrono>
#include <thread>

//only constructor
Printer::Printer(unsigned int width, unsigned int hight):
	mainWindow(sf::VideoMode(width, hight), "Driving doggo rectangles.")	
{
	mainWindow.setVerticalSyncEnabled(true);
}

void Printer::letUserDrawBarriers(Track& contextTrack)
{
	sf::Vector2i pressed_barrier_pos(0,0);
	while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		while(mainWindow.pollEvent(event))
		{
			if( event.type == sf::Event::Closed )  
			{
				mainWindow.close();
				return;
			}
			else if(event.type == sf::Event::MouseButtonPressed)
			{
				if(event.mouseButton.button == sf::Mouse::Left)
					pressed_barrier_pos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
			}
			else if( event.type == sf::Event::MouseButtonReleased )
			{
				if(event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2f xCon;
					sf::Vector2f yCon;
					if(event.mouseButton.x > pressed_barrier_pos.x)
					{
						xCon.x = pressed_barrier_pos.x;
						xCon.y = event.mouseButton.x;
					}
					else
					{
						xCon.x = event.mouseButton.x;
						xCon.y = pressed_barrier_pos.x;
					}

					if(event.mouseButton.y > pressed_barrier_pos.y)
					{
						yCon.x = pressed_barrier_pos.y;
						yCon.y = event.mouseButton.y;
					}
					else
					{
						yCon.x = event.mouseButton.y;
						yCon.y = pressed_barrier_pos.y;
					}

					contextTrack.add_barrier(xCon, yCon);
				}
			}
		} // end off polling events

		//graphics
		mainWindow.clear(sf::Color::Black);
		drawBarriers(contextTrack);
		mainWindow.display();
		waitForNextFrame();
		//
	}

	return;
}

void Printer::drawBarriers(const Track& contextTrack)
{
	sf::RectangleShape rs(sf::Vector2f(0,0));
	rs.setFillColor(sf::Color::Blue);
	while(contextTrack.getNextRectToDraw(rs))
		mainWindow.draw(rs);
}

void Printer::waitForNextFrame()
{
	static auto frame_time_point = std::chrono::system_clock::now();
	
	auto diffDuration = basic_quantum_time -  std::chrono::duration_cast<std::chrono::milliseconds>(frame_time_point - std::chrono::system_clock::now());
	std::this_thread::sleep_for(diffDuration);
	frame_time_point = std::chrono::system_clock::now();
}

void Printer::testPoll(Track& contextTrack, Car& contextCar)
{

	if(!arial.loadFromFile("arial.ttf"))
	{
		return;
	}
	sf::Text contextCarInfoText;
	contextCarInfoText.setFont(arial);
	contextCarInfoText.setCharacterSize(24);
	contextCarInfoText.setColor(sf::Color::White);

	while(mainWindow.isOpen())
	{
		while(mainWindow.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				mainWindow.close();
		}

		sf::Vector2f doggoDir;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			doggoDir.y = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::J))
			doggoDir.y = 1;
		else 
			doggoDir.y = 0;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			doggoDir.x = 1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::H))
			doggoDir.x = -1;
		else
			doggoDir.x = 0;


		contextTrack.trackMove(contextCar);
		contextCar.accelerate(basic_quantum_time, doggoDir);

		std::string contextCarMesg  = "Speed of contextCar: " + std::to_string(contextCar.getVelocity().x) + "x ";
	 	contextCarMesg += std::to_string(contextCar.getVelocity().y) + "y" + '\n';
		contextCarMesg += "Position of contextCar: " + std::to_string(contextCar.getPosition().x) + "x ";
		contextCarMesg += std::to_string(contextCar.getPosition().y) + "y";

		contextCarInfoText.setString(contextCarMesg);
		contextCarInfoText.setPosition(10,50);

		mainWindow.clear(sf::Color::Black);
		
	
		mainWindow.draw(contextCarInfoText);
		drawBarriers(contextTrack);	
		drawCar(contextCar);
		mainWindow.display();

		waitForNextFrame();
	}

}
