#include "RenderEngineSDL.hpp"

RenderEngineSDL::RenderEngineSDL(int width, int height)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	this->_w = width * 24;
	this->_h = height * 24 + 100;
	this->_win = SDL_CreateWindow("NIBBLER", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->_w, this->_h, SDL_WINDOW_SHOWN);
	this->_rend =  SDL_CreateRenderer(this->_win, 0, SDL_RENDERER_ACCELERATED);
}

RenderEngineSDL::~RenderEngineSDL(void)
{
}

void				RenderEngineSDL::setWidth(int width)
{
	this->_w = width;
}

int					RenderEngineSDL::getWidth(void) const
{
	return this->_w;
}

void				RenderEngineSDL::setHeight(int height)
{
	this->_h = height;
}

int					RenderEngineSDL::getHeight(void) const
{
	return this->_h;
}

void				RenderEngineSDL::drawTile(int colors[3], int x, int y)
{
	SDL_Rect rect = {y, x, 24, 24};
	SDL_SetRenderDrawColor(this->_rend, colors[0], colors[1], colors[2], 0xFF);
	SDL_RenderFillRect(this->_rend, &rect);
}

void				RenderEngineSDL::drawText(std::string content, int size, int* colors, int x, int y)
{
	(void)content;
	(void)size;
	(void)colors;
	(void)x;
	(void)y;
}

void				RenderEngineSDL::clear(void)
{
}

void				RenderEngineSDL::display(void)
{
	SDL_RenderPresent(this->_rend);
}

void				RenderEngineSDL::exit(void)
{
	SDL_DestroyWindow(this->_win);
	SDL_Quit();
}

int					RenderEngineSDL::getEvent(void)
{
	int			input = eInputs::NONE;
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				SDL_DestroyWindow(this->_win);
				input = eInputs::ESCAPE;
			}
		}
		else if (event.type == SDL_KEYDOWN)
		{
			std::cout << event.key.keysym.scancode << std::endl;
/*
			switch (event->keyboardkey.code)
			{
				case sf::Keyboard::Escape:
					input = eInputs::ESCAPE;
					break;
				case sf::Keyboard::Up:
					input = eInputs::P1_UP;
					break;
				case sf::Keyboard::Down:
					input = eInputs::P1_DOWN;
					break;
				case sf::Keyboard::Left:
					input = eInputs::P1_LEFT;
					break;
				case sf::Keyboard::Right:
					input = eInputs::P1_RIGHT;
					break;
				case sf::Keyboard::W:
					input = eInputs::P2_UP;
					break;
				case sf::Keyboard::S:
					input = eInputs::P2_DOWN;
					break;
				case sf::Keyboard::A:
					input = eInputs::P2_LEFT;
					break;
				case sf::Keyboard::D:
					input = eInputs::P2_RIGHT;
					break;
				default:
					break;
			}*/
		}
	}

	return input;
}
