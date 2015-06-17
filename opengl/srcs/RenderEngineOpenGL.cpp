#include "RenderEngineOpenGL.hpp"

RenderEngineOpenGL::RenderEngineOpenGL(int width, int height)
{
	glfwInit();
	this->_w = width * 24;
	this->_h = height * 24 + 100;
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_REFRESH_RATE, 60);
	this->_win = glfwCreateWindow(this->_w, this->_h, "NIBBLER - OPENGL", NULL, NULL);
	if (!this->_win)
		std::cout << "ERROR" << std::endl;
	glfwMakeContextCurrent(this->_win);
	glfwSwapInterval(0);
	glOrtho(0, this->_w, this->_h, 0, 0, 1);
}

RenderEngineOpenGL::~RenderEngineOpenGL(void)
{
}

void				RenderEngineOpenGL::setWidth(int width)
{
	this->_w = width;
}

int					RenderEngineOpenGL::getWidth(void) const
{
	return this->_w;
}

void				RenderEngineOpenGL::setHeight(int height)
{
	this->_h = height;
}

int					RenderEngineOpenGL::getHeight(void) const
{
	return this->_h;
}

void				RenderEngineOpenGL::drawBackground(int colors[3])
{
	(void)colors;
}

void				RenderEngineOpenGL::drawTile(int colors[3], int x, int y)
{
	x *= 24;
	y *= 24;
	glColor3f((float)(colors[0] / 255.0f), (float)(colors[1] / 255.0f), (float)(colors[2] / 255.0f));
	glRectf(y, x, y + 24, x + 24);
	glFlush();
}

void				RenderEngineOpenGL::drawText(std::string content, int size, int colors[3], int x, int y)
{
	(void)content;
	(void)size;
	(void)colors;
	(void)x;
	(void)y;
}

void				RenderEngineOpenGL::clear(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void				RenderEngineOpenGL::display(void)
{
	glfwSwapBuffers(this->_win);
}

void				RenderEngineOpenGL::exit(void)
{
	glfwTerminate();
	glfwDestroyWindow(this->_win);
	this->~RenderEngineOpenGL();
}

int					RenderEngineOpenGL::getEvent(void)
{
	int			input = eInputs::NONE;

	glfwPollEvents();

	if (glfwGetKey(this->_win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwDestroyWindow(this->_win);
		input = eInputs::ESCAPE;
	}
	else if (glfwGetKey(this->_win, GLFW_KEY_1) == GLFW_PRESS)
		input = eInputs::KEY_1;
	else if (glfwGetKey(this->_win, GLFW_KEY_2) == GLFW_PRESS)
		input = eInputs::KEY_2;
	else if (glfwGetKey(this->_win, GLFW_KEY_3) == GLFW_PRESS)
		input = eInputs::KEY_3;
	else if (glfwGetKey(this->_win, GLFW_KEY_UP) == GLFW_PRESS)
		input = eInputs::P1_UP;
	else if (glfwGetKey(this->_win, GLFW_KEY_DOWN) == GLFW_PRESS)
		input = eInputs::P1_DOWN;
	else if (glfwGetKey(this->_win, GLFW_KEY_LEFT) == GLFW_PRESS)
		input = eInputs::P1_LEFT;
	else if (glfwGetKey(this->_win, GLFW_KEY_RIGHT) == GLFW_PRESS)
		input = eInputs::P1_RIGHT;
	else if (glfwGetKey(this->_win, GLFW_KEY_W) == GLFW_PRESS)
		input = eInputs::P2_UP;
	else if (glfwGetKey(this->_win, GLFW_KEY_S) == GLFW_PRESS)
		input = eInputs::P2_DOWN;
	else if (glfwGetKey(this->_win, GLFW_KEY_A) == GLFW_PRESS)
		input = eInputs::P2_LEFT;
	else if (glfwGetKey(this->_win, GLFW_KEY_D) == GLFW_PRESS)
		input = eInputs::P2_RIGHT;

	return input;
}

iRenderEngine*				loadRenderer(int width, int height)
{
	return new RenderEngineOpenGL(width, height);
}

void						deleteRenderer(iRenderEngine* renderer)
{
	renderer->exit();
	delete renderer;
}
