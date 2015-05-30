#ifndef SNAKE_HPP
# define SNAKE_HPP

# include <iostream>
# include <vector>
# include <map>

enum	eDir
{
	UP = 100,
	DOWN,
	LEFT,
	RIGHT
};

class Snake
{
	public:
		Snake(int, int);
		~Snake(void);

		void								setDirection(int);
		int									getDirection(void) const;

		void								setNext(int);
		int									getNext(void) const;

		void								setSnake(std::vector<std::pair<int, int>>&);
		std::vector<std::pair<int, int>>	getSnake(void) const;
		void								setHead(std::pair<int, int>&);
		std::pair<int, int>					getHead(void) const;

		void								setEat(bool);
		bool								hasEat(void) const;

		void								setSpeed(double);
		double								getSpeed(void) const;

		void								setDelta(double);
		double								getDelta(void) const;

		void								move(void);

	private:
		int									_dir;
		int									_next;
		std::vector<std::pair<int, int>>	_snake;
		bool								_eat;
		double								_speed;
		double								_delta;
		std::map<int, std::map<int, int>>	_convert =
			{
				{eDir::UP, {
					{eDir::UP, eDir::UP},
					{eDir::DOWN, eDir::UP},
					{eDir::LEFT, eDir::LEFT},
					{eDir::RIGHT, eDir::RIGHT}
				}},
				{eDir::DOWN, {
					{eDir::UP, eDir::DOWN},
					{eDir::DOWN, eDir::DOWN},
					{eDir::LEFT, eDir::LEFT},
					{eDir::RIGHT, eDir::RIGHT}
				}},
				{eDir::LEFT, {
					{eDir::UP, eDir::UP},
					{eDir::DOWN, eDir::DOWN},
					{eDir::LEFT, eDir::LEFT},
					{eDir::RIGHT, eDir::LEFT}
				}},
				{eDir::RIGHT, {
					{eDir::UP, eDir::UP},
					{eDir::DOWN, eDir::DOWN},
					{eDir::LEFT, eDir::RIGHT},
					{eDir::RIGHT, eDir::RIGHT}
				}}
			};
};

#endif
