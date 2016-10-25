#include <printer.hpp>
#include <controller.hpp>

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

	sf::RectangleShape finishRect;
	do{ //TODO add thread or smth
		finishRect = mouseDrawingBarriersDetection();
	} while(finishRect.getSize().x == 0 || finishRect.getSize().y == 0);
	contextTrack.add_finish_barrier(finishRect);

	while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		auto barrierRect = mouseDrawingBarriersDetection();
		if(barrierRect.getSize().x > 0 && barrierRect.getSize().y > 0)
			contextTrack.add_barrier(barrierRect);

		//graphics
		mainWindow.clear(sf::Color::Black);
		drawBarriers(contextTrack);
		mainWindow.display();
		waitForNextFrame();
		//
	}

	return;
}

sf::RectangleShape Printer::mouseDrawingBarriersDetection()
{
	sf::RectangleShape barrierRect(sf::Vector2f(0, 0));
	sf::Vector2i pressed_barrier_pos(0,0);
	bool drawingBarrierNotEnded = false;

	do
	{
		while(mainWindow.pollEvent(event))
		{
			if( event.type == sf::Event::Closed )  
			{
				mainWindow.close();
				break;
			}
			else if(event.type == sf::Event::MouseButtonPressed)
			{
				if(event.mouseButton.button == sf::Mouse::Left)
				{
					pressed_barrier_pos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
					drawingBarrierNotEnded = true;
				}
			}
			else if( event.type == sf::Event::MouseButtonReleased )
			{
				if(event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2f xCon;
					sf::Vector2f yCon;
					//xCons
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

					//yCons
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
				barrierRect.setPosition(xCon.x, yCon.x);
				barrierRect.setSize(sf::Vector2f(xCon.y-xCon.x,yCon.y-yCon.x));	
				drawingBarrierNotEnded = false;	
				}
			}
		} // end off polling events
	}while(drawingBarrierNotEnded);

	return barrierRect;
}

void Printer::drawBarriers(const Track& contextTrack)
{
	sf::RectangleShape rs(sf::Vector2f(0,0));
	rs.setFillColor(sf::Color::Red);
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

	KeyboardController manualController;	

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

		//###FINISH###
		if(contextCar.getFinishState())
		{
			contextCar.resetCar();
			
			sf::Text finishInfoText;
			finishInfoText.setFont(arial);
			finishInfoText.setColor(sf::Color::Blue);
			finishInfoText.setString(std::string("FINISHED"));
			finishInfoText.setCharacterSize(30UL);
			finishInfoText.setPosition(500,500);

			while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				mainWindow.clear(sf::Color::Black);
				drawBarriers(contextTrack);	
				drawCar(contextCar);
				mainWindow.draw(finishInfoText);
				mainWindow.display();
				waitForNextFrame();
			}
		}
		//###~FINISH###

		//###computations###
		contextTrack.trackMove(contextCar);
		manualController.move(contextCar);	

		//### TEXT ### /TODO
		std::string contextCarMesg  = "Speed of contextCar: " + std::to_string(contextCar.getVelocity().x) + "x ";
	 	contextCarMesg += std::to_string(contextCar.getVelocity().y) + "y" + '\n';
		contextCarMesg += "Position of contextCar: " + std::to_string(contextCar.getPosition().x) + "x ";
		contextCarMesg += std::to_string(contextCar.getPosition().y) + "y";

		contextCarInfoText.setString(contextCarMesg);
		contextCarInfoText.setPosition(10,50);
		//### ~TEXT ###

		mainWindow.clear(sf::Color::Black);
		mainWindow.draw(contextCarInfoText);
		drawBarriers(contextTrack);	
		drawCar(contextCar);
		mainWindow.display();

		waitForNextFrame();
	}
}

