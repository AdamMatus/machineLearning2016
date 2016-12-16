#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <thread>
#include <string>
#include <chrono>

#include <car.hpp>
#include <track.hpp>
#include <printer.hpp>

int main(int argc, char *argv[])
{
	//PRINTER +++
	auto winSize = sf::Vector2u(1400,900);
	Printer mainPrinter(winSize.x, winSize.y);
	//++++++++++++

	//TRACK +++
	Track mainTrack(winSize);
	//++++++++++++

	//single test barrier
	auto testBarrier = sf::RectangleShape(sf::Vector2f(100, 50));
	testBarrier.setPosition(200,300);
	testBarrier.setFillColor(sf::Color::Green);

	mainTrack.add_barrier(testBarrier);

	testBarrier.setPosition(700, 300);
	mainTrack.add_barrier(testBarrier);
	/********************/

	//DRAWING BARRIERS
	if(mainPrinter.letUserDrawBarriers(mainTrack)) return 0; //add exception 
	//++++++++++++++++++


	//TEST CAR
	auto doggoSize = sf::Vector2f(25,25);
	sf::Vector2<float> doggoStartPos;
	doggoStartPos.x	= static_cast<float>(winSize.x);
	doggoStartPos.y	= static_cast<float>(winSize.y);
	doggoStartPos.x /= 2;
	doggoStartPos.x -= doggoSize.x/2;
	doggoStartPos.y /= 2;
	doggoStartPos.y -= doggoSize.y/2;
	Car doggo(30, doggoStartPos, doggoSize);
	//+++++++++++++++++++++++

	mainPrinter.testPoll(mainTrack, doggo);
	return 0;
}
