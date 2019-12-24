namespace lp {
struct Card;
struct Deck;
class Board;
class Combo;
struct EV;
class Eval;
struct Hand;
class HandStrength;
} // namespace lp

#include "combo.h"
#include "handstrength.h"
#include <algorithm>
#include <cassert>

namespace lp {

std::vector< Card > sortCards( std::vector< Card > combo ) {
    Card temp_card;

    for ( uint8_t count = 0; count < combo.size(); ++count ) {
        for ( uint8_t subcount = count + 1; subcount < combo.size(); ++subcount ) {
            if ( combo.at( count ) > combo.at( subcount ) ) {
                temp_card = combo.at( count );
                combo.at( count ) = combo.at( subcount );
                combo.at( subcount ) = temp_card;
            }
        }
    }

    return combo;
}

//---------------------------------------------------------------------------------------------------------------------------
Combo::Combo( const Hand & hand, const Board & board ) : combo( std::vector< Card >{board.getBoard()} ) {
    combo.reserve( 7 );
    combo.push_back( hand.getLCard() );
    combo.push_back( hand.getRCard() );
}

} // namespace lp