#include "Player.hpp"

Player::Player(int id, int x, int y) :
	_id(id), _points(0), _dir(eDir::UP), _next(eDir::UP), _eat(false), _speed(0.3), _delta(0.0)
{
	this->_snake.push_back(std::pair<int, int>(x, y));
	++y;
	this->_snake.push_back(std::pair<int, int>(x, y));
	++y;
	this->_snake.push_back(std::pair<int, int>(x, y));
	++y;
	this->_snake.push_back(std::pair<int, int>(x, y));
}

Player::~Player(void)
{
}

void								Player::setId(int id)
{
	this->_id = id;
}

int									Player::getId(void) const
{
	return this->_id;
}

void								Player::setPoints(int points)
{
	this->_points = points;
}

int									Player::getPoints(void) const
{
	return this->_points;
}

void								Player::setSnake(std::vector<std::pair<int, int>>& snake)
{
	this->_snake = snake;
}

std::vector<std::pair<int, int>>	Player::getSnake(void) const
{
	return this->_snake;
}

void								Player::setHead(std::pair<int, int> p)
{
	this->_snake.erase(this->_snake.begin());
	this->_snake.insert(this->_snake.begin(), p);
}

std::pair<int, int>					Player::getHead(void) const
{
	return this->_snake.front();
}

void								Player::setDir(int dir)
{
	this->_dir = this->_convert[this->_dir][dir];
}

int									Player::getDir(void) const
{
	return this->_dir;
}

void								Player::setNext(int next)
{
	this->_next = this->_convert[this->_dir][next];
}

int									Player::getNext(void) const
{
	return this->_next;
}

void								Player::setEat(bool eat)
{
	this->_eat = eat;
}

bool								Player::getEat(void) const
{
	return this->_eat;
}

void								Player::setSpeed(double speed)
{
	this->_speed = speed;
}

double								Player::getSpeed(void) const
{
	return this->_speed;
}

void								Player::setDelta(double delta)
{
	this->_delta = delta;
}

double								Player::getDelta(void) const
{
	return this->_delta;
}

void								Player::move(void)
{
	std::pair<int, int>	p = this->_snake.front();
	this->_dir = this->_next;

	if (this->_dir == eDir::UP)
		p.second--;
	else if (this->_dir == eDir::DOWN)
		p.second++;
	else if (this->_dir == eDir::LEFT)
		p.first--;
	else if (this->_dir == eDir::RIGHT)
		p.first++;
	this->_snake.insert(this->_snake.begin(), p);

	if (!this->_eat)
		this->_snake.pop_back();
	else
		this->_eat = false;
}

void								Player::eat(Tile* tile)
{
	this->_eat = true;
	this->_points = this->_points + tile->getValue();
}

void								Player::draw(iRenderEngine* renderer)
{
	int	textColor[3] = {255, 255, 255};
	int	colors[2][2][3] = {
		{{120, 255, 120}, {20, 255, 20}},
		{{255, 100, 100}, {255, 40, 40}}
	};
	int width = renderer->getWidth();
	int	x = this->_id ? width / 2 - width / 4 - width / 20: width - width / 4 - width / 20;

	/**
	 * Renders UI
	 */
	renderer->drawText("Player " + std::to_string(this->_id + 1), 40, textColor, x, renderer->getHeight() - 110);
	renderer->drawText("Score: " + std::to_string(this->_points), 30, textColor, x + 10, renderer->getHeight() - 70);
	renderer->drawText("Speed: " + std::to_string(int(3 / this->_speed)), 30, textColor, x + 5, renderer->getHeight() - 40);
	for (int y = renderer->getHeight() - 100; y < renderer->getHeight(); y++)
	{
		int color[3] = {45, 45, 45};
		renderer->drawTile(color, y / 24, width / 2 / 24);
	}

	/**
	 * Renders snake
	 */
	for (std::vector<std::pair<int, int>>::iterator it = this->_snake.begin(); it != this->_snake.end(); it++)
	{
		if (it != this->_snake.begin())
			renderer->drawTile(colors[this->_id][0], (*it).second, (*it).first);
		else
			renderer->drawTile(colors[this->_id][1], (*it).second, (*it).first);
	}
}
