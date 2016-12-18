#include <terminal.hpp>

Terminal::Terminal(unsigned int w, unsigned int h):
	buffer(std::string()),
	width(w),
	hight(h),
	posx(0),
	posy(0),
	available_lines(hight/static_cast<unsigned int>(1.2*text_size)),
	state(false)
{
	history.push_back(std::string());
}

bool Terminal::getNextTextToDraw(sf::Text& textToDraw) const
{
	static int index = 0; // never call .end() - 0
	auto t_iter = history.end() - (index);
	textToDraw.setCharacterSize(text_size);
	textToDraw.setColor(sf::Color::Black);
	if( index == 0 )
	{
		textToDraw.setString(std::string(">"+buffer));
		textToDraw.setPosition(posx,posy+(available_lines-1)*(1.2*text_size));
		index++;
		return true;
	}
	else if(t_iter >= history.begin() and index <= static_cast<int>(available_lines))
	{
		textToDraw.setString(*t_iter);	
		textToDraw.setPosition(posx, posy+static_cast<unsigned int>(available_lines-1 - index)*(1.2*text_size));
		index++;
		return true;
	}
	index = 0;
	return false;
}

