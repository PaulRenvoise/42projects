#ifndef GRAPHIC_HPP
# define GRAPHIC_HPP

# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include <iostream>
# include "Board.hpp"

class Graphic
{
	public:
		Graphic(void);
		~Graphic(void);

		void							setWidth(int);
		int								getWidth(void) const;
		void							setHeight(int);
		int								getHeight(void) const;
		void							setWin(sf::RenderWindow*);
		sf::RenderWindow*				getWin(void) const;
		void							setFont(sf::Font*);
		sf::Font*						getFont(void) const;

		void							update(void);

	private:
		int								_w;
		int								_h;
		sf::RenderWindow*				_win;
		sf::Font*						_font;

		void							_handleEvents(void);
};

#endif
