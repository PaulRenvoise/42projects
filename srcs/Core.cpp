#include "Core.hpp"

Core::Core(int width, int height, int players)
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
	this->setEngine(new Engine(width, height));
	if (players > 1)
	{
		this->addPlayer(new Player(width / 2 + 1, height / 2));
		this->addPlayer(new Player(width / 2 - 1, height / 2));
	}
	else
		this->addPlayer(new Player(width / 2, height / 2));
	this->setRunning(true);
}

Core::~Core(void)
{
	delete this->_engine;

	for (unsigned long i = 0; i < this->_players.size(); i++)
		delete this->_players[i];
}

void								Core::setEngine(Engine* engine)
{
	this->_engine = engine;
}

Engine*								Core::getEngine(void) const
{
	return this->_engine;
}

void								Core::addPlayer(Player* player)
{
	this->_players.push_back(player);
}

void								Core::setBoard(std::vector<std::vector<Tile*>> board)
{
	this->_board = board;
}

std::vector<std::vector<Tile*>>		Core::getBoard(void) const
{
	return this->_board;
}

void								Core::setTile(Tile* tile, int x, int y)
{
	this->_board[x][y] = tile;
}

Tile*								Core::getTile(int x, int y) const
{
	return this->_board[x][y];
}

void								Core::setRunning(bool running)
{
	this->_running = running;
}

bool								Core::isRunning(void) const
{
	return this->_running;
}

/**
 * Main function which consists of an infinite loop and three steps
 */
void		Core::run(void)
{
	double last = 0.0;
	while (this->_running)
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
void							Core::_handleInput(void)
{
	Player* player = NULL;

	int input = this->_engine->getEvent();

	if (input == eInputs::ESCAPE)
		this->_exit();
	else if (input != eInputs::NONE)
	{
		player = this->_players.front();

		if (input == eInputs::P1_UP)
			player->setSnakeNext(eDir::UP);
		else if (input == eInputs::P1_DOWN)
			player->setSnakeNext(eDir::DOWN);
		else if (input == eInputs::P1_LEFT)
			player->setSnakeNext(eDir::LEFT);
		else if (input == eInputs::P1_RIGHT)
			player->setSnakeNext(eDir::RIGHT);
		else if (this->_players.size() > 1)
		{
			player = this->_players.back();

			if (input == eInputs::P2_UP)
				player->setSnakeNext(eDir::UP);
			else if (input == eInputs::P2_DOWN)
				player->setSnakeNext(eDir::DOWN);
			else if (input == eInputs::P2_LEFT)
				player->setSnakeNext(eDir::LEFT);
			else if (input == eInputs::P2_RIGHT)
				player->setSnakeNext(eDir::RIGHT);
		}
	}
}

/**
 * Update the game state and all the game entities
 */
void							Core::_update(double delta)
{
	for (unsigned long i = 0; i < this->_players.size(); i++)
	{
		this->_players[i]->setSnakeDelta(this->_players[i]->getSnakeDelta() + delta);
		if (this->_players[i]->getSnakeDelta() >= this->_players[i]->getSnakeSpeed())
		{
			this->_players[i]->moveSnake();
			this->_players[i]->setSnakeDelta(0);
			this->_handleSelfCollisions(this->_players[i]);
		}
	}

	if (this->_players.size() > 1)
		this->_handleExtCollisions();

	if ((std::rand() % 50000) == 1)
		this->_spawnTile(eType::BONUS);
}

/**
 * handles the collision with tiles and itself
 */
void							Core::_handleSelfCollisions(Player* player)
{
	std::pair<int, int>	tmp;
	std::pair<int, int>	p1 = player->getSnakeHead();
	Tile*				t1 = this->_board[p1.second][p1.first];

	switch (t1->getType())
	{
		case eType::WALL:
			this->_exit();
			break;
		case eType::HOLE:
			tmp = t1->getOut();
			player->setSnakeHead(std::pair<int, int>(tmp.second, tmp.first));
			break;
		case eType::FOOD:
			player->setSnakeSpeed(player->getSnakeSpeed() / 1.5);
			player->setSnakeEat(t1);
			this->_board[p1.second][p1.first]->setType(eType::EMPTY);
			this->_spawnTile(eType::FOOD);
			break;
		case eType::BONUS:
			player->setSnakeEat(t1);
			this->_board[p1.second][p1.first]->setType(eType::EMPTY);
			break;
		default:
			break;
	}

	std::vector<std::pair<int, int>>	serpent = player->getSnake()->getSnake();
	std::sort(serpent.begin(), serpent.end());
	for (unsigned long j = 0; j < serpent.size() - 1; j++)
	{
		if (serpent[j] == serpent[j + 1])
			this->_exit();
	}
}

/**
 * handles the collision between snakes
 */
void							Core::_handleExtCollisions(void)
{
	std::vector<std::pair<int, int>>	serpent = this->_players.front()->getSnake()->getSnake();
	std::vector<std::pair<int, int>>	serpent2 = this->_players.back()->getSnake()->getSnake();

	std::sort(serpent.begin(), serpent.end());
	std::sort(serpent2.begin(), serpent2.end());

	for (unsigned long j = 0; j < serpent.size(); j++)
	{
		for (unsigned long k = 0; k < serpent2.size(); k++)
		{
			if (serpent[j] == serpent2[k])
				this->_exit();
		}
	}
}

void							Core::_spawnTile(int type)
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
		this->_board[x1][y1]->setType(type);
		this->_board[x1][y1]->setOut(std::pair<int, int>(x2, y2));
		this->_board[x2][y2]->setType(type);
		this->_board[x2][y2]->setOut(std::pair<int, int>(x1, y1));
	}
	else
	{
		int		x = std::rand() % (this->_board.size() - 1);
		int		y = std::rand() % (this->_board[0].size() - 1);
		x = x ? x : ++x;
		y = y ? y : ++y;
		this->_board[x][y]->setType(type);
	}
}

/**
 * Render the game current state
 */
void							Core::_render(void)
{
	this->_engine->clear();
	this->_engine->render(this->_board, this->_players);
	this->_engine->display();
}

/**
 * Exits cleanly the game
 */
void							Core::_exit(void)
{
	this->_engine->exit();
	this->~Core();
	exit(0);
}
