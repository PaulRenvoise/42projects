#include "Engine.hpp"

Engine::Engine(int width, int height)
{
	this->setWidth(width * 24);
	this->setHeight(height * 24 + 100);
	this->setWin(new sf::RenderWindow(sf::VideoMode(this->_w, this->_h), "NIBBLER"));
	this->setFont(new sf::Font());
	this->_font->loadFromFile("./font/Lato-Regular.ttf");
}

Engine::~Engine(void)
{
	delete this->_win;
	delete this->_font;
}

void				Engine::setWidth(int width)
{
	this->_w = width;
}

int					Engine::getWidth(void) const
{
	return this->_w;
}

void				Engine::setHeight(int height)
{
	this->_h = height;
}

int					Engine::getHeight(void) const
{
	return this->_h;
}

void				Engine::setWin(sf::RenderWindow* win)
{
	this->_win = win;
}

sf::RenderWindow*	Engine::getWin(void) const
{
	return this->_win;
}

void				Engine::setFont(sf::Font* font)
{
	this->_font = font;
}

sf::Font*			Engine::getFont(void) const
{
	return this->_font;
}

void				Engine::render(std::vector<std::vector<Tile*>>& board, std::vector<Player*>& players)
{
	this->_renderBoard(board);
	for (unsigned long i = 0; i < players.size(); i++)
	{
		this->_renderSnake(players[i]->getSnake());
		this->_renderUI(players[i]);
	}
}

void				Engine::_renderBoard(std::vector<std::vector<Tile*>>& board)
{
	int					x = 0;
	sf::RectangleShape	sq(sf::Vector2f(24, 24));

	for (std::vector<std::vector<Tile*>>::iterator it = board.begin(); it != board.end(); it++)
	{
		int				y = 0;
		for (std::vector<Tile*>::iterator iit = (*it).begin(); iit != (*it).end(); iit++)
		{
			int type = (*iit)->getType();
			if (type == eType::EMPTY)
			{
				sq.setFillColor(sf::Color(0, 0, 0));
				sq.setPosition(y, x);
			}
			else if (type == eType::WALL)
			{
				sq.setFillColor(sf::Color(122, 0, 0));
				sq.setPosition(y, x);
			}
			else if (type == eType::HOLE)
			{
				sq.setFillColor(sf::Color(255, 255, 255));
				sq.setPosition(y, x);
			}
			else if (type == eType::FOOD)
			{
				sq.setFillColor(sf::Color(0, 122, 122));
				sq.setPosition(y, x);
			}
			else if (type == eType::BONUS)
			{
				sq.setFillColor(sf::Color(0, 255, 255));
				sq.setPosition(y, x);
			}
			this->_win->draw(sq);
			y += 24;
		}
		x += 24;
	}
}

void				Engine::_renderSnake(Snake* snake)
{
	std::vector<std::pair<int, int>>	serpent = snake->getSnake();
	sf::RectangleShape					sq(sf::Vector2f(24, 24));
	sq.setFillColor(sf::Color(0, 122, 0));

	for (std::vector<std::pair<int, int>>::iterator it = serpent.begin(); it != serpent.end(); it++)
	{
		if (it != serpent.begin())
			sq.setFillColor(sf::Color(0, 50, 0));
		sq.setPosition((*it).first * 24, (*it).second * 24);
		this->_win->draw(sq);
	}
}

void				Engine::_renderUI(Player* player)
{
	sf::Text pts(std::to_string(player->getPoints()), *this->_font);
	pts.setCharacterSize(20);
	pts.setColor(sf::Color(255, 255, 255));
	pts.setPosition(10, this->_h - 50);
	this->_win->draw(pts);
}

void				Engine::clear(void)
{
	this->_win->clear();
}

void				Engine::display(void)
{
	this->_win->display();
}

void				Engine::exit(void)
{
	this->_win->close();
}

int					Engine::getEvent(void)
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
