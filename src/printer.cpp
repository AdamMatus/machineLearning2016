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

bool Printer::letUserDrawBarriers(Track& contextTrack) //TODO exceptions
{

	sf::RectangleShape finishRect;
	do{ 
		finishRect = mouseDrawingBarriersDetection();
		doBarrierGraphicsAndEndFrame(contextTrack);
		
	} while(finishRect.getSize().x == 0 || finishRect.getSize().y == 0);
	contextTrack.add_finish_barrier(finishRect);

	while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		auto barrierRect = mouseDrawingBarriersDetection();
		if(barrierRect.getSize().x > 0 && barrierRect.getSize().y > 0)
			contextTrack.add_barrier(barrierRect);

		doBarrierGraphicsAndEndFrame(contextTrack);
	}
	return false;
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
				break; //TODO throw excteption
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

void Printer::drawCarInfo(const Car& contextCar, const CarPredictedMovementInfo& cpmi)
{
	sf::Text carInfoText;

//### TEXT ### /TODO
	carInfoText.setFont(arial);
	carInfoText.setCharacterSize(24);
	carInfoText.setColor(sf::Color::Red);

	std::string carMesg = 
						"Speed of Car: " + std::to_string(contextCar.getVelocity().x)+"x "+			//
						std::to_string(contextCar.getVelocity().y) + "y" + '\n' + 							//
						"Position of Car: " + std::to_string(contextCar.getPosition().x) +"x "+	//
						std::to_string(contextCar.getPosition().y) + "y" + '\n'+								//
						"R1 predict vec is: " + std::to_string(cpmi.relPosVec1.x) + "x " +			//
						std::to_string(cpmi.relPosVec1.y) + "y" + '\n' +												//
						"R2 predict vec is: " + std::to_string(cpmi.relPosVec2.x) + "x " +			//
						std::to_string(cpmi.relPosVec2.y) + "y" + '\n' +												//
						"End veloc versor is: " + std::to_string(cpmi.endVelVersor.x) + "x " +	//
						std::to_string(cpmi.endVelVersor.y) + "y" + '\n' 
						;
	

	carInfoText.setString(carMesg);
	carInfoText.setPosition(0,0);
//### ~TEXT ###
	mainWindow.draw(carInfoText);

	sf::Vertex line[] = 
	{
		sf::Vertex(sf::Vector2f(contextCar.getPosition().x, contextCar.getPosition().y)),
		sf::Vertex(sf::Vector2f(contextCar.getPosition().x + cpmi.relPosVec1.x, contextCar.getPosition().y + cpmi.relPosVec1.y))
	};

	mainWindow.draw(line, 2, sf::Lines);

	line[0] = line[1]; 
	line[1] = sf::Vertex(sf::Vector2f(	line[0].position.x + cpmi.relPosVec2.x,
																			line[0].position.y + cpmi.relPosVec2.y));

	mainWindow.draw(line, 2, sf::Lines);
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
	CarPredictedMovementInfo contextCarPMI{	sf::Vector2f(50,50),
																					sf::Vector2f(0,0),
																					sf::Vector2f(0,0)};

	if(!arial.loadFromFile("arial.ttf"))
	{
		return;
	}
	sf::Text contextCarInfoText;


	while(mainWindow.isOpen())
	{
		if( isWindowClosed() ) return;

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
				if( isWindowClosed() ) return;	

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
		contextCar.calculateNewPosition();
		//### ~computations ###
		
		//### car info
		contextCar.getCPMovementInfo( contextCarPMI, contextTrack);	
		//### ~car info

		mainWindow.clear(sf::Color::Black);
		drawBarriers(contextTrack);	
		drawCar(contextCar);
		drawCarInfo(contextCar, contextCarPMI);
		mainWindow.display();

		waitForNextFrame();
	}
}

