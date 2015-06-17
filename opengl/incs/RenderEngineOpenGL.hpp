#ifndef RENDERENGINEOPENGL_HPP
# define RENDERENGINEOPENGL_HPP

# include "iRenderEngine.hpp"
# include <GLFW/glfw3.h>
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <FTGL/ftgl.h>

class RenderEngineOpenGL : public iRenderEngine
{
	public:
		RenderEngineOpenGL(int, int);
		~RenderEngineOpenGL(void);

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
		GLFWwindow*			_win;
		FTFont*				_font;
};

extern "C"
{
	iRenderEngine*				loadRenderer(int, int);
	void						deleteRenderer(iRenderEngine*);
}

#endif
