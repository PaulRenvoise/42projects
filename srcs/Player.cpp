#include "Player.hpp"

Player::Player(int width, int height) :
	_points(0)
{
	this->setSnake(new Snake(width, height));
}

Player::~Player(void)
{
	delete this->_snake;
}

void			Player::setSnake(Snake* snake)
{
	this->_snake = snake;
}

Snake*			Player::getSnake(void) const
{
	return this->_snake;
}

void			Player::addPoints(int points)
{
	this->_points += points;
}

int				Player::getPoints(void) const
{
	return this->_points;
}

void			Player::setSnakeDirection(int dir)
{
	this->_snake->setDirection(dir);
}

int				Player::getSnakeDirection(void) const
{
	return this->_snake->getDirection();
}

void			Player::setSnakeNext(int next)
{
	this->_snake->setNext(next);
}

int				Player::getSnakeNext(void) const
{
	return this->_snake->getNext();
}

void			Player::setSnakeHead(std::pair<int, int> p)
{
	this->_snake->setHead(p);
}

std::pair<int, int>	Player::getSnakeHead(void) const
{
	return this->_snake->getHead();
}

void				Player::setSnakeSpeed(double speed)
{
	this->_snake->setSpeed(speed);
}

double				Player::getSnakeSpeed(void) const
{
	return this->_snake->getSpeed();
}

void				Player::setSnakeDelta(double delta)
{
	this->_snake->setDelta(delta);
}

double				Player::getSnakeDelta(void) const
{
	return this->_snake->getDelta();
}

void			Player::moveSnake(void)
{
	this->_snake->move();
}

void			Player::setSnakeEat(Tile* tile)
{
	this->_snake->setEat(true);
	this->addPoints(tile->getValue());
}

void			Player::setSnakeStarve(void)
{
	this->_snake->setEat(false);
}
