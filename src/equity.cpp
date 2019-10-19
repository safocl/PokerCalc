#include "equity.h"
#include "Board.h"
#include "Hand.h"
#include "handstrength.h"
#include <iostream>
//#include <thread>
#include <cassert>

namespace lp {

Eval::Eval( const Hand & hero, const Hand & opp )
    : heroEquity( 0 ), oppEquity( 0 ), tieEquity( 0 ), hero( hero ), opp( opp ) {}

Eval::Eval( Hand && hero, Hand && opp )
    : heroEquity( 0 ), oppEquity( 0 ), tieEquity( 0 ), hero( std::move( hero ) ), opp( std::move( opp ) ) /*,
       heroHsl( HandStrengthList{} ), oppHsl( HandStrengthList{} )*/
{
    assert( opp != hero );
}
//---------------------------------------------------------------------------------------------------------------------------
void Eval::setHeroH( const Card::valCard lCardV, const Card::suitCard lCardS, const Card::valCard rCardV,
                     const Card::suitCard rCardS ) {
    hero.setHand( lCardV, lCardS, rCardV, rCardS );
}
//---------------------------------------------------------------------------------------------------------------------------
void Eval::setOppH( const Card::valCard lCardV, const Card::suitCard lCardS, const Card::valCard rCardV,
                    const Card::suitCard rCardS ) {
    opp.setHand( lCardV, lCardS, rCardV, rCardS );
}
//---------------------------------------------------------------------------------------------------------------------------
void Eval::setHeroH( const std::string lCardStr, const std::string rCardStr ) { hero.setHand( lCardStr, rCardStr ); }
//---------------------------------------------------------------------------------------------------------------------------
void Eval::setOppH( const std::string lCardStr, const std::string rCardStr ) { opp.setHand( lCardStr, rCardStr ); }
//---------------------------------------------------------------------------------------------------------------------------
void Eval::setHeroH( const Hand & hero ) { this->hero = hero; }
//---------------------------------------------------------------------------------------------------------------------------
void Eval::setOppH( const Hand & opp ) { this->opp = opp; }
//---------------------------------------------------------------------------------------------------------------------------
const Hand & Eval::getHeroH() const { return hero; }
//---------------------------------------------------------------------------------------------------------------------------
const Hand & Eval::getOppH() const { return opp; }
//---------------------------------------------------------------------------------------------------------------------------
bool Eval::isEqHands() const { return ( hero == opp ); }
//---------------------------------------------------------------------------------------------------------------------------
void Eval::calc( const Board & board ) {
    auto hsHero = std::make_unique< HandStrength >( hero, board );
    auto hsOpp = std::make_unique< HandStrength >( opp, board );

    switch ( board.getState() ) {
    case Board::boardState::FLOP:
        break;

    case Board::boardState::TURN:

        if ( hsHero->containHight() ) {
        }

        if ( hsHero->containPair() ) {
        }

        if ( hsHero->containTwoPairs() ) {
        }

        if ( hsHero->containSet() ) {
        }

        if ( hsHero->containStrait() ) {
        }

        if ( hsHero->containFlush() ) {
        }

        if ( hsHero->containFullHouse() ) {
        }

        if ( hsHero->containKare() ) {
            heroEquity = 1;
            oppEquity = 0;
            tieEquity = 0;

            if ( hsOpp->containKare() ) {
                if ( board.getBoard().at( 0 ).getValueNum() == board.getBoard().at( 1 ).getValueNum() ==
                     board.getBoard().at( 2 ).getValueNum() == board.getBoard().at( 3 ).getValueNum() ) {
                    if ( hero.getHigerCard().getValueNum() == opp.getHigerCard().getValueNum() ) {
                        heroEquity = 0.5;
                        oppEquity = 0.5;
                        tieEquity = 1;
                    } else if ( hero.getHigerCard().getValueNum() > opp.getHigerCard().getValueNum() ) {
                        uint8_t eqCards = hero.isPair() ? 2 : 3;
                        heroEquity = 1;
                        oppEquity = 0;
                        if ( board.getBoard().at( 0 ).getValueNum() < hero.getHigerCard().getValueNum() )
                            tieEquity = ( hero.getHigerCard().howHigerCards() * 4 + eqCards ) / 44;
                        else
                            tieEquity = ( ( hero.getHigerCard().howHigerCards() - 1 ) * 4 + eqCards ) / 44;
                    }
                }
            }

            if ( ( hsOpp->containSD() && hsOpp->containFD() ) ||
                 ( hsOpp->containFlush() && ( hsOpp->containSD() || hsOpp->containGutShot() ) ) ||
                 ( hsOpp->containStrait() && hsOpp->containFD() ) ) {
                constexpr float _heroEquity = 1 - 1 / 44;
                heroEquity = _heroEquity;
                constexpr float _oppEquity = 1 / 44;
                oppEquity = _oppEquity;
                tieEquity = 0;
            }

            if ( hsOpp->containStraitFlush() ) {
                heroEquity = 0;
                oppEquity = 1;
                tieEquity = 0;
            }
        }

        if ( hsHero->containStraitFlush() ) {

            uint8_t countSuitedCards = 0;
            uint8_t suiteFlushCardN = 0;

            for ( uint8_t i = 0; i < board.getBoard().size(); ++i ) {
                if ( countSuitedCards < 3 ) {
                    countSuitedCards = 0;
                    for ( uint8_t si = i + 1; si < board.getBoard().size(); ++si ) {
                        if ( board.getBoard().at( i ).getSuitNum() == board.getBoard().at( si ).getSuitNum() ) {
                            ++countSuitedCards;
                        }
                    }
                } else
                    suiteFlushCardN = board.getBoard().at( i - 1 ).getSuitNum();
            }

            uint32_t valFlushCardsN = 0;

            for ( auto card : board.getBoard() ) {
                if ( card.getSuitNum() == suiteFlushCardN )
                    valFlushCardsN |= card.getValueNum();
            }

#define STRAIT_BOARD( first, second, last )                                                                            \
    constexpr uint32_t straitBoard_##first##_##last = static_cast< uint32_t >( Card::valCard::_##first ) |             \
                                                      static_cast< uint32_t >( Card::valCard::_##second ) |            \
                                                      static_cast< uint32_t >( Card::valCard::_##last )

            STRAIT_BOARD( 3, 4, 5 );
            STRAIT_BOARD( 4, 5, 6 );
            STRAIT_BOARD( 5, 6, 7 );
            STRAIT_BOARD( 6, 7, 8 );
            STRAIT_BOARD( 7, 8, 9 );
            STRAIT_BOARD( 8, 9, T );
            STRAIT_BOARD( 9, T, J );
            STRAIT_BOARD( T, J, Q );

#undef STRAIT_BOARD

#define STRAIT_BOARD( first, second, third, last )                                                                     \
    constexpr uint32_t straitBoard_##first##_##last =                                                                  \
        static_cast< uint32_t >( Card::valCard::_##first ) | static_cast< uint32_t >( Card::valCard::_##second ) |     \
        static_cast< uint32_t >( Card::valCard::_##third ) | static_cast< uint32_t >( Card::valCard::_##last )

            STRAIT_BOARD( 2, 3, 4, 5 );
            STRAIT_BOARD( 3, 4, 5, 6 );
            STRAIT_BOARD( 4, 5, 6, 7 );
            STRAIT_BOARD( 5, 6, 7, 8 );
            STRAIT_BOARD( 6, 7, 8, 9 );
            STRAIT_BOARD( 7, 8, 9, T );
            STRAIT_BOARD( 8, 9, T, J );
            STRAIT_BOARD( 9, T, J, Q );
            STRAIT_BOARD( T, J, Q, K );

#undef STRAIT_BOARD

            bool hsHeroIsBlockHighest = false;

            switch ( valFlushCardsN ) {

#define CASE_STRAIT_BOARD( first, last, match )                                                                        \
    case straitBoard_##first##_##last:                                                                                 \
        if ( hero.getLCard().getValueNum() == static_cast< uint32_t >( Card::valCard::_##match ) ||                    \
             hero.getRCard().getValueNum() == static_cast< uint32_t >( Card::valCard::_##match ) )                     \
            hsHeroIsBlockHighest = true;                                                                               \
        break;

                CASE_STRAIT_BOARD( 3, 5, 6 )
                CASE_STRAIT_BOARD( 4, 6, 7 )
                CASE_STRAIT_BOARD( 5, 7, 8 )
                CASE_STRAIT_BOARD( 6, 8, 9 )
                CASE_STRAIT_BOARD( 7, 9, T )
                CASE_STRAIT_BOARD( 8, T, J )
                CASE_STRAIT_BOARD( 9, J, Q )
                CASE_STRAIT_BOARD( T, Q, K )
                CASE_STRAIT_BOARD( 2, 5, 6 )
                CASE_STRAIT_BOARD( 3, 6, 7 )
                CASE_STRAIT_BOARD( 4, 7, 8 )
                CASE_STRAIT_BOARD( 5, 8, 9 )
                CASE_STRAIT_BOARD( 6, 9, T )
                CASE_STRAIT_BOARD( 7, T, J )
                CASE_STRAIT_BOARD( 8, J, Q )
                CASE_STRAIT_BOARD( 9, Q, K )
                CASE_STRAIT_BOARD( T, K, A )

#undef CASE_STRAIT_BOARD

            default:
                break;
            }

            heroEquity = 1;
            oppEquity = 0;
            tieEquity = 0;

            if ( !hsHeroIsBlockHighest ) {
                if ( ( hsOpp->containSD() && hsOpp->containFD() ) ||
                     ( hsOpp->containFlush() && ( hsOpp->containSD() || hsOpp->containGutShot() ) ) ||
                     ( hsOpp->containStrait() && hsOpp->containFD() ) ) {
                    constexpr float _heroEquity = 1 - 1 / 44;
                    heroEquity = _heroEquity;
                    constexpr float _oppEquity = 1 / 44;
                    oppEquity = _oppEquity;
                    tieEquity = 0;
                }

                if ( hsOpp->containStraitFlush() ) {
                    heroEquity = 0;
                    oppEquity = 1;
                    tieEquity = 0;
                }
            }
        }
        break;
    case Board::boardState::RIVER:
        break;
    default:
        break;
    }
} // namespace lp
//---------------------------------------------------------------------------------------------------------------------------
void Eval::print() const {
    std::cout << "Hero eq = " << heroEquity << std::endl;
    std::cout << "Opp eq = " << oppEquity << std::endl;
    std::cout << "Equal eq = " << tieEquity << std::endl;
}

} // namespace lp