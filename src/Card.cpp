#include "Card.h"
// #define NDEBUG
#include <cassert>

namespace lp {

//---------------------------------------------------------------------------------------------------------------------------
Card::Card()
    : numCard( static_cast< uint32_t >( Card::valCard::NODEF ) | static_cast< uint8_t >( Card::suitCard::NODEF ) ) {}
//---------------------------------------------------------------------------------------------------------------------------
Card::Card( const std::string & strCard ) : numCard( 0 ) {
    assert( strCard.length() == 2 && "invalid string length" );
    setCard( strCard );
}
//---------------------------------------------------------------------------------------------------------------------------
Card::Card( valCard && value, suitCard && suit ) : numCard( 0 ) {
    assert( static_cast< bool >( static_cast< uint32_t >( value ) < valueSize ) );
    assert( static_cast< bool >( static_cast< uint8_t >( suit ) < suitSize ) );

    numCard = static_cast< uint32_t >( value ) | static_cast< uint8_t >( suit );
}
//---------------------------------------------------------------------------------------------------------------------------
// Card::Card( const Card & other ) : numCard( other.numCard ) {}
//---------------------------------------------------------------------------------------------------------------------------
// Card::Card( Card && other ) : numCard( other.numCard ) { other.numCard = 0; }
//---------------------------------------------------------------------------------------------------------------------------
// Card::~Card() {}
//---------------------------------------------------------------------------------------------------------------------------
void Card::setCard( const std::string & strCard ) {
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
    if ( numCard & suitMask )
        numCard &= valueMask;
    if ( checkValidSuit( suit ) )
        numCard |= static_cast< uint8_t >( suit );
}
//---------------------------------------------------------------------------------------------------------------------------
void Card::setValueNum( const Card::valCard & value ) {
    if ( numCard & valueMask )
        numCard &= suitMask;
    if ( checkValidValue( value ) )
        numCard |= static_cast< uint32_t >( value );
}
//---------------------------------------------------------------------------------------------------------------------------
std::string Card::getSuit() const noexcept {
    switch ( numCard & suitMask ) {
    case static_cast< uint8_t >( Card::suitCard::_c_0x4 ):
        return std::string{"c"};
        //        break;
    case static_cast< uint8_t >( Card::suitCard::_h_0x8 ):
        return std::string{"h"};
        //        break;
    case static_cast< uint8_t >( Card::suitCard::_d_0x1 ):
        return std::string{"d"};
        //        break;
    case static_cast< uint8_t >( Card::suitCard::_s_0x2 ):
        return std::string{"s"};
        //        break;
    default:
        assert( false && "an attempt to display the card suit, but the card suit is not defined" );
    }
    //    return std::move( res );
}
//---------------------------------------------------------------------------------------------------------------------------
std::string Card::getValue() const noexcept {
    switch ( numCard & valueMask ) {
    case static_cast< uint32_t >( Card::valCard::_2 ):
        return std::string{"2"};
        //        break;
    case static_cast< uint32_t >( Card::valCard::_3 ):
        return std::string{"3"};
        //        break;
    case static_cast< uint32_t >( Card::valCard::_4 ):
        return std::string{"4"};
        //        break;
    case static_cast< uint32_t >( Card::valCard::_5 ):
        return std::string{"5"};
        //        break;
    case static_cast< uint32_t >( Card::valCard::_6 ):
        return std::string{"6"};
        //        break;
    case static_cast< uint32_t >( Card::valCard::_7 ):
        return std::string{"7"};
        //        break;
    case static_cast< uint32_t >( Card::valCard::_8 ):
        return std::string{"8"};
        //        break;
    case static_cast< uint32_t >( Card::valCard::_9 ):
        return std::string{"9"};
        //        break;
    case static_cast< uint32_t >( Card::valCard::_T ):
        return std::string{"T"};
        //        break;
    case static_cast< uint32_t >( Card::valCard::_J ):
        return std::string{"J"};
        //        break;
    case static_cast< uint32_t >( Card::valCard::_Q ):
        return std::string{"Q"};
        //        break;
    case static_cast< uint32_t >( Card::valCard::_K ):
        return std::string{"K"};
        //        break;
    case static_cast< uint32_t >( Card::valCard::_A ):
        return std::string{"A"};
        //        break;
    default:
        assert( false && "an attempt to display the card value, but the card value is not defined" );
    }
    //    return res;
}
//---------------------------------------------------------------------------------------------------------------------------
std::string Card::getString() const noexcept { return getValue() + getSuit(); }
//---------------------------------------------------------------------------------------------------------------------------
uint8_t Card::getSuitNum() const noexcept { return ( numCard & suitMask ); }
//---------------------------------------------------------------------------------------------------------------------------
uint32_t Card::getValueNum() const noexcept { return ( numCard & valueMask ); }
//---------------------------------------------------------------------------------------------------------------------------
uint8_t Card::howHigerCards() const noexcept {
    switch ( numCard & valueMask ) {
    case static_cast< uint32_t >( valCard::_K ):
        return 1;
    case static_cast< uint32_t >( valCard::_Q ):
        return 2;
    case static_cast< uint32_t >( valCard::_J ):
        return 3;
    case static_cast< uint32_t >( valCard::_T ):
        return 4;
    case static_cast< uint32_t >( valCard::_9 ):
        return 5;
    case static_cast< uint32_t >( valCard::_8 ):
        return 6;
    case static_cast< uint32_t >( valCard::_7 ):
        return 7;
    case static_cast< uint32_t >( valCard::_6 ):
        return 8;
    case static_cast< uint32_t >( valCard::_5 ):
        return 9;
    case static_cast< uint32_t >( valCard::_4 ):
        return 10;
    case static_cast< uint32_t >( valCard::_3 ):
        return 11;
    case static_cast< uint32_t >( valCard::_2 ):
        return 12;

    default:
        return 0;
    }
}

Card Card::incVal() noexcept {
    //    assert(((numCard & valueMask) < (valueSize - 1)) && "out of range");
    numCard ^= ( numCard & valueMask ) | ( ( numCard & valueMask ) << 1 );
    return *this;
};
//---------------------------------------------------------------------------------------------------------------------------
Card Card::incSuit() noexcept {
    //    assert(((numCard & suitMask) < (suitSize -1)) && "out of range");
    numCard ^= ( numCard & suitMask ) | ( ( numCard & suitMask ) << 1 );
    return *this;
};
//---------------------------------------------------------------------------------------------------------------------------
Card Card::decVal() noexcept {
    //    assert(((numCard & valueMask) > static_cast<uint32_t>(Card::valCard::_2)) && "out of range");
    numCard ^= ( numCard & valueMask ) | ( ( numCard & valueMask ) >> 1 );
    return *this;
};
//---------------------------------------------------------------------------------------------------------------------------
Card Card::decSuit() noexcept {
    //    assert(((numCard & suitMask) > 0) && "out of range");
    numCard ^= ( numCard & suitMask ) | ( ( numCard & suitMask ) >> 1 );
    return *this;
};
//---------------------------------------------------------------------------------------------------------------------------
bool Card::operator==( const Card & other ) const noexcept { return ( this->numCard == other.numCard ); }
//---------------------------------------------------------------------------------------------------------------------------
bool Card::operator!=( const Card & other ) const noexcept { return !( this->numCard == other.numCard ); }
//---------------------------------------------------------------------------------------------------------------------------
Card & Card::operator=( const Card & other ) {
    this->numCard = other.numCard;
    return *this;
}
//---------------------------------------------------------------------------------------------------------------------------
Card & Card::operator=( Card && other ) noexcept {
    this->numCard = other.numCard;
    other.numCard = 0;
    return *this;
}
//---------------------------------------------------------------------------------------------------------------------------
bool Card::operator<( const Card & other ) const noexcept { return ( this->getValueNum() < other.getValueNum() ); }
//---------------------------------------------------------------------------------------------------------------------------
bool Card::operator>( const Card & other ) const noexcept { return ( this->getValueNum() > other.getValueNum() ); }
//---------------------------------------------------------------------------------------------------------------------------
bool Card::checkValidValue( const Card::valCard & value ) {
    uint32_t check;
    for ( check = static_cast< uint32_t >( Card::valCard::_2 );
          ( check < valueSize ) && ( static_cast< uint32_t >( value ) != check ); check <<= 1 )
        ;
    //    assert( static_cast< uint32_t >( value ) == check );
    return static_cast< uint32_t >( value ) == check;
}
//---------------------------------------------------------------------------------------------------------------------------
bool Card::checkValidSuit( const Card::suitCard & suit ) {
    uint8_t check;
    for ( check = static_cast< uint8_t >( Card::suitCard::_d_0x1 );
          ( check < suitSize ) && ( static_cast< uint8_t >( suit ) != check ); check <<= 1 )
        ;
    //    assert( static_cast< uint8_t >( suit ) == check );
    return static_cast< uint8_t >( suit ) == check;
}

} // namespace lp