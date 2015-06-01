#ifndef RENDERENGINESFML_HPP
# define RENDERENGINESFML_HPP

# include "iRenderEngine.hpp"
# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>

class RenderEngineSFML : public iRenderEngine
{
	public:
		RenderEngineSFML(int, int);
		~RenderEngineSFML(void);

		void				setWidth(int);
		int					getWidth(void) const;
		void				setHeight(int);
		int					getHeight(void) const;

		void				clear(void);
		void				exit(void);
		void				display(void);
		int					getEvent(void);

		void				drawTile(int[3], int, int);
		void				drawText(std::string, int, int[3], int, int);
		void				drawBackground(int[3]);

	private:
		int					_w;
		int					_h;
		sf::RenderWindow*	_win;
		sf::Font*			_font;
		sf::RectangleShape*	_tile;
		sf::Text*			_text;
};

#endif
