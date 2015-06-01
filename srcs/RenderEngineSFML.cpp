#include "RenderEngineSFML.hpp"

RenderEngineSFML::RenderEngineSFML(int width, int height)
{
	this->_w = width * 24;
	this->_h = height * 24 + 100;
	this->_win = new sf::RenderWindow(sf::VideoMode(this->_w, this->_h), "NIBBLER");
	this->_font = new sf::Font();
	this->_font->loadFromFile("./font/Square.ttf");
	this->_tile = new sf::RectangleShape(sf::Vector2f(24, 24));
	this->_text = new sf::Text("", *this->_font);
}

RenderEngineSFML::~RenderEngineSFML(void)
{
	delete this->_win;
	delete this->_tile;
	delete this->_text;
}

void				RenderEngineSFML::setWidth(int width)
{
	this->_w = width;
}

int					RenderEngineSFML::getWidth(void) const
{
	return this->_w;
}

void				RenderEngineSFML::setHeight(int height)
{
	this->_h = height;
}

int					RenderEngineSFML::getHeight(void) const
{
	return this->_h;
}

void				RenderEngineSFML::setWin(sf::RenderWindow* win)
{
	this->_win = win;
}

sf::RenderWindow*	RenderEngineSFML::getWin(void) const
{
	return this->_win;
}

void				RenderEngineSFML::drawTile(int colors[3], int x, int y)
{
	this->_tile->setFillColor(sf::Color(colors[0], colors[1], colors[2]));
	this->_tile->setPosition(y, x);
	this->_win->draw(*this->_tile);
}

void				RenderEngineSFML::drawText(std::string content, int size, int* colors, int x, int y)
{
	this->_text->setFont(*this->_font);
	this->_text->setString(content);
	this->_text->setCharacterSize(size);
	this->_text->setColor(sf::Color(colors[0], colors[1], colors[2]));
	this->_text->setPosition(x, y);
	this->_win->draw(*this->_text);
}

void				RenderEngineSFML::clear(void)
{
	this->_win->clear();
}

void				RenderEngineSFML::display(void)
{
	this->_win->display();
}

void				RenderEngineSFML::exit(void)
{
	this->_win->close();
}

int					RenderEngineSFML::getEvent(void)
{
	sf::Event	event;
	int			input = eInputs::NONE;

	while (this->_win->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->_win->close();
			input = eInputs::ESCAPE;
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					input = eInputs::ESCAPE;
					break;
				case sf::Keyboard::Up:
					input = eInputs::P1_UP;
					break;
				case sf::Keyboard::Down:
					input = eInputs::P1_DOWN;
					break;
				case sf::Keyboard::Left:
					input = eInputs::P1_LEFT;
					break;
				case sf::Keyboard::Right:
					input = eInputs::P1_RIGHT;
					break;
				case sf::Keyboard::W:
					input = eInputs::P2_UP;
					break;
				case sf::Keyboard::S:
					input = eInputs::P2_DOWN;
					break;
				case sf::Keyboard::A:
					input = eInputs::P2_LEFT;
					break;
				case sf::Keyboard::D:
					input = eInputs::P2_RIGHT;
					break;
				default:
					break;
			}
		}
	}

	return input;
}
