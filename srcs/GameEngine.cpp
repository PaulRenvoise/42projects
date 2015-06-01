#include "GameEngine.hpp"

GameEngine::GameEngine(int width, int height, int players)
{
	std::vector<std::vector<Tile*>>	board(height, std::vector<Tile*>(width, NULL));
	for (std::vector<std::vector<Tile*>>::iterator it = board.begin(); it != board.end(); it++)
	{
		for (std::vector<Tile*>::iterator iit = (*it).begin(); iit != (*it).end(); iit++)
		{
			if (it == board.begin() || iit == (*it).begin() || it + 1 == board.end() || iit + 1 == (*it).end())
				(*iit) = new Tile(eType::WALL);
			else
				(*iit) = new Tile(eType::EMPTY);
		}
	}
	this->_board = board;
	this->_spawnTile(eType::FOOD);
	this->_spawnTile(eType::HOLE);
	this->setRenderer(new RenderEngineSFML(width, height));
	if (players > 1)
	{
		this->addPlayer(new Player(0, width / 2 + 1, height / 2));
		this->addPlayer(new Player(1, width / 2 - 1, height / 2));
		this->_spawnTile(eType::FOOD);
	}
	else
		this->addPlayer(new Player(0, width / 2, height / 2));
}

GameEngine::~GameEngine(void)
{
	delete this->_renderer;

	for (unsigned long i = 0; i < this->_players.size(); i++)
		delete this->_players[i];
}

void								GameEngine::setRenderer(iRenderEngine* renderer)
{
	this->_renderer = renderer;
}

iRenderEngine*						GameEngine::getRenderer(void) const
{
	return this->_renderer;
}

void								GameEngine::addPlayer(Player* player)
{
	this->_players.push_back(player);
}

void								GameEngine::setBoard(std::vector<std::vector<Tile*>> board)
{
	this->_board = board;
}

std::vector<std::vector<Tile*>>		GameEngine::getBoard(void) const
{
	return this->_board;
}

void								GameEngine::setTile(Tile* tile, int x, int y)
{
	this->_board[x][y] = tile;
}

Tile*								GameEngine::getTile(int x, int y) const
{
	return this->_board[x][y];
}

/**
 * Main function which consists of an infinite loop and three steps
 */
void		GameEngine::run(void)
{
	double last = 0.0;
	while (true)
	{
		double now = double(clock() - last) / CLOCKS_PER_SEC;

		this->_handleInput();
		this->_update(now - last);
		this->_render();

		last = now;
	}
}

/**
 * Handle users' inputs
 */
void							GameEngine::_handleInput(void)
{
	Player* player = NULL;

	int input = this->_renderer->getEvent();

	if (input == eInputs::ESCAPE)
		this->_exit();
	else if (input != eInputs::NONE)
	{
		if (this->_players[0])
		{
			player = this->_players.front();

			if (input == eInputs::P1_UP)
				player->setNext(eDir::UP);
			else if (input == eInputs::P1_DOWN)
				player->setNext(eDir::DOWN);
			else if (input == eInputs::P1_LEFT)
				player->setNext(eDir::LEFT);
			else if (input == eInputs::P1_RIGHT)
				player->setNext(eDir::RIGHT);
		}
		if (this->_players[1])
		{
			player = this->_players.back();

			if (input == eInputs::P2_UP)
				player->setNext(eDir::UP);
			else if (input == eInputs::P2_DOWN)
				player->setNext(eDir::DOWN);
			else if (input == eInputs::P2_LEFT)
				player->setNext(eDir::LEFT);
			else if (input == eInputs::P2_RIGHT)
				player->setNext(eDir::RIGHT);
		}
	}
}

/**
 * Update the game state and all the game entities
 */
void							GameEngine::_update(double delta)
{
	for (unsigned long i = 0; i < this->_players.size(); i++)
	{
		this->_players[i]->setDelta(this->_players[i]->getDelta() + delta);
		if (this->_players[i]->getDelta() >= this->_players[i]->getSpeed())
		{
			this->_players[i]->move();
			this->_players[i]->setDelta(0);
			this->_handleSelfCollisions(this->_players[i]);
		}
	}

	if (this->_players.size() > 1)
		this->_handleExtCollisions();

	if ((std::rand() % 10000) == 1)
		this->_spawnTile(eType::BONUS);
}

/**
 * handles the collision with tiles and itself
 */
void							GameEngine::_handleSelfCollisions(Player* player)
{
	std::pair<int, int>	tmp;
	std::pair<int, int>	p1 = player->getHead();
	Tile*				t1 = this->_board[p1.second][p1.first];

	switch (t1->getType())
	{
		case eType::WALL:
			this->_lastScreen(std::to_string(player->getId() + 1));
			break;
		case eType::HOLE:
			tmp = t1->getOut();
			player->setHead(std::pair<int, int>(tmp.second, tmp.first));
			break;
		case eType::FOOD:
			player->setSpeed(player->getSpeed() / 1.5);
			player->eat(t1);
			this->_board[p1.second][p1.first]->setType(eType::EMPTY);
			this->_spawnTile(eType::FOOD);
			break;
		case eType::BONUS:
			player->eat(t1);
			this->_board[p1.second][p1.first]->setType(eType::EMPTY);
			break;
		default:
			break;
	}

	std::vector<std::pair<int, int>>	serpent = player->getSnake();
	std::sort(serpent.begin(), serpent.end());
	for (unsigned long j = 0; j < serpent.size() - 1; j++)
	{
		if (serpent[j] == serpent[j + 1])
			this->_lastScreen(std::to_string(player->getId() + 1));
	}
}

