#ifndef GAME_HPP
# define GAME_HPP

class Game
{
	public:
		Game(void);
		Game(const Game&);
		~Game(void);

		Game&		operator=(const Game&);
};

#endif
