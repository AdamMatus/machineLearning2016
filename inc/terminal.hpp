#ifndef _TERMINAL_HPP_
#define _TERMINAL_HPP_

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

class Terminal {
	public:
		Terminal(unsigned int, unsigned int);
		void registerPhrase(const std::string& rp);
		const std::string& checkForPhrase();
		void put(char c)
		{
			buffer += c;
		}
		sf::Vector2f getSize()
		{
			return sf::Vector2f(width, hight);
		}
		sf::Vector2f getPosition()
		{
			return sf::Vector2f(posx, posy);
		}
		void setPosition(unsigned int x , unsigned int y)
		{
			posx = x; posy = y;
		}
		bool isTerminalOpen()
		{
			return state;
		}
		void activateTerminal()
		{
			state = true;
		}
		void deActivateTerminal()
		{
			state = false;
		}
		std::string getActualBuffer()
		{
			std::string bufferString;

			return bufferString;
		}
		sf::RectangleShape getRectToDraw() const
		{
			sf::RectangleShape recToDraw(sf::Vector2f(width, hight));
			recToDraw.setPosition(posx,posy);
			recToDraw.setFillColor(sf::Color(255,255,255,200));
			return recToDraw;
		}
		sf::Text getNextTextToDraw() const;

	private:
		static const unsigned int text_size = 40;
		std::vector<std::string> history;
		std::vector<std::string> registeredPhrases;
		std::string buffer;
		unsigned int width, hight;
		unsigned int posx, posy;
		const unsigned int available_lines;
		bool state;

}; //~terminal

#endif
