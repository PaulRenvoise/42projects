#ifndef CORE_HPP
# define CORE_HPP

# include "Player.hpp"
# include "dlfcn.h"

enum	eGraphics
{
	SFML,
	SDL,
	ALLEGRO
};

class GameEngine
{
	public:
		GameEngine(int, int, int, iRenderEngine*);
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
		int								_width;
		int								_height;
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
		void							_changeRenderer(std::string);
};

#endif
