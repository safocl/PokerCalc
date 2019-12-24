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

#include "Deck.h"
#include "Board.h"
#include "Card.h"
#include "Hand.h"
//#include <cassert>

namespace lp {

Deck::Deck( const Board & board, const Hand & hero, const Hand & opp ) : deckArr() {
    deckArr.reserve( Deck::capacity );
    gen( board, hero, opp );
}

Deck::~Deck() {}
//---------------------------------------------------------------------------------------------------------------------------
auto Deck::operator=( Deck && other ) noexcept -> Deck & {
    this->deckArr = other.deckArr;
    other.deckArr.clear();
    return *this;
}
//---------------------------------------------------------------------------------------------------------------------------
auto Deck::getDeckArr() const -> const std::vector< Card > & { return deckArr; }
//---------------------------------------------------------------------------------------------------------------------------
auto Deck::size() const -> unsigned long { return deckArr.size(); }
//----------------------------------------------------------------------------------------
void Deck::gen( const Board & board, const Hand & hero, const Hand & opp ) {
    if ( !deckArr.empty() )
        deckArr.clear();

    for ( auto card = std::make_unique< Card >( Card::valCard::_2,
                                                Card::suitCard::_d_0x1 );
          card->getValueNum() < Card::valueSize; card->incVal() ) {
        for ( card->setSuitNum( Card::suitCard::_d_0x1 );
             card->getSuitNum() < Card::suitSize; card->incSuit() ) {
            if ( *card != hero.getLCard() && *card != hero.getRCard() &&
                *card != opp.getLCard() && *card != opp.getRCard() &&
                !board.checkCardOnBoard( *card ) ) {

                deckArr.push_back( *card );
            }
        }
    }
}
//----------------------------------------------------------------------------------------
//auto howHighterCards( const lp::Card & matchingCard ) -> uint8_t {
//    uint8_t countHighterCards = 0;
//    for ( const auto & remainingCard : deckArr )
//        if ( remainingCard.getValueNum() > matchingCard.getValueNum() )
//            ++countHighterCards;
//    return countHighterCards;
//}

} // namespace lp
