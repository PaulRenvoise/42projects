#include "Graphic.hpp"

Graphic::Graphic(void)
{
	this->setWidth(1500);
	this->setHeight(1000);
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	this->setWin(new sf::RenderWindow(sf::VideoMode(this->_w, this->_h), "GOMOKU", sf::Style::Default, settings));
	this->setFont(new sf::Font());
	this->_font->loadFromFile("./font/Lato-Regular.ttf");
}

Graphic::~Graphic(void)
{
}

void				Graphic::setWidth(int width)
{
	this->_w = width;
}

int					Graphic::getWidth(void) const
{
	return this->_w;
}

void				Graphic::setHeight(int height)
{
	this->_h = height;
}

int					Graphic::getHeight(void) const
{
	return this->_h;
}

void				Graphic::setWin(sf::RenderWindow* win)
{
	this->_win = win;
}

sf::RenderWindow*	Graphic::getWin(void) const
{
	return this->_win;
}

void				Graphic::setFont(sf::Font* font)
{
	this->_font = font;
}

sf::Font*			Graphic::getFont(void) const
{
	return this->_font;
}

void				Graphic::_handleEvents(void)
{
	sf::Event event;
	while (this->_win->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->_win->close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
				default:
					break;
			}
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			switch (event.mouseButton.button)
			{
				case sf::Mouse::Left:
				default:
					break;
			}
		}
	}
}

void				Graphic::update()
{
	this->_win->clear();

	this->_win->display();

	this->_handleEvents();
}
