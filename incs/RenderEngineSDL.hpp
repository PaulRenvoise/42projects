#ifndef RENDERENGINESDL_HPP
# define RENDERENGINESDL_HPP

# include "iRenderEngine.hpp"
# include <SDL.h>
# include <SDL_ttf.h>

class RenderEngineSDL : public iRenderEngine
{
	public:
		RenderEngineSDL(int, int);
		~RenderEngineSDL(void);

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
		SDL_Window*			_win;
		SDL_Renderer*		_rend;
		SDL_Rect*			_tile;
};

extern "C"
{
	iRenderEngine*				loadRenderer(int, int);
	void						deleteRenderer(iRenderEngine*);
}

#endif
