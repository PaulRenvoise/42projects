#ifndef GRAPHIC_HPP
# define GRAPHIC_HPP

# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include <vector>
# include "Board.hpp"

enum	entries {
	START,
	HAI,
	HH,
	RESUME,
	QUIT,
	NONE
};

class Graphic
{
	class Entry
	{
		public:

			Entry(void);
			Entry(std::string, sf::Font&, sf::Color&, int, int, int, int);
			~Entry(void);

			void		setText(sf::Text);
			sf::Text	getText(void) const;
			void		setX(int);
			int			getX(void) const;
			void		setY(int);
			int			getY(void) const;
			void		setType(int);
			int			getType(void) const;

		private:
			sf::Text	_text;
			int			_x;
			int			_y;
			int			_type;
	};

	public:
		Graphic(void);
		~Graphic(void);

		void								setWidth(int);
		int									getWidth(void) const;
		void								setHeight(int);
		int									getHeight(void) const;
		void								setWin(sf::RenderWindow*);
		sf::RenderWindow*					getWin(void) const;
		void								setFont(sf::Font*);
		sf::Font*							getFont(void) const;

		int									getEntry(sf::Vector2f);

		void								update(void);

	private:
		int									_w;
		int									_h;
		sf::RenderWindow*					_win;
		sf::Font*							_font;
		std::vector<Graphic::Entry*>		_menu;
		bool								_pause;

		void								_handleEvents(void);
		void								_handleKeyboard(sf::Event&);
		void								_handleMouse(sf::Event&);
		void								_drawUI(void);
};

#endif
