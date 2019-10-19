#include "Hand.h"
#include "Card.h"
#include "handstrength.h"
#include <cassert>

namespace lp {
Hand::Hand( const Hand & other ) : lCard( other.lCard ), rCard( other.rCard ){};
//---------------------------------------------------------------------------------------------------------------------------
// Hand::Hand() : lCard( std::make_unique< Card >() ), rCard( std::make_unique< Card >() ) {}
//---------------------------------------------------------------------------------------------------------------------------
Hand::Hand( Hand && other ) : lCard( std::move( other.lCard ) ), rCard( std::move( other.rCard ) ) {
    other.lCard.setCard( Card::valCard::NODEF, Card::suitCard::NODEF );
    other.rCard.setCard( Card::valCard::NODEF, Card::suitCard::NODEF );
}
//---------------------------------------------------------------------------------------------------------------------------
Hand::Hand( Card::valCard && __lCardV, Card::suitCard && __lCardS, Card::valCard && __rCardV,
            Card::suitCard && __rCardS )
    : lCard( std::move( __lCardV ), std::move( __lCardS ) ), rCard( std::move( __rCardV ), std::move( __rCardS ) ) {
    assert( ( ( __lCardV != __rCardV ) || ( __lCardS != __rCardS ) ) && "identical cards" );
}
//---------------------------------------------------------------------------------------------------------------------------
Hand::Hand( const std::string __lCardStr, const std::string __rCardStr ) : lCard( __lCardStr ), rCard( __rCardStr ) {
    assert( __lCardStr != __rCardStr && "identical cards" );
}
//---------------------------------------------------------------------------------------------------------------------------
Hand::~Hand() {}
//---------------------------------------------------------------------------------------------------------------------------
void Hand::setHand( const std::string __lCard, const std::string __rCard ) {
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
const Card & Hand::getLCard() const { return lCard; }
//---------------------------------------------------------------------------------------------------------------------------
const Card & Hand::getRCard() const { return rCard; }
//---------------------------------------------------------------------------------------------------------------------------
const Card & Hand::getHigerCard() const { return lCard.getValueNum() > rCard.getValueNum() ? lCard : rCard; }
//---------------------------------------------------------------------------------------------------------------------------
bool Hand::isPair() const noexcept { return lCard.getValueNum() == rCard.getValueNum(); }
//---------------------------------------------------------------------------------------------------------------------------
bool Hand::operator==( const Hand & other ) const {
    return ( ( ( this->lCard == other.lCard ) && ( this->rCard == other.rCard ) ) ||
             ( ( this->lCard == other.rCard ) && ( this->rCard == other.lCard ) ) );
}
//---------------------------------------------------------------------------------------------------------------------------
bool Hand::operator!=( const Hand & other ) const {
    return !( ( ( this->lCard == other.lCard ) && ( this->rCard == other.rCard ) ) ||
              ( ( this->lCard == other.rCard ) && ( this->rCard == other.lCard ) ) );
}
//---------------------------------------------------------------------------------------------------------------------------
Hand & Hand::operator=( const Hand & other ) {
    this->lCard.setCard( other.lCard );
    this->rCard.setCard( other.rCard );
    return *this;
}
//---------------------------------------------------------------------------------------------------------------------------
Hand & Hand::operator=( Hand && other ) {
    this->lCard.setCard( std::move( other.lCard ) );
    this->rCard.setCard( std::move( other.rCard ) );
    other.lCard.setCard( Card::valCard::NODEF, Card::suitCard::NODEF );
    other.rCard.setCard( Card::valCard::NODEF, Card::suitCard::NODEF );
    return *this;
}

} // namespace lp