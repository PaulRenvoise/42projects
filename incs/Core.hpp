#ifndef CORE_HPP
# define CORE_HPP

# include <iostream>
# include <vector>
# include "Engine.hpp"
# include "Player.hpp"
# include "Tile.hpp"

# define INTERVAL_FRAMES 0.1

enum	eGraphics
{
	SFML,
	SDL,
	ALLEGRO
};

class Core
{
	public:
		Core(int, int, int);
		~Core(void);

		void							setEngine(Engine*);
		Engine*							getEngine(void) const;

		void							addPlayer(Player*);

		void							setBoard(std::vector<std::vector<Tile*>>);
		std::vector<std::vector<Tile*>>	getBoard(void) const;
		void							setTile(Tile*, int, int);
		Tile*							getTile(int, int) const;

		void							setRunning(bool);
		bool							isRunning(void) const;

		void							run(void);

	private:
		Engine*							_engine;
		std::vector<Player*>			_players;
		std::vector<std::vector<Tile*>>	_board;
		bool							_running;

		void							_handleInput(void);
		void							_update(double);
		void							_handleSelfCollisions(Player*);
		void							_handleExtCollisions(void);
		void							_spawnTile(int);
		void							_render(void);
		void							_exit(void);
		std::vector<std::vector<Tile*>>	_initBoard(int, int);
};

#endif
