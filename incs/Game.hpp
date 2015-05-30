#ifndef GAME_HPP
# define GAME_HPP

# include "Graphic.hpp"
# include "Player.hpp"
# include "Board.hpp"

enum	states
{
	INIT,
	ONGOING,
	PAUSE,
	
}

class Game
{
	public:
		Game(void);
		~Game(void);

		void			setGraphic(Graphic*);
		Graphic*		getGraphic(void) const;
		void			setPlayer1(Player*);
		Player*			getPlayer1(void) const;
		void			setPlayer2(Player*);
		Player*			getPlayer2(void) const;
		void			setBoard(Board*);
		Board*			getBoard(void) const;

		void			run(void);

	private:
		Graphic*		_graphic;
		Player*			_player1;
		Player*			_player2;
		Board*			_board;
		int				_state;
};

#endif
