#include "Hand.h"
#include "cassert"

namespace lp {

Hand::Hand( const Hand & other ) : card1( std::make_unique< Card >() ), card2( std::make_unique< Card >() )  {
	card1->setCard( other.card1.operator*() );
	card2->setCard( other.card2.operator*() );
};
//---------------------------------------------------------------------------------------------------------------------------
Hand::Hand() : card1( std::make_unique< Card >() ), card2( std::make_unique< Card >() ) {}
//---------------------------------------------------------------------------------------------------------------------------
Hand::Hand( Hand && other ) : card1( other.card1.release() ), card2( other.card2.release() ) { 
	other.card1 = nullptr;
	other.card2 = nullptr;
}
//---------------------------------------------------------------------------------------------------------------------------
Hand::Hand( Card::valCard numValue1, Card::suitCard numSuit1,
            Card::valCard numValue2, Card::suitCard numSuit2 ) {
    assert( ( ( numValue1 != numValue2 ) || ( numSuit1 != numSuit2 ) ) && "identical cards" );
    card1->setCard( numValue1, numSuit1 );
    card2->setCard( numValue2, numSuit2 );
}
//---------------------------------------------------------------------------------------------------------------------------
Hand::Hand( const std::string str1, const std::string str2 ) :	card1( std::make_unique< Card >( str1 ) ), 
																card2( std::make_unique< Card >( str2 ) )  { 
	assert( str1 != str2 && "identical cards" ); 
}
//---------------------------------------------------------------------------------------------------------------------------
Hand::~Hand(){}
//---------------------------------------------------------------------------------------------------------------------------
// Указание руки
void Hand::setHand ( const std::string card1_, const std::string card2_ ) {
    card1->setCard( card1_ );
    card2->setCard( card2_ );
}
//---------------------------------------------------------------------------------------------------------------------------
void Hand::setHand ( Card::valCard numValueCard1, Card::suitCard numSuitCard1,
                     Card::valCard numValueCard2, Card::suitCard numSuitCard2 ) {
    card1->setCard( numValueCard1, numSuitCard1 );
    card2->setCard( numValueCard2, numSuitCard2 );
}
//---------------------------------------------------------------------------------------------------------------------------
void Hand::setHand ( const Card & card1_, const Card & card2_ ) {
    card1->setCard( card1_ );
    card2->setCard( card2_ );
}
//---------------------------------------------------------------------------------------------------------------------------
// Получение значения руки в переменные типа char
void Hand::getHand( std::string & card1_str, std::string & card2_str ) const {
    card1_str = card1->get_string();
    card2_str = card2->get_string();
}
//---------------------------------------------------------------------------------------------------------------------------
void Hand::getCards( Card & card1_, Card & card2_ ) const {
    card1_.setCard( *card1 );
    card2_.setCard( *card2 );
}
//---------------------------------------------------------------------------------------------------------------------------
const Card & Hand::getCard1 () const { return *card1; }
//---------------------------------------------------------------------------------------------------------------------------
const Card & Hand::getCard2 () const { return *card2; }
//---------------------------------------------------------------------------------------------------------------------------
bool Hand::operator== ( const Hand & other ) const
{
    return ( ( ( this->card1.operator*() == other.card1.operator*() ) && ( this->card2.operator*() == other.card2.operator*() ) ) ||
			 ( ( this->card1.operator*() == other.card2.operator*() ) && ( this->card2.operator*() == other.card1.operator*() ) ) );
}
//---------------------------------------------------------------------------------------------------------------------------
bool Hand::operator!= ( const Hand &other ) const
{
    return !( ( ( this->card1.operator*() == other.card1.operator*() ) && ( this->card2.operator*() == other.card2.operator*() ) ) ||
			  ( ( this->card1.operator*() == other.card2.operator*() ) && ( this->card2.operator*() == other.card1.operator*() ) ) );
}
//---------------------------------------------------------------------------------------------------------------------------
Hand & Hand::operator= ( const Hand & other ) {
	this->card1->setCard(*(other.card1));
	this->card2->setCard(*(other.card2));
	return *this;
}
//---------------------------------------------------------------------------------------------------------------------------
Hand & Hand::operator= ( Hand && other ) {
	this->card1.swap( other.card1 );
	this->card2.swap( other.card2 );
	other.card1 = nullptr;
	other.card2 = nullptr;
	return *this;
}

}