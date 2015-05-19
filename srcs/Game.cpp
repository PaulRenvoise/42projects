#include "Game.hpp"

Game::Game(void)
{
}

Game::~Game(void)
{
}

void		Game::run(void)
{
	Graphic graphic;
	while (true)
	{
		graphic.update();
	}
}
