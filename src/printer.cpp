#include <printer.hpp>
#include <controller.hpp>

#include <chrono>
#include <thread>

//TODO
#include <floatfann.h>

//only constructor
Printer::Printer(unsigned int w, unsigned int h):
	mainWindow(sf::VideoMode(w, h), "Driving doggo rectangles."),
	width(w),
	hight(h)	
{
	mainWindow.setVerticalSyncEnabled(true);

	if(!arial.loadFromFile("aux/arial.ttf"))
	{
		return;
	}
}

bool Printer::letUserDrawBarriers(Track& contextTrack) //TODO exceptions
{

	sf::RectangleShape finishRect;
	do{ 
		finishRect = mouseDrawingBarriersDetection();
		doBarrierGraphicsAndEndFrame(contextTrack);
		
	} while(finishRect.getSize().x == 0 || finishRect.getSize().y == 0);
	contextTrack.add_finish_barrier(finishRect);

	letUserDrawSingleBarrier(contextTrack); 
	return false;
}

void Printer::letUserDrawSingleBarrier(Track& contextTrack)
{
	while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		auto barrierRect = mouseDrawingBarriersDetection();
		if(barrierRect.getSize().x > 0 && barrierRect.getSize().y > 0)
			contextTrack.add_barrier(barrierRect);
		doBarrierGraphicsAndEndFrame(contextTrack);
	}
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

void Printer::drawTerminal(const Terminal& term)
{
	sf::RectangleShape terminalRect = term.getRectToDraw();
	mainWindow.draw(terminalRect);

	sf::Text textToDraw;
	textToDraw.setFont(arial);
	while( term.getNextTextToDraw(textToDraw) )
	{
		mainWindow.draw(textToDraw);
	}

	mainWindow.draw(textToDraw);
}

void Printer::drawBarriers(const Track& contextTrack)
{
	sf::RectangleShape rs(sf::Vector2f(0,0));
	while(contextTrack.getNextRectToDraw(rs))
		mainWindow.draw(rs);
}

