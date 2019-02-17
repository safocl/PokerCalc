#include "Deck.h"
//#include "Board.h"
#include <cassert>



//---------------------------------------------------------------------------------------------------------------------------
Deck::Range::Range() : minPos( -1 ), maxPos( -1 ) { }
//---------------------------------------------------------------------------------------------------------------------------
Deck::Range::Range( const int minPos, const int maxPos ) : minPos( minPos ), maxPos( maxPos ) { 
	assert( minPos <= Deck::SIZE_DeckArr && "invalid minPos" );
	assert( maxPos <= Deck::SIZE_DeckArr && "invalid maxPos" );
}
//---------------------------------------------------------------------------------------------------------------------------
Deck::Deck( const int minPos, const int maxPos ) : range( minPos, maxPos ) { deckArr.reserve( Deck::SIZE_DeckArr ); }
//---------------------------------------------------------------------------------------------------------------------------
Deck::Deck() : deckArr() { deckArr.reserve( Deck::SIZE_DeckArr ); }
//---------------------------------------------------------------------------------------------------------------------------
//Deck::Deck(const Deck & other){this->deckArr = other.deckArr;}
//---------------------------------------------------------------------------------------------------------------------------
Deck::Deck( Deck && other ) : deckArr( other.deckArr ) { other.deckArr.clear(); }
//---------------------------------------------------------------------------------------------------------------------------
bool Deck::Range::isValid() const { return ( minPos > -1 ) && ( maxPos > -1 ); }
//---------------------------------------------------------------------------------------------------------------------------
int Deck::getMinPos () const { 
	assert(range.isValid() && "invalid minPos or maxPos");
	return range.minPos;
}
//---------------------------------------------------------------------------------------------------------------------------
int Deck::getMaxPos () const { 
	assert(range.isValid() && "invalid minPos or maxPos");
	return range.maxPos;
}
//---------------------------------------------------------------------------------------------------------------------------
Deck & Deck::operator = ( Deck && other ) {
    this->deckArr = other.deckArr;
    other.deckArr.clear();                                     
    return *this;
}
//---------------------------------------------------------------------------------------------------------------------------
const std::vector< Card > & Deck::getDeckArr() const { return deckArr; }
//---------------------------------------------------------------------------------------------------------------------------
unsigned long Deck::size() const { return deckArr.size(); }
//---------------------------------------------------------------------------------------------------------------------------
//const int & Deck::capacity() const {return Deck::SIZE_DeckArr;}
//---------------------------------------------------------------------------------------------------------------------------
void Deck::gen( const Board & board, const Hand & hero, const Hand & opp ) {
	if ( ! range.isValid() ) {
		range.minPos = 0;
		if ( hero == opp )
			range.maxPos = 50;
		else
			range.maxPos = 48;
	}
	if ( !deckArr.empty() )
        deckArr.clear();

    for ( auto card = std::make_unique< Card >( Card::valCard::_2, Card::suitCard::_d_0x1 ); 
		  card->getValueNum() < Card::sizeValueCardArr; card->inc_val() ) {
		for ( card->setSuitNum( Card::suitCard::_d_0x1 ); card->getSuitNum() < Card::sizeSuitCardArr; card->inc_suit() ) {
			if ( *card != hero.getCard1() && 
               *card != hero.getCard2() && 
               *card != opp.getCard1() && 
               *card != opp.getCard2() &&
               !board.checkCardOnBoard( *card ) ) {
               deckArr.push_back( *card );
            }
        }
    }
}