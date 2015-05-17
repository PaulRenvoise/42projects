#ifndef GRAPHIC_HPP
# define GRAPHIC_HPP

# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include "Board.hpp"

enum	inputs {
	NONE,
	ESCAPE,
	CLICK,
};

class Graphic
{
	public:
		Graphic(void);
		~Graphic(void);

		Graphic(const Graphic&);
		Graphic&			operator=(const Graphic&);

		void				setWidth(int);
		int					getWidth(void) const;
		void				setHeight(int);
		int					getHeight(void) const;
		void				setWin(sf::RenderWindow*);
		sf::RenderWindow*	getWin(void) const;
		void				setFont(sf::Font*);
		sf::Font*			getFont(void) const;

		void				render(const Board&);

	private:
		int					_w;
		int					_h;
		sf::RenderWindow*	_win;
		sf::Font*			_font;
		sf::RectangleShape*	_bgShape;

		int					_getEvents(void) const;
};

#endif
