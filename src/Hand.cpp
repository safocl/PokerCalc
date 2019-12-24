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

#include "Hand.h"
#include "Card.h"
#include "handstrength.h"
#include <cassert>
#include <stdexcept>

namespace lp {
// Hand::Hand( const Hand & other ) : , = default;;
//---------------------------------------------------------------------------------------------------------------------------
// Hand::Hand() : lCard( std::make_unique< Card >() ), rCard( std::make_unique< Card >() ) {}
//---------------------------------------------------------------------------------------------------------------------------
Hand::Hand( Hand && other ) noexcept : lCard( std::move( other.lCard ) ), rCard( std::move( other.rCard ) ) {
    other.lCard.setCard( Card::valCard::NODEF, Card::suitCard::NODEF );
    other.rCard.setCard( Card::valCard::NODEF, Card::suitCard::NODEF );
}
//---------------------------------------------------------------------------------------------------------------------------
Hand::Hand( Card::valCard __lCardV, Card::suitCard __lCardS, Card::valCard __rCardV,
            Card::suitCard __rCardS )
    : lCard( std::move( __lCardV ), std::move( __lCardS ) ), rCard( std::move( __rCardV ), std::move( __rCardS ) ) {
    //    assert( ( ( __lCardV != __rCardV ) || ( __lCardS != __rCardS ) ) && "identical cards" );
    // Access of moved variable '__lCardV'. [accessMoved]
}
//---------------------------------------------------------------------------------------------------------------------------
Hand::Hand( const std::string & __lCardStr, const std::string & __rCardStr )
    : lCard( __lCardStr ), rCard( __rCardStr ) {
    assert( __lCardStr != __rCardStr && "identical cards" );
}
//---------------------------------------------------------------------------------------------------------------------------
// Hand::~Hand() = default;
//---------------------------------------------------------------------------------------------------------------------------
void Hand::setHand( const std::string & __lCard, const std::string & __rCard ) {
    lCard.setCard( __lCard );
    rCard.setCard( __rCard );
}
//---------------------------------------------------------------------------------------------------------------------------
void Hand::setHand( Card::valCard __lCardV, Card::suitCard __lCardS, Card::valCard __rCardV, Card::suitCard __rCardS ) {
    lCard.setCard( __lCardV, __lCardS );
    rCard.setCard( __rCardV, __rCardS );
}
//---------------------------------------------------------------------------------------------------------------------------
void Hand::setHand( const Card & __lCard, const Card & __rCard ) {
    lCard.setCard( __lCard );
    rCard.setCard( __rCard );
}
//---------------------------------------------------------------------------------------------------------------------------
// Получение значения руки в переменные типа char
void Hand::getHand( std::string & __lCardStr, std::string & __rCardStr ) const {
    __lCardStr = lCard.getString();
    __rCardStr = rCard.getString();
}
//---------------------------------------------------------------------------------------------------------------------------
void Hand::getCards( Card & __lCard, Card & __rCard ) const {
    __lCard.setCard( lCard );
    __rCard.setCard( rCard );
}
//---------------------------------------------------------------------------------------------------------------------------
auto Hand::getLCard() const -> const Card & { return lCard; }
//---------------------------------------------------------------------------------------------------------------------------
auto Hand::getRCard() const -> const Card & { return rCard; }
//---------------------------------------------------------------------------------------------------------------------------
auto Hand::getHigerCard() const -> const Card & { return lCard.getValueNum() > rCard.getValueNum() ? lCard : rCard; }

auto Hand::getLowerCard() const -> const Card & { return lCard.getValueNum() < rCard.getValueNum() ? lCard : rCard; }
//---------------------------------------------------------------------------------------------------------------------------
auto Hand::isPair() const noexcept -> bool { return lCard.getValueNum() == rCard.getValueNum(); }

auto Hand::isSuited() const noexcept -> bool { return lCard.getSuitNum() == rCard.getSuitNum(); }
//---------------------------------------------------------------------------------------------------------------------------
auto Hand::operator==( const Hand & other ) const -> bool {
    return ( ( ( this->lCard == other.lCard ) && ( this->rCard == other.rCard ) ) ||
             ( ( this->lCard == other.rCard ) && ( this->rCard == other.lCard ) ) );
}
//---------------------------------------------------------------------------------------------------------------------------
auto Hand::operator!=( const Hand & other ) const -> bool {
    return !( ( ( this->lCard == other.lCard ) && ( this->rCard == other.rCard ) ) ||
              ( ( this->lCard == other.rCard ) && ( this->rCard == other.lCard ) ) );
}
//---------------------------------------------------------------------------------------------------------------------------
// auto Hand::operator=( const Hand & other ) -> Hand & {
//    this->lCard.setCard( other.lCard );
//    this->rCard.setCard( other.rCard );
//    return *this;
//}
//---------------------------------------------------------------------------------------------------------------------------
auto Hand::operator=( Hand && other ) noexcept -> Hand & {
    this->lCard.setCard( other.lCard );
    this->rCard.setCard( other.rCard );
    other.lCard.setCard( Card::valCard::NODEF, Card::suitCard::NODEF );
    other.rCard.setCard( Card::valCard::NODEF, Card::suitCard::NODEF );
    return *this;
}

auto Hand::getFlushCard(const uint32_t matchingCardSuitN) const -> const Card & {

    if ( isSuited() )
        throw std::runtime_error("hand is suited");
    else if ( lCard.getSuitNum() == matchingCardSuitN )
        return lCard;
    else if ( rCard.getSuitNum() == matchingCardSuitN )
        return rCard;
    else
        throw std::runtime_error("no match flush card");
}

} // namespace lp
