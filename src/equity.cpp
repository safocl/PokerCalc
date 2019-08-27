#include "equity.h"
#include "Board.h"
#include "Hand.h"
#include "handstrength.h"
#include <iostream>
//#include <thread>
#include <cassert>

namespace lp {

Eval::Eval()
    : heroEquity( 0 ), oppEquity( 0 ), tieEquity( 0 ),
      hero( Hand{Card::valCard::NODEF, Card::suitCard::NODEF, Card::valCard::NODEF, Card::suitCard::NODEF} ),
      opp( Hand{Card::valCard::NODEF, Card::suitCard::NODEF, Card::valCard::NODEF, Card::suitCard::NODEF} ),
      heroHsl( HandStrengthList{} ), oppHsl( HandStrengthList{} ), wHero( 0 ), wOpp( 0 ), wHeroTmp( 0 ), wOppTmp( 0 ) {
    assert( opp != hero );
}
//---------------------------------------------------------------------------------------------------------------------------
void Eval::setheroH( const Card::valCard lCardV, const Card::suitCard lCardS, const Card::valCard rCardV,
                     const Card::suitCard rCardS ) {
    hero.setHand( lCardV, lCardS, rCardV, rCardS );
}
//---------------------------------------------------------------------------------------------------------------------------
void Eval::setoppH( const Card::valCard lCardV, const Card::suitCard lCardS, const Card::valCard rCardV,
                    const Card::suitCard rCardS ) {
    opp.setHand( lCardV, lCardS, rCardV, rCardS );
}
//---------------------------------------------------------------------------------------------------------------------------
void Eval::setheroH( const std::string lCardStr, const std::string rCardStr ) { hero.setHand( lCardStr, rCardStr ); }
//---------------------------------------------------------------------------------------------------------------------------
void Eval::setoppH( const std::string lCardStr, const std::string rCardStr ) { opp.setHand( lCardStr, rCardStr ); }
//---------------------------------------------------------------------------------------------------------------------------
void Eval::setheroH( const Hand & hero ) { this->hero = hero; }
//---------------------------------------------------------------------------------------------------------------------------
void Eval::setoppH( const Hand & opp ) { this->opp = opp; }
//---------------------------------------------------------------------------------------------------------------------------
const Hand & Eval::getHeroH() const { return hero; }
//---------------------------------------------------------------------------------------------------------------------------
const Hand & Eval::getOppH() const { return opp; }
//---------------------------------------------------------------------------------------------------------------------------
bool Eval::isEqHands() const { return ( hero == opp ); }
//---------------------------------------------------------------------------------------------------------------------------
void Eval::calc() {
    unsigned long long sumHO = heroHsl.getSum();
    wHero = wHeroTmp;
    wOpp = wOppTmp;
    heroEquity = static_cast< float >( wHero ) / static_cast< float >( sumHO );
    oppEquity = static_cast< float >( wOpp ) / static_cast< float >( sumHO );
    tieEquity = static_cast< float >( heroHsl.getSum() - ( wHero + wOpp ) ) / static_cast< float >( heroHsl.getSum() );
    wHeroTmp = 0;
    wOppTmp = 0;
}
//---------------------------------------------------------------------------------------------------------------------------
void Eval::accumulate( const Board & board ) {
    heroHsl.accumulate( hero, board );
    oppHsl.accumulate( opp, board );
    if ( !isEqHands() ) {
        if ( HandStrength{hero, board}.getCurrStrength() > HandStrength{opp, board}.getCurrStrength() )
            ++wHeroTmp;
        else if ( HandStrength{hero, board}.getCurrStrength() < HandStrength{opp, board}.getCurrStrength() )
            ++wOppTmp;
        else {
            /*			implimentation when handstrength hero eq handstrength opp */
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void Eval::print() const {
    std::cout << "Hero eq = " << heroEquity << std::endl;
    std::cout << "Opp eq = " << oppEquity << std::endl;
    std::cout << "Equal eq = " << tieEquity << std::endl;
}
//---------------------------------------------------------------------------------------------------------------------------
Combo::Combo( const Hand & hand, const Board & board ) : combo( std::vector< Card >{} ) {
    combo.reserve( 7 );
    for ( auto const & card : board.getBoard() ) {
        combo.push_back( card );
    }
    combo.push_back( hand.getLCard() );
    combo.push_back( hand.getRCard() );
}
//---------------------------------------------------------------------------------------------------------------------------
bool Combo::operator<( const Combo & other ) {
    bool res;
    HandStrength thisHs{hand, board}, otherHs{other.hand, other.board};
    switch ( thisHs.getCurrStrength() ) {
    case HandStrength::strength::HIGHT:
        switch ( otherHs.getCurrStrength() ) {
        case HandStrength::strength::HIGHT:
            res = false;
            break;
        case HandStrength::strength::NODEF:
            assert( false && "is no define strength" );
        default:
            res = true;
        }
        break;
    case HandStrength::strength::PAIR:
        switch ( otherHs.getCurrStrength() ) {
        case HandStrength::strength::HIGHT:
            res = false;
            break;
        case HandStrength::strength::PAIR:
            res = false;
            break;
        case HandStrength::strength::NODEF:
            assert( false && "is no define strength" );
        default:
            res = true;
        }
        break;
    case HandStrength::strength::SET:
        switch ( otherHs.getCurrStrength() ) {
        case HandStrength::strength::HIGHT:
            res = false;
            break;
        case HandStrength::strength::PAIR:
            res = false;
            break;
        case HandStrength::strength::SET:
            res = false;
            break;
        case HandStrength::strength::TWO_PAIRS:
            res = false;
            break;
        case HandStrength::strength::NODEF:
            assert( false && "is no define strength" );
        default:
            res = true;
        }
        break;
    case HandStrength::strength::TWO_PAIRS:
        switch ( otherHs.getCurrStrength() ) {
        case HandStrength::strength::HIGHT:
            res = false;
            break;
        case HandStrength::strength::PAIR:
            res = false;
            break;
        case HandStrength::strength::TWO_PAIRS:
            res = false;
            break;
        case HandStrength::strength::NODEF:
            assert( false && "is no define strength" );
        default:
            res = true;
        }
        break;
    case HandStrength::strength::STRAIT:
        switch ( otherHs.getCurrStrength() ) {
        case HandStrength::strength::FLUSH:
            res = true;
            break;
        case HandStrength::strength::FULL_HOUSE:
            res = true;
            break;
        case HandStrength::strength::STRAIT_FLUSH:
            res = true;
            break;
        case HandStrength::strength::KARE:
            res = true;
            break;
        case HandStrength::strength::NODEF:
            assert( false && "is no define strength" );
        default:
            res = false;
        }
        break;
    case HandStrength::strength::FLUSH:
        switch ( otherHs.getCurrStrength() ) {
        case HandStrength::strength::FULL_HOUSE:
            res = true;
            break;
        case HandStrength::strength::STRAIT_FLUSH:
            res = true;
            break;
        case HandStrength::strength::KARE:
            res = true;
            break;
        case HandStrength::strength::NODEF:
            assert( false && "is no define strength" );
        default:
            res = false;
        }
        break;
    case HandStrength::strength::FULL_HOUSE:
        switch ( otherHs.getCurrStrength() ) {
        case HandStrength::strength::STRAIT_FLUSH:
            res = true;
            break;
        case HandStrength::strength::KARE:
            res = true;
            break;
        case HandStrength::strength::NODEF:
            assert( false && "is no define strength" );
        default:
            res = false;
        }
        break;
    case HandStrength::strength::STRAIT_FLUSH:
        res = false;
        break;
    case HandStrength::strength::KARE:
        switch ( otherHs.getCurrStrength() ) {
        case HandStrength::strength::STRAIT_FLUSH:
            res = true;
            break;
        case HandStrength::strength::NODEF:
            assert( false && "is no define strength" );
        default:
            res = false;
        }
        break;
    case HandStrength::strength::NODEF:
        assert( false && "is no define strength" );
    }

    return res;
}
//---------------------------------------------------------------------------------------------------------------------------
bool Combo::operator>( const Combo & other ) { return !operator<( other ); }
//---------------------------------------------------------------------------------------------------------------------------
bool Combo::operator==( const Combo & other ) {
    return ( HandStrength( hand, board ).getCurrStrength() ==
             HandStrength( other.hand, other.board ).getCurrStrength() );
}
//---------------------------------------------------------------------------------------------------------------------------

} // namespace lp