#ifndef PLAYER_HPP
# define PLAYER_HPP

class Player
{
	public:
		Player(void);
		Player(const Player&);
		~Player(void);

		Player&		operator=(const Player&);
};

#endif
