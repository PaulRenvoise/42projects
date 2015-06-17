#include "RenderEngineSDL.hpp"

RenderEngineSDL::RenderEngineSDL(int width, int height)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	this->_w = width * 24;
	this->_h = height * 24 + 100;
	this->_win = SDL_CreateWindow("NIBBLER - SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->_w, this->_h, SDL_WINDOW_SHOWN);
	this->_rend = SDL_CreateRenderer(this->_win, 0, SDL_RENDERER_ACCELERATED);
	this->_tile = new SDL_Rect;
	this->_tile->h = 24;
	this->_tile->w = 24;
	this->_tile->x = 0;
	this->_tile->y = 0;
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

void				RenderEngineSDL::drawBackground(int colors[3])
{
	this->_tile->h = this->_h;
	this->_tile->w = this->_w;
	this->_tile->x = 0;
	this->_tile->y = 0;
	SDL_SetRenderDrawColor(this->_rend, colors[0], colors[1], colors[2], 0xFF);
	SDL_RenderFillRect(this->_rend, this->_tile);
	this->_tile->h = 24;
	this->_tile->w = 24;
}

void				RenderEngineSDL::drawTile(int colors[3], int x, int y)
{
	this->_tile->x = y * 24;
	this->_tile->y = x * 24;
	SDL_SetRenderDrawColor(this->_rend, colors[0], colors[1], colors[2], 0xFF);
	SDL_RenderFillRect(this->_rend, this->_tile);
}

void				RenderEngineSDL::drawText(std::string content, int size, int colors[3], int x, int y)
{
	TTF_Font*		font = TTF_OpenFont("./font/Square.ttf", size);
	SDL_Color		color = {static_cast<Uint8>(colors[0]), static_cast<Uint8>(colors[1]), static_cast<Uint8>(colors[2]), 0xFF};
	SDL_Surface*	surface = TTF_RenderText_Solid(font, content.c_str(), color);
	SDL_Texture*	texture = SDL_CreateTextureFromSurface(this->_rend, surface);
	SDL_Rect		rect;
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	rect.x = x;
	rect.y = y + 12;
	SDL_RenderCopy(this->_rend, texture, NULL, &rect);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}

void				RenderEngineSDL::clear(void)
{
	SDL_RenderClear(this->_rend);
}

void				RenderEngineSDL::display(void)
{
	SDL_RenderPresent(this->_rend);
}

void				RenderEngineSDL::exit(void)
{
	SDL_DestroyWindow(this->_win);
	SDL_Quit();
	TTF_Quit();
	this->~RenderEngineSDL();
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
			switch (event.key.keysym.scancode)
			{
				case SDL_SCANCODE_ESCAPE:
					input = eInputs::ESCAPE;
					break;
				case SDL_SCANCODE_1:
					input = eInputs::KEY_1;
					break;
				case SDL_SCANCODE_2:
					input = eInputs::KEY_2;
					break;
				case SDL_SCANCODE_3:
					input = eInputs::KEY_3;
					break;
				case SDL_SCANCODE_UP:
					input = eInputs::P1_UP;
					break;
				case SDL_SCANCODE_DOWN:
					input = eInputs::P1_DOWN;
					break;
				case SDL_SCANCODE_LEFT:
					input = eInputs::P1_LEFT;
					break;
				case SDL_SCANCODE_RIGHT:
					input = eInputs::P1_RIGHT;
					break;
				case SDL_SCANCODE_W:
					input = eInputs::P2_UP;
					break;
				case SDL_SCANCODE_S:
					input = eInputs::P2_DOWN;
					break;
				case SDL_SCANCODE_A:
					input = eInputs::P2_LEFT;
					break;
				case SDL_SCANCODE_D:
					input = eInputs::P2_RIGHT;
					break;
				default:
					break;
			}
		}
	}

	return input;
}

iRenderEngine*				loadRenderer(int width, int height)
{
	return new RenderEngineSDL(width, height);
}

void						deleteRenderer(iRenderEngine* renderer)
{
	renderer->exit();
	delete renderer;
}
