#ifndef TILE_HPP
# define TILE_HPP

# include <iostream>

enum	eType
{
	EMPTY = 150,
	WALL,
	HOLE,
	FOOD,
	BONUS
};

class Tile
{
	public:
		Tile(void);
		Tile(int);
		Tile(const Tile&);
		~Tile(void);

		Tile&				operator=(const Tile&);

		void				setType(int);
		int					getType(void) const;

		void				setValue(int);
		int					getValue(void) const;

		void				setOut(std::pair<int, int>);
		std::pair<int, int>	getOut(void) const;

		void				dump(void) const;

	private:
		int					_type;
		int					_value;
		std::pair<int, int>	_out;
};

#endif