/**
 * handles the collision between snakes
 */
void							GameEngine::_handleExtCollisions(void)
{
	std::vector<std::pair<int, int>>	serpent = this->_players.front()->getSnake();
	std::vector<std::pair<int, int>>	serpent2 = this->_players.back()->getSnake();

	std::sort(serpent.begin(), serpent.end());
	std::sort(serpent2.begin(), serpent2.end());

	for (unsigned long j = 0; j < serpent.size(); j++)
	{
		for (unsigned long k = 0; k < serpent2.size(); k++)
		{
			if (serpent[j] == serpent2[k])
			{
				if (serpent[j] == this->_players.front()->getHead())
					this->_lastScreen(std::to_string(this->_players.front()->getId() + 1));
				else
					this->_lastScreen(std::to_string(this->_players.back()->getId() + 1));
			}
		}
	}
}

void							GameEngine::_lastScreen(std::string id)
{
	int	colors[2][3] = {
		{0, 0, 0},
		{255, 255, 255}
	};
	while (true)
	{
		this->_handleInput();
		this->_renderer->clear();
		this->_renderer->drawBackground(colors[0]);
		this->_renderer->drawText("Player " + id + " lost", 50, colors[1], this->_renderer->getWidth() / 2 - this->_renderer->getWidth() / 9, this->_renderer->getHeight() / 2 - this->_renderer->getHeight() / 9);
		this->_renderer->display();
	}
}

void							GameEngine::_spawnTile(int type)
{
	if (type == eType::HOLE)
	{
		int		x1 = std::rand() % (this->_board.size() - 1);
		int		y1 = std::rand() % (this->_board[0].size() - 1);
		x1 = x1 ? x1 : ++x1;
		y1 = y1 ? y1 : ++y1;
		int		x2 = std::rand() % (this->_board.size() - 1);
		int		y2 = std::rand() % (this->_board[0].size() - 1);
		x2 = x2 ? x2 : ++x2;
		y2 = y2 ? y2 : ++y2;
		if (this->_board[x1][y1]->getType() == eType::EMPTY && this->_board[x2][y2]->getType() == eType::EMPTY)
		{
			this->_board[x1][y1]->setType(type);
			this->_board[x1][y1]->setOut(std::pair<int, int>(x2, y2));
			this->_board[x2][y2]->setType(type);
			this->_board[x2][y2]->setOut(std::pair<int, int>(x1, y1));
		}
		else
			this->_spawnTile(type);
	}
	else
	{
		int		x = std::rand() % (this->_board.size() - 1);
		int		y = std::rand() % (this->_board[0].size() - 1);
		x = x ? x : ++x;
		y = y ? y : ++y;
		if (this->_board[x][y]->getType() == eType::EMPTY)
			this->_board[x][y]->setType(type);
		else
			this->_spawnTile(type);
	}
}

/**
 * Render the game current state
 */
void							GameEngine::_render(void)
{
	this->_renderer->clear();
	this->_drawBoard();
	for (unsigned long i = 0; i < this->_players.size() ; i++)
		this->_players[i]->draw(this->_renderer);
	this->_renderer->display();
}

void							GameEngine::_drawBoard(void)
{
	int		colors[5][3] = {
		{0, 0, 0},
		{45, 45, 45},
		{255, 255, 255},
		{255, 150, 0},
		{255, 240, 0},
	};
	int		x = 0;

	this->_renderer->drawBackground(colors[0]);
	for (std::vector<std::vector<Tile*>>::iterator it = this->_board.begin(); it != this->_board.end(); it++)
	{
		int	y = 0;
		for (std::vector<Tile*>::iterator iit = (*it).begin(); iit != (*it).end(); iit++)
		{
			switch ((*iit)->getType())
			{
				case eType::EMPTY:
					this->_renderer->drawTile(colors[0], x, y);
					break;
				case eType::WALL:
					this->_renderer->drawTile(colors[1], x, y);
					break;
				case eType::HOLE:
					this->_renderer->drawTile(colors[2], x, y);
					break;
				case eType::FOOD:
					this->_renderer->drawTile(colors[3], x, y);
					break;
				case eType::BONUS:
					this->_renderer->drawTile(colors[4], x, y);
					break;
			}
			y += 24;
		}
		x += 24;
	}
}

/**
 * Cleanly exits the game
 */
void							GameEngine::_exit(void)
{
	this->_renderer->exit();
	this->~GameEngine();
	exit(0);
}
