#include "Graphic.hpp"

int		main(void)
{
	Graphic graphic;

	graphic.render(*(new Board));
	return (0);
}
