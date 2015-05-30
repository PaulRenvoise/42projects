#include "Snake.hpp"

Snake::Snake(int x, int y) :
	_speed(0.3), _delta(0.0)
{
	this->_snake.push_back(std::pair<int, int>(x, y));
	++y;
	this->_snake.push_back(std::pair<int, int>(x, y));
	++y;
	this->_snake.push_back(std::pair<int, int>(x, y));
	++y;
	this->_snake.push_back(std::pair<int, int>(x, y));

	this->_dir = eDir::UP;
	this->_next = eDir::UP;
	this->_eat = false;
}

Snake::~Snake(void)
{
}

void								Snake::setDirection(int dir)
{
	this->_dir = this->_convert[this->_dir][dir];
}

int									Snake::getDirection(void) const
{
	return this->_dir;
}

void								Snake::setNext(int next)
{
	this->_next = this->_convert[this->_dir][next];
}

int									Snake::getNext(void) const
{
	return this->_next;
}

void								Snake::setSnake(std::vector<std::pair<int, int>>& snake)
{
	this->_snake = snake;
}

std::vector<std::pair<int, int>>	Snake::getSnake(void) const
{
	return this->_snake;
}

void								Snake::setHead(std::pair<int, int>& p)
{
	this->_snake.erase(this->_snake.begin());
	this->_snake.insert(this->_snake.begin(), p);
}

std::pair<int, int>					Snake::getHead(void) const
{
	return this->_snake.front();
}

void								Snake::setEat(bool eat)
{
	this->_eat = eat;
}

bool								Snake::hasEat(void) const
{
	return this->_eat;
}

void								Snake::setSpeed(double speed)
{
	this->_speed = speed;
}

double								Snake::getSpeed(void) const
{
	return this->_speed;
}

void								Snake::setDelta(double delta)
{
	this->_delta = delta;
}

double								Snake::getDelta(void) const
{
	return this->_delta;
}

void								Snake::move(void)
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
