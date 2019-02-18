#include "Card.h"
// #define NDEBUG
#include <cassert>

namespace lp {


//---------------------------------------------------------------------------------------------------------------------------
Card::Card () : numCard( 0 ) {}
//---------------------------------------------------------------------------------------------------------------------------
Card::Card( const std::string strCard ) : numCard( 0 ) {
    assert( strCard.length() == 2 && "invalid string length" );
    setCard( strCard );
}
//---------------------------------------------------------------------------------------------------------------------------
Card::Card( const Card::valCard && value, const Card::suitCard && suit ) : numCard( 0 ) {
    assert( static_cast< bool >( static_cast< uint32_t >( value ) < sizeValueCardArr ) );
    assert( static_cast< bool >( static_cast< uint8_t >( suit ) < sizeSuitCardArr ) );

    numCard = static_cast< uint32_t >( value ) | static_cast< uint8_t >( suit );
}
//---------------------------------------------------------------------------------------------------------------------------
Card::Card( const Card &other ) : numCard( other.numCard ) {}
//---------------------------------------------------------------------------------------------------------------------------
Card::Card( Card && other ) : numCard( other.numCard ) { other.numCard = 0; }
//---------------------------------------------------------------------------------------------------------------------------
Card::~Card(){}
//---------------------------------------------------------------------------------------------------------------------------
void Card::setCard( const std::string strCard ) {
    assert( strCard.length() == 2 && "invalid string length" );
    
    if ( numCard )
        numCard = 0;
    
    switch ( strCard.at( 0 ) ) {
    case '2':
        numCard |= static_cast< uint32_t >( Card::valCard::_2 );
        break;
    case '3':
        numCard |= static_cast< uint32_t >( Card::valCard::_3 );
        break;
    case '4':
        numCard |= static_cast< uint32_t >( Card::valCard::_4 );
        break;
    case '5':
        numCard |= static_cast< uint32_t >( Card::valCard::_5 );
        break;
    case '6':
        numCard |= static_cast< uint32_t >( Card::valCard::_6 );
        break;
    case '7':
        numCard |= static_cast< uint32_t >( Card::valCard::_7 );
        break;
    case '8':
        numCard |= static_cast< uint32_t >( Card::valCard::_8 );
        break;
    case '9':
        numCard |= static_cast< uint32_t >( Card::valCard::_9 );
        break;
    case 't':
    case 'T':
        numCard |= static_cast< uint32_t >( Card::valCard::_T );
        break;
    case 'j':
    case 'J':
        numCard |= static_cast< uint32_t >( Card::valCard::_J );
        break;
    case 'q':
    case 'Q':
        numCard |= static_cast< uint32_t >( Card::valCard::_Q );
        break;
    case 'k':
    case 'K':
        numCard |= static_cast< uint32_t >( Card::valCard::_K );
        break;
    case 'a':
    case 'A':
        numCard |= static_cast< uint32_t >( Card::valCard::_A );
        break;
    default:
        assert( false && "invalid card suit" );
    }
    
    switch ( strCard.at( 1 ) ) {
    case 'd':
    case 'D':
        numCard |= static_cast< uint32_t >( Card::suitCard::_d_0x1 );
        break;
    case 's':
    case 'S':
        numCard |= static_cast< uint32_t >( Card::suitCard::_s_0x2 );
        break;
    case 'c':
    case 'C':
        numCard |= static_cast< uint32_t >( Card::suitCard::_c_0x4 );
        break;
    case 'h':
    case 'H':
        numCard |= static_cast< uint32_t >( Card::suitCard::_h_0x8 );
        break;
    default:
        assert( false && "invalid card suit" );
    }
}

void Card::setCard( const Card & card ) {
//    numCard = 0;
    numCard = card.numCard;
}
//---------------------------------------------------------------------------------------------------------------------------
void Card::setCard( const Card::valCard & value, const Card::suitCard & suit ) {
    setValueNum( value );
    setSuitNum( suit );
}
//---------------------------------------------------------------------------------------------------------------------------
void Card::setSuitNum( const Card::suitCard & suit ) {
    if ( numCard & suit_mask )
        numCard &= value_mask;
    if ( check_valid_suit( suit ) )
        numCard |= static_cast< uint8_t >( suit );
}
//---------------------------------------------------------------------------------------------------------------------------
void Card::setValueNum( const Card::valCard & value ) {
    if ( numCard & value_mask )
        numCard &= suit_mask;
    if ( check_valid_value( value ) )
        numCard |= static_cast< uint32_t >( value );
}
//---------------------------------------------------------------------------------------------------------------------------
std::string && Card::getSuit() const noexcept{
    std::string res;
    switch ( numCard | suit_mask ) {
    case static_cast< uint8_t >( Card::suitCard::_c_0x4 ) :
        res = "c";
        break;
    case static_cast< uint8_t >( Card::suitCard::_h_0x8 ) :
        res = "h";
        break;
    case static_cast< uint8_t >( Card::suitCard::_d_0x1 ) :
        res = "d";
        break;
    case static_cast< uint8_t >( Card::suitCard::_s_0x2 ) :
        res = "s";
        break;
    default:
        assert( false && "an attempt to display the card suit, but the card suit is not defined" );
    }
    return std::move( res );
}
//---------------------------------------------------------------------------------------------------------------------------
std::string Card::getValue() const noexcept{
    std::string res;
    switch ( numCard & value_mask ) {
    case static_cast< uint32_t >( Card::valCard::_2 ) :
        res = "2";
        break;
    case static_cast< uint32_t >( Card::valCard::_3 ) :
        res = "3";
        break;
    case static_cast< uint32_t >( Card::valCard::_4 ) :
        res = "4";
        break;
    case static_cast< uint32_t >( Card::valCard::_5 ) :
        res = "5";
        break;
    case static_cast< uint32_t >( Card::valCard::_6 ) :
        res = "6";
        break;
    case static_cast< uint32_t>( Card::valCard::_7 ) :
        res = "7";
        break;
    case static_cast< uint32_t >( Card::valCard::_8 ) :
        res = "8";
        break;
    case static_cast< uint32_t >( Card::valCard::_9 ) :
        res = "9";
        break;
    case static_cast< uint32_t >( Card::valCard::_T ) :
        res = "T";
        break;
    case static_cast< uint32_t >( Card::valCard::_J ) :
        res = "J";
        break;
    case static_cast< uint32_t >( Card::valCard::_Q ) :
        res = "Q";
        break;
    case static_cast< uint32_t >( Card::valCard::_K ) :
        res = "K";
        break;
    case static_cast< uint32_t >( Card::valCard::_A ) :
        res = "A";
        break;
    default:
        assert( false && "an attempt to display the card value, but the card value is not defined" );
    }
    return res;
}
//---------------------------------------------------------------------------------------------------------------------------
std::string Card::get_string() const noexcept { return getValue() + getSuit(); }
//---------------------------------------------------------------------------------------------------------------------------
uint8_t Card::getSuitNum() const noexcept { return (numCard & suit_mask); }
//---------------------------------------------------------------------------------------------------------------------------
uint32_t Card::getValueNum() const noexcept { return (numCard & value_mask); }
//---------------------------------------------------------------------------------------------------------------------------
Card Card::inc_val() noexcept {
//    assert(((numCard & value_mask) < (sizeValueCardArr - 1)) && "out of range");
    numCard ^= ( numCard & value_mask) | ( ( numCard & value_mask ) << 1 );
    return *this;
};
//---------------------------------------------------------------------------------------------------------------------------
Card Card::inc_suit() noexcept {
//    assert(((numCard & suit_mask) < (sizeSuitCardArr -1)) && "out of range");
    numCard ^= ( numCard & suit_mask ) | ( ( numCard & suit_mask ) << 1 );
    return *this;
};
//---------------------------------------------------------------------------------------------------------------------------
Card Card::dec_val() noexcept {
//    assert(((numCard & value_mask) > static_cast<uint32_t>(Card::valCard::_2)) && "out of range");
    numCard ^= ( numCard & value_mask ) | ( ( numCard & value_mask ) >> 1 );
    return *this;
};
//---------------------------------------------------------------------------------------------------------------------------
Card Card::dec_suit() noexcept {
//    assert(((numCard & suit_mask) > 0) && "out of range");
    numCard ^= ( numCard & suit_mask ) | ( ( numCard & suit_mask ) >> 1 );
    return *this;
};
//---------------------------------------------------------------------------------------------------------------------------
bool Card::operator== ( const Card & other ) const noexcept {
    return ( this->numCard == other.numCard );
}
//---------------------------------------------------------------------------------------------------------------------------
bool Card::operator!=( const Card & other ) const noexcept {
    return !( this->numCard == other.numCard );
}
//---------------------------------------------------------------------------------------------------------------------------
Card & Card::operator= (const Card & other) noexcept {
    this->numCard = other.numCard;
    return *this;
}
//---------------------------------------------------------------------------------------------------------------------------
Card & Card::operator= ( Card && other ) noexcept {
    this->numCard = other.numCard;
    other.numCard = 0;
    return *this;
}
//---------------------------------------------------------------------------------------------------------------------------
bool Card::operator< ( const Card & other ) const noexcept { return ( this->getValueNum() < other.getValueNum() ); }
//---------------------------------------------------------------------------------------------------------------------------
bool Card::operator> ( const Card & other ) const noexcept { return ( this->getValueNum() > other.getValueNum() ); }
//---------------------------------------------------------------------------------------------------------------------------
bool Card::check_valid_value( const Card::valCard & value ) {
    uint32_t check;
    for ( check = static_cast<uint32_t>( Card::valCard::_2 ); ( check < sizeValueCardArr ) &&
		  ( static_cast< uint32_t >( value ) != check ); check <<= 1 )
        ;
    assert( static_cast< uint32_t >( value ) == check );
    return true;
}
//---------------------------------------------------------------------------------------------------------------------------
bool Card::check_valid_suit( const Card::suitCard & suit ) {
    uint8_t check;
    for ( check = static_cast< uint8_t >( Card::suitCard::_d_0x1 ); ( check < sizeSuitCardArr ) &&
		  ( static_cast< uint8_t >( suit ) != check ); check <<= 1 )
        ;
    assert( static_cast< uint8_t >( suit ) == check );
    return true;
}

}