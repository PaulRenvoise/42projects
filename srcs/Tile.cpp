#include "Tile.hpp"

Tile::Tile(void) :
	_type(EMPTY), _value(0), _out(std::pair<int, int>(0, 0))
{
}

Tile::Tile(int type) :
	_type(type), _out(std::pair<int, int>(0, 0))
{
	if (this->_type == eType::FOOD)
		this->_value = 1;
	else if (this->_type == eType::BONUS)
		this->_value = 5;
	else
		this->_value = 0;
}

Tile::Tile(const Tile& rhs)
{
	*this = rhs;
}

Tile::~Tile(void)
{
}

Tile&		Tile::operator=(const Tile& rhs)
{
	this->_type = rhs.getType();
	this->_value = rhs.getValue();
	this->_out = rhs.getOut();

	return *this;
}

void		Tile::setType(int type)
{
	this->_type = type;

	if (this->_type == eType::FOOD)
		this->_value = 1;
	else if (this->_type == eType::BONUS)
		this->_value = 5;
	else
		this->_value = 0;
}

int			Tile::getType(void) const
{
	return this->_type;
}

void		Tile::setValue(int value)
{
	this->_value = value;
}

int			Tile::getValue(void) const
{
	return this->_value;
}

void		Tile::setOut(std::pair<int, int> p)
{
	this->_out = p;
}

std::pair<int, int>	Tile::getOut(void) const
{
	return this->_out;
}

void		Tile::dump(void) const
{
	if (this->_type == eType::EMPTY)
		std::cout << "EMPTY";
	else if (this->_type == eType::WALL)
		std::cout << "WALL";
	else if (this->_type == eType::HOLE)
		std::cout << "HOLE";
	else if (this->_type == eType::FOOD)
		std::cout << "FOOD";
	else if (this->_type == eType::BONUS)
		std::cout << "BONUS";
}
