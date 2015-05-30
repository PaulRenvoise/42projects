#ifndef PLAYER_HPP
# define PLAYER_HPP

# include <iostream>
# include "Snake.hpp"
# include "Tile.hpp"

class Player
{
	public:
		Player(int, int);
		~Player(void);

		void				setSnake(Snake*);
		Snake*				getSnake(void) const;

		void				addPoints(int);
		int					getPoints(void) const;

		void				setSnakeDirection(int);
		int					getSnakeDirection(void) const;

		void				setSnakeNext(int);
		int					getSnakeNext(void) const;

		void				setSnakeHead(std::pair<int, int>);
		std::pair<int, int>	getSnakeHead(void) const;

		void				setSnakeSpeed(double);
		double				getSnakeSpeed(void) const;

		void				setSnakeDelta(double);
		double				getSnakeDelta(void) const;

		void				moveSnake(void);
		void				setSnakeEat(Tile*);
		void				setSnakeStarve(void);

	private:
		Snake*				_snake;
		int					_points;
};

#endif
