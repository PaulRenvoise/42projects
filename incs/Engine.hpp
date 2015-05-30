#ifndef ENGINE_HPP
# define ENGINE_HPP

# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include <vector>
# include <iostream>
# include "Tile.hpp"
# include "Player.hpp"

enum	eInputs
{
	NONE = 50,
	ESCAPE,
	P1_UP,
	P1_DOWN,
	P1_LEFT,
	P1_RIGHT,
	P2_UP,
	P2_DOWN,
	P2_LEFT,
	P2_RIGHT
};

class Engine
{
	public:
		Engine(int, int);
		~Engine(void);

		void				setWidth(int);
		int					getWidth(void) const;
		void				setHeight(int);
		int					getHeight(void) const;
		void				setWin(sf::RenderWindow*);
		sf::RenderWindow*	getWin(void) const;
		void				setFont(sf::Font*);
		sf::Font*			getFont(void) const;

		void				render(std::vector<std::vector<Tile*>>&, std::vector<Player*>&);
		void				clear(void);
		void				exit(void);
		void				display(void);
		int					getEvent(void);

	private:
		int					_w;
		int					_h;
		sf::RenderWindow*	_win;
		sf::Font*			_font;

		void				_renderBoard(std::vector<std::vector<Tile*>>&);
		void				_renderSnake(Snake*);
		void				_renderUI(Player*);
};

#endif
