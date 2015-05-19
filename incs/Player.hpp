#ifndef PLAYER_HPP
# define PLAYER_HPP

class Player
{
	public:
		Player(void);
		~Player(void);

		void			setActive(bool);
		bool			isActive(void) const;

	private:
		bool	_active;
};

#endif
