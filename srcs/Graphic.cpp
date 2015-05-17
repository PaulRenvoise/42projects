#include "Graphic.hpp"

#include <iostream>
Graphic::Graphic(void)
{
	this->setWidth(1500);
	this->setHeight(1000);
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	this->setWin(new sf::RenderWindow(sf::VideoMode(this->_w, this->_h), "GOMOKU", sf::Style::Default, settings));
	this->setFont(new sf::Font());
	this->_font->loadFromFile("./font/Lato-Regular.ttf");

	this->_bgShape = new sf::RectangleShape(sf::Vector2f(this->_w, this->_h));
	this->_bgShape->setFillColor(sf::Color(42, 49, 63));
	this->_bgShape->setPosition(0, 0);
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

int				Graphic::_getEvents(void) const
{
	sf::Event event;
	while (this->_win->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->_win->close();
			return inputs::ESCAPE;
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					this->_win->close();
					return inputs::ESCAPE;
				case sf::Mouse::Left:
					return inputs::CLICK;
				default:
					break;
			}
		}
	}
	return inputs::NONE;
}

void				Graphic::render(const Board& board)
{
	(void)board;
	while (this->_win->isOpen())
	{
		this->_win->clear();

		this->_win->draw(*this->_bgShape);

		for (int i = 0; i < 18; ++i)
		{
			for (int j = 0; j < 18; ++j)
			{
				sf::RectangleShape cell(sf::Vector2f(48, 48));
				cell.setFillColor(sf::Color(0, 0, 0, 0));
				cell.setOutlineColor(sf::Color(255, 255, 255));
				cell.setOutlineThickness(1);
				cell.setPosition(300 + i * 49, 50 + j * 49);
				this->_win->draw(cell);
			}
		}

		sf::CircleShape circle(25);
		circle.setFillColor(sf::Color(0, 0, 0));
		circle.setPosition(275, 25);
		this->_win->draw(circle);

		sf::CircleShape circle2(25);
		circle2.setFillColor(sf::Color(255, 255, 255));
		circle2.setPosition(325, 25);
		this->_win->draw(circle2);

		sf::CircleShape circle3(25);
		circle3.setFillColor(sf::Color(0, 0, 0));
		circle3.setPosition(375, 25);
		this->_win->draw(circle3);

		this->_win->display();

		int input = this->_getEvents();
		if (input == inputs::ESCAPE)
			exit(0);
	}
}
