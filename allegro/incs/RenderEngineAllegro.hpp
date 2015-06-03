#ifndef RENDERENGINEALLEGRO_HPP
# define RENDERENGINEALLEGRO_HPP

# include "iRenderEngine.hpp"
# include <allegro5/allegro5.h>
# include <allegro5/allegro_font.h>
# include <allegro5/allegro_ttf.h>
# include <allegro5/allegro_primitives.h>

class RenderEngineAllegro : public iRenderEngine
{
	public:
		RenderEngineAllegro(int, int);
		~RenderEngineAllegro(void);

		void					setWidth(int);
		int						getWidth(void) const;
		void					setHeight(int);
		int						getHeight(void) const;

		void					clear(void);
		void					exit(void);
		void					display(void);
		int						getEvent(void);

		void					drawTile(int[3], int, int);
		void					drawText(std::string, int, int[3], int, int);
		void					drawBackground(int[3]);

	private:
		int						_w;
		int						_h;
		ALLEGRO_DISPLAY*		_win;
		ALLEGRO_EVENT_QUEUE*	_events;
};

extern "C"
{
	iRenderEngine*				loadRenderer(int, int);
	void						deleteRenderer(iRenderEngine*);
}

#endif
