#ifndef PLAYER_HPP
# define PLAYER_HPP

# include <map>
# include "iRenderEngine.hpp"

enum	eDir
{
	UP = 100,
	DOWN,
	LEFT,
	RIGHT
};

class Player
{
	public:
		Player(int, int, int);
		~Player(void);

		void								setId(int);
		int									getId(void) const;
		void								setPoints(int);
		int									getPoints(void) const;
		void								setSnake(std::vector<std::pair<int, int>>&);
		std::vector<std::pair<int, int>>	getSnake(void) const;
		void								setHead(std::pair<int, int>);
		std::pair<int, int>					getHead(void) const;
		void								setDir(int);
		int									getDir(void) const;
		void								setNext(int);
		int									getNext(void) const;
		void								setEat(bool);
		bool								getEat(void) const;
		void								setSpeed(double);
		double								getSpeed(void) const;
		void								setDelta(double);
		double								getDelta(void) const;

		void								move(void);
		void								eat(Tile*);
		void								draw(iRenderEngine*);

	private:
		int									_id;
		int									_points;
		std::vector<std::pair<int, int>>	_snake;
		int									_dir;
		int									_next;
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
