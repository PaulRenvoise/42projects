#ifndef IRENDERENGINE_HPP
# define IRENDERENGINE_HPP

# include <vector>
# include <iostream>
# include "Tile.hpp"

enum	eInputs
{
	NONE = 50,
	ESCAPE,
	KEY_1,
	KEY_2,
	KEY_3,
	P1_UP,
	P1_DOWN,
	P1_LEFT,
	P1_RIGHT,
	P2_UP,
	P2_DOWN,
	P2_LEFT,
	P2_RIGHT
};

class iRenderEngine
{
	public:
		virtual ~iRenderEngine(void){};
		virtual void				setWidth(int) = 0;
		virtual int					getWidth(void) const = 0;
		virtual void				setHeight(int) = 0;
		virtual int					getHeight(void) const = 0;

		virtual void				clear(void) = 0;
		virtual void				exit(void) = 0;
		virtual void				display(void) = 0;
		virtual int					getEvent(void) = 0;

		virtual void				drawTile(int[3], int, int) = 0;
		virtual void				drawText(std::string, int, int[3], int, int) = 0;
		virtual void				drawBackground(int[3]) = 0;

	protected:
		int					_w;
		int					_h;
};

#endif
