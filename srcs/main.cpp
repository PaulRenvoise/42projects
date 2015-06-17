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
	{WIDTH, 0, "w", "width", option::Arg::Width, " -w, --width \t Specify the game area's width, must be between 20 and 104 (default 50)." },
	{HEIGHT, 0, "h", "height", option::Arg::Height, " -h, --height \t Specify the game area's height, must be between 12 and 55 (default 40)." },
	{PLAYERS, 0, "p", "players", option::Arg::Players, " -p, --players \t Specify the number of players for the game, must be 1 or 2 (default 1)." },
	{LIBRARY, 0, "l", "library", option::Arg::Library, " -l, --library \t Specify the graphic library for the game, must be sfml, sdl, allegro or ncurses (default sfml)." },
	{0, 0, 0, 0, 0, 0}
};

int		main(int argc, char **argv)
{
	argc -= (argc > 0);
	argv += (argc > 0);

	option::Stats	stats(usage, argc, argv);
	option::Option*	options = new option::Option[stats.options_max];
	option::Option*	buffer = new option::Option[stats.buffer_max];
	option::Parser	parser(usage, argc, argv, options, buffer);
	int				width = 50;
	int				height = 40;
	int				players = 1;
	iRenderEngine*	renderer = NULL;
	void*			handle;
	iRenderEngine*	(*factory)(int, int);

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
			handle = dlopen(options[LIBRARY].arg, RTLD_LAZY | RTLD_LOCAL);
		else
			handle = dlopen("sfml.so", RTLD_LAZY | RTLD_LOCAL);
		if (!handle)
			std::cout << "nibbler: error: " << dlerror() << std::endl;
		factory = (iRenderEngine *(*)(int, int))dlsym(handle, "loadRenderer");
		if (!factory)
			std::cout << "nibbler: error: " << dlerror() << std::endl;
		renderer = factory(width, height);
	}

	std::srand(std::time(0));

	GameEngine game(width, height, players, renderer);

	game.run();

	delete[] options;
	delete[] buffer;

	return (0);
}