void Printer::drawCarInfo(const Car& contextCar, const CarPredictedMovementInfo& cpmi, const CarPredictedMovementInfo& normalized_cpmi)
{
	sf::Text carInfoText;

//### TEXT ### /TODO
	carInfoText.setFont(arial);
	carInfoText.setCharacterSize(24);
	carInfoText.setColor(sf::Color::Red);

	std::string carMesg = 
						"Speed of Car: " + 
						std::to_string(contextCar.getVelocity().x/contextCar.getAcceleration().x)+"x "+
						std::to_string(contextCar.getVelocity().y/contextCar.getAcceleration().y) + "y"+
					 	'\n'+
						"Position of Car: "+
					 	std::to_string(contextCar.getPosition().x/contextCar.getAcceleration().x) +"x "+
						std::to_string(contextCar.getPosition().y/contextCar.getAcceleration().y) + "y"+
					 	'\n'+
						"R1 predict vec is: " + std::to_string(normalized_cpmi.relPosVec1.x) + "x " +
						std::to_string(normalized_cpmi.relPosVec1.y) + "y" + '\n' +
						"R2 predict vec is: " + std::to_string(normalized_cpmi.relPosVec2.x) + "x " +
						std::to_string(normalized_cpmi.relPosVec2.y) + "y" + '\n' +
						"End veloc versor is: "+
					 	std::to_string(normalized_cpmi.endVelVersor.x)+"x "+
						std::to_string(normalized_cpmi.endVelVersor.y)+"y"+'\n'+
						"Vector to Finish is: "+
					 	std::to_string(normalized_cpmi.vectorToFinishBarrier.x) + "x " +
						std::to_string(normalized_cpmi.vectorToFinishBarrier.y) + "y" + '\n'  												//
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

	line[0] = line[1]; 
	line[1] = sf::Vertex(sf::Vector2f(	line[0].position.x + 50*cpmi.endVelVersor.x, //TODO normalize scalar "50" to velocity per qtime
																			line[0].position.y + 50*cpmi.endVelVersor.y));

	mainWindow.draw(line, 2, sf::Lines);

	auto finishBarPoint = cpmi.vectorToFinishBarrier;
	finishBarPoint.x += contextCar.getPosition().x;
	finishBarPoint.y += contextCar.getPosition().y;
	line[0] = finishBarPoint;
	line[0].color = sf::Color::Blue;
	line[1] = sf::Vertex(contextCar.getPosition());
	line[1].color = sf::Color::Yellow;

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
	//fann creation and training
	struct fann *ann = fann_create_standard(3,10,10,2);
	fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);
	fann_train_on_file(ann, "train.data", 200, 10, 0.01);

	fann_save(ann, "car.net");
	//~fann creation and training
	//
	//terminal init

	Terminal terminal(width/2, hight/2);
	terminal.setPosition(width/4, hight/4);
	
	//#controllers init
	KeyboardController manualController;	
	ANNController testAnnController;
	CarPredictedMovementInfo contextCarPMI{	sf::Vector2f(50,50),
																					sf::Vector2f(0,0),
																					sf::Vector2f(0,0),
																					sf::Vector2f(0,0)};
	CarPredictedMovementInfo normalizedContextCarPMI = contextCarPMI;
	//~controllers init

	
	//Cars info sf:texts
	sf::Text contextCarInfoText;
	//~cars info textxs

	while(mainWindow.isOpen())
	{

	auto command_str = std::string();	

		while(mainWindow.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				mainWindow.close();
				return;
			}

			if(event.type == sf::Event::TextEntered)
			{
				auto contextUnicode = static_cast<char>(event.text.unicode);
				if(terminal.isTerminalOpen())
				{
					if(! (contextUnicode == '\\'))
					{
						if( contextUnicode == '\r' )
						{
							auto str = terminal.end_command();
							command_str = str;
						}
						else
						{
							terminal.put(static_cast<char>(contextUnicode));		
						}
					}	
					else
					{
						terminal.deActivateTerminal();
					}
				}
				else // terminal not open
				{
					if(contextUnicode == '\\')
					{
						terminal.activateTerminal();
					}
				}
			} // ~textEvent

		}

		//###FINISH state###
		if(contextCar.getFinishState())
		{
			contextCar.resetCar();
		} 
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			contextCar.resetCar();			
		}
		//###~FINISH state###
		
		//commands
		if(command_str != std::string())
		{
			if(command_str == "reset car")
			{
				contextCar.resetCar();	
			}
			else if(command_str == "exit")
			{
				break;
			}
			else if(command_str == "barrier")
			{
				terminal.deActivateTerminal();
				letUserDrawSingleBarrier(contextTrack);
			}
		}
		//~commands
		
	

		//###computations made to CARS###
		contextTrack.trackMove(contextCar); // TRACK caused ACCELERATION

		//TODO: let in some way displaying user controled car
		//manualController.move(contextCar);	
		testAnnController.move(contextCar, ann, contextTrack); // CONTROLLER cause ACCELERATION
		
		contextCar.calculateNewPosition(); // compute new position after acceleration
		//### ~computations ###
		
		//### cars info
		contextCar.getCPMovementInfo(contextCarPMI, contextTrack );
		contextCar.getNormalizedCPMovementInfo(normalizedContextCarPMI, contextTrack);
		//### ~car info
		
		//new single trainning info for ANN
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			std::ofstream tf;
			tf.open("train.data", std::ios::app | std::ios::out);

			tf << normalizedContextCarPMI.vectorToFinishBarrier.x;
			tf << " ";
			tf << normalizedContextCarPMI.vectorToFinishBarrier.y;
			tf << " ";
			tf << contextCar.getVelocity().x/contextCar.getAcceleration().x;
			tf << " ";
			tf << contextCar.getVelocity().y/contextCar.getAcceleration().y;
			tf << " ";
			tf << normalizedContextCarPMI.relPosVec1.x;
			tf << " ";
			tf << normalizedContextCarPMI.relPosVec1.y;
			tf << " ";
			tf << normalizedContextCarPMI.relPosVec2.x;
			tf << " ";
			tf << normalizedContextCarPMI.relPosVec2.y;
			tf << " ";
			tf << normalizedContextCarPMI.endVelVersor.x;
			tf << " ";
			tf << normalizedContextCarPMI.endVelVersor.y;
			tf << "\n\n";

			sf::Vector2f dir(0,0);
			while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
						dir.y=-1;
				else	
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					dir.y=1;

	
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					dir.x=1;
				else
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					dir.x=-1;

				mainWindow.clear(sf::Color::Black);
				drawBarriers(contextTrack);	
				drawCar(contextCar);
				mainWindow.display();
				if(terminal.isTerminalOpen()) drawTerminal(terminal);
				waitForNextFrame();
			}

			tf << dir.x;
			tf << " ";
			tf << dir.y;
			tf << "\n\n";

			tf.close();
		}//~fann 

		mainWindow.clear(sf::Color::Black);
		drawBarriers(contextTrack);	
		drawCar(contextCar);
		drawCarInfo(contextCar, contextCarPMI, normalizedContextCarPMI);
		if(terminal.isTerminalOpen()) drawTerminal(terminal);
		mainWindow.display();

		waitForNextFrame();

	}
	//fann
	fann_destroy(ann);
} //~testPoll

