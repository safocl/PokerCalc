#include "Hand.h"
#include "Card.h"
#include "handstrength.h"
#include <cassert>

namespace lp {
Hand::Hand( const Hand & other )
    : lCard( std::make_unique< Card >( other.lCard.operator*() ) ),
      rCard( std::make_unique< Card >( other.rCard.operator*() ) ){};
//---------------------------------------------------------------------------------------------------------------------------
Hand::Hand() : lCard( std::make_unique< Card >() ), rCard( std::make_unique< Card >() ) {}
//---------------------------------------------------------------------------------------------------------------------------
Hand::Hand( Hand && other ) : lCard( other.lCard.release() ), rCard( other.rCard.release() ) {
    other.lCard = nullptr;
    other.rCard = nullptr;
}
//---------------------------------------------------------------------------------------------------------------------------
Hand::Hand( const Card::valCard lCardV, const Card::suitCard lCardS, const Card::valCard rCardV,
            const Card::suitCard rCardS )
    : lCard( std::make_unique< Card >( std::move( lCardV ), std::move( lCardS ) ) ),
      rCard( std::make_unique< Card >( std::move( rCardV ), std::move( rCardS ) ) ) {
    assert( ( ( lCardV != rCardV ) && ( lCardS != rCardS ) ) && "identical cards" );
}
//---------------------------------------------------------------------------------------------------------------------------
Hand::Hand( const std::string str1, const std::string str2 )
    : lCard( std::make_unique< Card >( str1 ) ), rCard( std::make_unique< Card >( str2 ) ) {
    assert( str1 != str2 && "identical cards" );
}
//---------------------------------------------------------------------------------------------------------------------------
Hand::~Hand() {}
//---------------------------------------------------------------------------------------------------------------------------
void Hand::setHand( const std::string lCard_, const std::string rCard_ ) {
    lCard->setCard( lCard_ );
    rCard->setCard( rCard_ );
}
//---------------------------------------------------------------------------------------------------------------------------
void Hand::setHand( Card::valCard lCardV, Card::suitCard lCardS, Card::valCard rCardV, Card::suitCard rCardS ) {
    lCard->setCard( lCardV, lCardS );
    rCard->setCard( rCardV, rCardS );
}
//---------------------------------------------------------------------------------------------------------------------------
void Hand::setHand( const Card & lCard_, const Card & rCard_ ) {
    lCard->setCard( lCard_ );
    rCard->setCard( rCard_ );
}
//---------------------------------------------------------------------------------------------------------------------------
// Получение значения руки в переменные типа char
void Hand::getHand( std::string & lCardStr, std::string & rCardStr ) const {
    lCardStr = lCard->getString();
    rCardStr = rCard->getString();
}
//---------------------------------------------------------------------------------------------------------------------------
void Hand::getCards( Card & lCard_, Card & rCard_ ) const {
    lCard_.setCard( *lCard );
    rCard_.setCard( *rCard );
}
//---------------------------------------------------------------------------------------------------------------------------
const Card & Hand::getLCard() const { return *lCard; }
//---------------------------------------------------------------------------------------------------------------------------
const Card & Hand::getRCard() const { return *rCard; }
//---------------------------------------------------------------------------------------------------------------------------
bool Hand::operator==( const Hand & other ) const {
    return ( ( ( this->lCard.operator*() == other.lCard.operator*() ) &&
               ( this->rCard.operator*() == other.rCard.operator*() ) ) ||
             ( ( this->lCard.operator*() == other.rCard.operator*() ) &&
               ( this->rCard.operator*() == other.lCard.operator*() ) ) );
}
//---------------------------------------------------------------------------------------------------------------------------
bool Hand::operator!=( const Hand & other ) const {
    return !( ( ( this->lCard.operator*() == other.lCard.operator*() ) &&
                ( this->rCard.operator*() == other.rCard.operator*() ) ) ||
              ( ( this->lCard.operator*() == other.rCard.operator*() ) &&
                ( this->rCard.operator*() == other.lCard.operator*() ) ) );
}
//---------------------------------------------------------------------------------------------------------------------------
Hand & Hand::operator=( const Hand & other ) {
    this->lCard->setCard( *( other.lCard ) );
    this->rCard->setCard( *( other.rCard ) );
    return *this;
}
//---------------------------------------------------------------------------------------------------------------------------
Hand & Hand::operator=( Hand && other ) {
    this->lCard.swap( other.lCard );
    this->rCard.swap( other.rCard );
    other.lCard = nullptr;
    other.rCard = nullptr;
    return *this;
}

} // namespace lp