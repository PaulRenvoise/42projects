#include "RenderEngineAllegro.hpp"

RenderEngineAllegro::RenderEngineAllegro(int width, int height)
{
	al_init();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	this->_w = width * 24;
	this->_h = height * 24 + 100;
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	this->_win = al_create_display(this->_w, this->_h);
	al_set_window_title(this->_win, "NIBBLER - ALLEGRO");
	this->_events = al_create_event_queue();
	al_register_event_source(this->_events, al_get_display_event_source(this->_win));
	al_register_event_source(this->_events, al_get_keyboard_event_source());
}

RenderEngineAllegro::~RenderEngineAllegro(void)
{
}

void				RenderEngineAllegro::setWidth(int width)
{
	this->_w = width;
}

int					RenderEngineAllegro::getWidth(void) const
{
	return this->_w;
}

void				RenderEngineAllegro::setHeight(int height)
{
	this->_h = height;
}

int					RenderEngineAllegro::getHeight(void) const
{
	return this->_h;
}

void				RenderEngineAllegro::drawBackground(int colors[3])
{
	al_draw_filled_rectangle(0, 0, this->_w, this->_h, al_map_rgb(colors[0], colors[1], colors[2]));
}

void				RenderEngineAllegro::drawTile(int colors[3], int x, int y)
{
	al_draw_filled_rectangle(y * 24, x * 24, y * 24 + 24, x * 24 + 24, al_map_rgb(colors[0], colors[1], colors[2]));
}

void				RenderEngineAllegro::drawText(std::string content, int size, int colors[3], int x, int y)
{
	ALLEGRO_FONT*	font = al_load_ttf_font("./font/Square.ttf", size, 0);
	al_draw_text(font, al_map_rgb(colors[0], colors[1], colors[2]), x, y + 12, 0, content.c_str());
	al_destroy_font(font);
}

void				RenderEngineAllegro::clear(void)
{
	al_set_target_bitmap(al_get_backbuffer(this->_win));
	al_clear_to_color(al_map_rgb(0,0,0));
}

void				RenderEngineAllegro::display(void)
{
	al_flip_display();
}

void				RenderEngineAllegro::exit(void)
{
	al_destroy_display(this->_win);
	al_destroy_event_queue(this->_events);
	this->~RenderEngineAllegro();
}

int					RenderEngineAllegro::getEvent(void)
{
	int				input = eInputs::NONE;
	ALLEGRO_EVENT	event;

	while (!al_is_event_queue_empty(this->_events))
	{
		bool isEvent = al_get_next_event(this->_events, &event);
		if (isEvent && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			al_destroy_display(this->_win);
			input = eInputs::ESCAPE;
		}
		else if (isEvent && event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (event.keyboard.keycode)
			{
				case ALLEGRO_KEY_ESCAPE:
					input = eInputs::ESCAPE;
					break;
				case ALLEGRO_KEY_1:
					input = eInputs::KEY_1;
					break;
				case ALLEGRO_KEY_2:
					input = eInputs::KEY_2;
					break;
				case ALLEGRO_KEY_3:
					input = eInputs::KEY_3;
					break;
				case ALLEGRO_KEY_UP:
					input = eInputs::P1_UP;
					break;
				case ALLEGRO_KEY_DOWN:
					input = eInputs::P1_DOWN;
					break;
				case ALLEGRO_KEY_LEFT:
					input = eInputs::P1_LEFT;
					break;
				case ALLEGRO_KEY_RIGHT:
					input = eInputs::P1_RIGHT;
					break;
				case ALLEGRO_KEY_W:
					input = eInputs::P2_UP;
					break;
				case ALLEGRO_KEY_S:
					input = eInputs::P2_DOWN;
					break;
				case ALLEGRO_KEY_A:
					input = eInputs::P2_LEFT;
					break;
				case ALLEGRO_KEY_D:
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
	return new RenderEngineAllegro(width, height);
}

void						deleteRenderer(iRenderEngine* renderer)
{
	renderer->exit();
	delete renderer;
}
