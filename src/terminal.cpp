#include <terminal.hpp>

Terminal::Terminal(unsigned int w, unsigned int h):
	buffer(std::string()),
	width(w),
	hight(h),
	posx(0),
	posy(0),
	available_lines(hight/(2*text_size)),
	state(false)
{

}

sf::Text Terminal::getNextTextToDraw() const
{
	sf::Text textToDraw;
	textToDraw.setCharacterSize(text_size);
	textToDraw.setColor(sf::Color::Black);
	textToDraw.setString(std::string(">"+buffer));
	textToDraw.setPosition(posx,posy+(available_lines)*(2*text_size));
	return textToDraw;
}

