#include "Game.hpp"

Game::Game(void)
{
	this->setGraphic(new Graphic());
}

Game::~Game(void)
{
}

void			Game::setGraphic(Graphic* graphic)
{
	this->_graphic = graphic;
}

Graphic*		Game::getGraphic(void) const
{
	return this->_graphic;
}

void			Game::setPlayer1(Player* player)
{
	this->_player1 = player;
}

Player*			Game::getPlayer1(void) const
{
	return this->_player1;
}

void			Game::setPlayer2(Player* player)
{
	this->_player2 = player;
}

Player*			Game::getPlayer2(void) const
{
	return this->_player2;
}

void			Game::setBoard(Board* board)
{
	this->_board = board;
}

Board*			Game::getBoard(void) const
{
	return this->_board;
}

void		Game::run(void)
{
	while (true)
	{
		this->_graphic->update();
	}
}
