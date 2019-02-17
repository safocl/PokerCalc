//#pragma once
#ifndef BOARD_H
#define BOARD_H

struct Deck;
struct HandStrengthList;

#include <vector>
#include "Card.h"
#include "Hand.h"
#include "Deck.h"
#include "defines.h"
#include "handstrength.h"

namespace lp {

class Board {
	std::unique_ptr< std::vector< Card > > board_ptr;
	uint8_t MAX_SIZE = 5;
public:
	Board();
	const std::vector< Card > & getVector() const;
	bool pushNewCardToBoard( const Hand & hero, const Hand & opp, const Card & card ) const;
	bool checkCardOnBoard( const Card & card ) const;
	void brutforcePreFlop_Flop( Deck & deck, const Hand & hero, const Hand & opp, HandStrengthList & hsl );
private:
	void genBoardCards( Deck & deck, const Hand & hero, const Hand & opp, HandStrengthList & hsl,const int &cycles_count );
	void parallel_genBoardCards( Deck & deck, const Hand & hero, const Hand & opp, HandStrengthList & hsl, const int &cycles_count );
};

}

#endif //BOARD_H