#ifndef CORE_HPP
# define CORE_HPP

# include <iostream>
# include <vector>
# include "iRenderEngine.hpp"
# include "Player.hpp"
# include "Tile.hpp"

# define INTERVAL_FRAMES 0.1

enum	eGraphics
{
	SFML,
	SDL,
	ALLEGRO
};

class GameEngine
{
	public:
		GameEngine(int, int, int);
		~GameEngine(void);

		void							setRenderer(iRenderEngine*);
		iRenderEngine*					getRenderer(void) const;

		void							addPlayer(Player*);

		void							setBoard(std::vector<std::vector<Tile*>>);
		std::vector<std::vector<Tile*>>	getBoard(void) const;
		void							setTile(Tile*, int, int);
		Tile*							getTile(int, int) const;

		void							setRunning(bool);
		bool							isRunning(void) const;

		void							run(void);

	private:
		iRenderEngine*					_renderer;
		std::vector<Player*>			_players;
		std::vector<std::vector<Tile*>>	_board;

		void							_handleInput(void);
		void							_update(double);
		void							_handleSelfCollisions(Player*);
		void							_handleExtCollisions(void);
		void							_spawnTile(int);
		void							_render(void);
		void							_exit(void);

		void							_drawBoard(void);
		void							_lastScreen(std::string);
};

#endif
