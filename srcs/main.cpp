#include "GameEngine.hpp"
#include "Parser.hpp"

enum	eOptions
{
	UNKNOWN,
	HELP,
	WIDTH,
	HEIGHT,
	PLAYERS,
	LIBRARY
};

const option::Descriptor	usage[] =
{
	{UNKNOWN, 0, "", "", option::Arg::None, "Usage:\n nibbler [--help] [-w WIDTH] [-h HEIGHT]" },
	{HELP, 0, "", "help", option::Arg::None, "\nOptions:\n --help \t Display this help." },
	{WIDTH, 0, "w", "width", option::Arg::NumericAbove4, " -w, --width \t Specify the game area's width, must be > 4 (default 50)." },
	{HEIGHT, 0, "h", "height", option::Arg::NumericAbove4, " -h, --height \t Specify the game area's height, must be > 4 (default 40)." },
	{PLAYERS, 0, "p", "players", option::Arg::Numeric1Or2, " -p, --players \t Specify the number of players for the game, must be 1 or 2 (default 1)." },
	{LIBRARY, 0, "l", "library", option::Arg::Library, " -l, --library \t Specify the graphic library for the game, must be allegro, sdl or sfml (default sfml)." },
	{0, 0, 0, 0, 0, 0}
};

int		main(int ac, char** av)
{
	ac -= (ac > 0);
	av += (ac > 0);

	option::Stats	stats(usage, ac, av);
	option::Option*	options = new option::Option[stats.options_max];
	option::Option*	buffer = new option::Option[stats.buffer_max];
	option::Parser	parser(usage, ac, av, options, buffer);
	int				width = 50;
	int				height = 40;
	int				players = 1;
	iRenderEngine*	renderer = NULL;
	void*			handle;
	iRenderEngine*	(*factory)(int, int);
	std::string		path("./");

	if (parser.nonOptionsCount() || options[UNKNOWN])
	{
		std::cerr << "nibbler: illegal option -- " << std::string((options[UNKNOWN]) ? options[UNKNOWN].name : parser.nonOption(0)) << std::endl;
		std::exit(-1);
	}
	if (parser.error())
		std::exit(-1);

	if (options[HELP])
	{
		option::printUsage(std::cout, usage);
		std::exit(0);
	}
	else
	{
		if (options[WIDTH])
			width = std::atoi(options[WIDTH].arg);
		if (options[HEIGHT])
			height = std::atoi(options[HEIGHT].arg);
		if (options[PLAYERS])
			players = std::atoi(options[PLAYERS].arg);
		if (options[LIBRARY])
		{
			path.append(options[LIBRARY].arg);
			path.append(".so");
		}
		else
			path.append("sfml.so");
		handle = dlopen(path.c_str(), RTLD_LAZY | RTLD_LOCAL);
		if (!handle)
			std::cout << "ERROR HANDLE" << std::endl;
		factory = (iRenderEngine *(*)(int, int))dlsym(handle, "loadRenderer");
		if (!factory)
			std::cout << "ERROR FACTORY" << std::endl;
		renderer = factory(width, height);
	}

	std::srand(std::time(0));

	GameEngine game(width, height, players, renderer);

	game.run();

	delete[] options;
	delete[] buffer;

	return (0);
}
