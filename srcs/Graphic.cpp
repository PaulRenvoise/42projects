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
	sf::Color color(255, 255, 255);
	this->_menu.push_back(new Graphic::Entry("START", *this->_font, color, this->_w / 2, this->_h / 2, 50, 1));
	this->_menu.push_back(new Graphic::Entry("HUMAN VS AI", *this->_font, color, this->_w / 4, this->_h / 2, 50, 2));
	this->_menu.push_back(new Graphic::Entry("HUMAN VS HUMAN", *this->_font, color, this->_w - this->_w / 4, this->_h / 2, 50, 2));
	this->_menu.push_back(new Graphic::Entry("RESUME", *this->_font, color, this->_w / 2, this->_h / 2 - 50, 50, 3));
	this->_menu.push_back(new Graphic::Entry("QUIT", *this->_font, color, this->_w / 2, this->_h / 2 + 50, 50, 3));
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

int					Graphic::getEntry(sf::Vector2f pos)
{
	for (unsigned long i = 0; i < this->_menu.size(); ++i)
	{
		if (this->_pause && this->_menu[i]->getType() == 3)
		{
			sf::Vector2f ori = this->_menu[i]->getText().getPosition();
			if (pos.x > ori.x && pos.y > ori.y && pos.x < ori.x + this->_menu[i]->getText().getLocalBounds().width && pos.y < ori.y + this->_menu[i]->getText().getLocalBounds().height)
				return static_cast<int>(i);
		}
	}
	return entries::NONE;
}

void				Graphic::_handleKeyboard(sf::Event& event)
{
	switch (event.key.code)
	{
		case sf::Keyboard::Escape:
			this->_pause = this->_pause ? false : true;
		default:
			break;
	}
}

void				Graphic::_handleMouse(sf::Event& event)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		switch (this->getEntry(this->_win->mapPixelToCoords(sf::Mouse::getPosition(*this->_win))))
		{
			case START:
				break;
			case HAI:
				break;
			case HH:
				break;
			case RESUME:
				this->_pause = false;
				break;
			case QUIT:
				std::exit(0);
				break;
			default:
				break;
		}
	}
}

void				Graphic::_handleEvents(void)
{
	sf::Event event;
	while (this->_win->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->_win->close();
			exit(0);
		}
		else if (event.type == sf::Event::KeyPressed)
			this->_handleKeyboard(event);
		else if (event.type == sf::Event::MouseButtonPressed)
			this->_handleMouse(event);
	}
}

void				Graphic::_drawUI(void)
{
	if (this->_pause)
	{
		this->_win->draw(this->_menu[RESUME]->getText());
		this->_win->draw(this->_menu[QUIT]->getText());
	}
}

void				Graphic::update(void)
{
	this->_win->clear();

	this->_drawUI();

	this->_win->display();

	this->_handleEvents();
}

/* GRAPHIC::ENTRY */

Graphic::Entry::Entry(void)
{
}

Graphic::Entry::Entry(std::string string, sf::Font& font, sf::Color& color, int x, int y, int size, int type) : _x(x), _y(y), _type(type)
{
	sf::Text text(string, font, size);
	text.setColor(color);
	text.setPosition(x - text.getLocalBounds().width /2, y - text.getLocalBounds().height /2);
	this->setText(text);
}

Graphic::Entry::~Entry(void)
{
}

void		Graphic::Entry::setText(sf::Text text)
{
	this->_text = text;
}

sf::Text	Graphic::Entry::getText(void) const
{
	return this->_text;
}

void		Graphic::Entry::setX(int x)
{
	this->_x = x;
}

int			Graphic::Entry::getX(void) const
{
	return this->_x;
}

void		Graphic::Entry::setY(int y)
{
	this->_y = y;
}

int			Graphic::Entry::getY(void) const
{
	return this->_y;
}

void		Graphic::Entry::setType(int type)
{
	this->_type = type;
}

int			Graphic::Entry::getType(void) const
{
	return this->_type;
}
