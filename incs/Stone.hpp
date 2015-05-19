#ifndef STONE_HPP
# define STONE_HPP

# include "Player.hpp"

class Stone
{
	public:
		Stone(void);
		~Stone(void);

		void		setX(int);
		int			getX(void) const;
		void		setY(int);
		int			getY(void) const;
		void		setPlayer(Player*);
		Player*		getPlayer(void) const;

	private:
		int			_x;
		int			_y;
		Player*		_player;
};

#endif
