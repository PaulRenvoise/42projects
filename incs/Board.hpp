#ifndef BOARD_HPP
# define BOARD_HPP

class Board
{
	public:
		Board(void);
		Board(const Board&);
		~Board(void);

		Board&		operator=(const Board&);
};

#endif
