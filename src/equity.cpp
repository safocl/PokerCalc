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

#include "equity.h"
#include "Board.h"
#include "Deck.h"
#include "Hand.h"
#include "handstrength.h"
#include <iostream>
//#include <thread>
#include <cassert>
#include <numeric>
#include <memory>



template < lp::Board::boardState S >
static std::unique_ptr< lp::EV > hiVSall
    [[nodiscard]] ( const lp::Hand & hero, const lp::Hand & opp, const lp::Board & board, const lp::Deck & deck);

static std::unique_ptr< lp::EV > straitflushVSall
    [[nodiscard]] ( const lp::Hand & hero, const lp::Hand & opp, const lp::Board & board ) {

    auto boardPtr = std::make_unique< lp::Board >( board );
    boardPtr->calcTraits();

    auto hsHero = std::make_unique< lp::HandStrength >( hero, *boardPtr );
    auto hsOpp = std::make_unique< lp::HandStrength >( opp, *boardPtr );

    //            uint8_t countSuitedCards = 0;
    uint8_t suiteFlushCardN = 0;

    for ( uint8_t i = 0, countSuitedCards = 0; i < boardPtr->getBoard().size(); ++i ) {
        if ( countSuitedCards < 3 ) {
            countSuitedCards = 0;
            for ( uint8_t si = i + 1; si < boardPtr->getBoard().size(); ++si ) {
                if ( boardPtr->getBoard().at( i ).getSuitNum() == boardPtr->getBoard().at( si ).getSuitNum() ) {
                    ++countSuitedCards;
                }
            }
        } else
            suiteFlushCardN = boardPtr->getBoard().at( i - 1 ).getSuitNum();
    }

    uint32_t valFlushCardsN = 0;

    // проверить что быстрее -- accumulate или собственная петля ниже.
    valFlushCardsN = std::accumulate( boardPtr->getBoard().cbegin(), boardPtr->getBoard().cend(), valFlushCardsN,
                                      [suiteFlushCardN]( uint32_t val, const lp::Card & card ) {
                                          if ( card.getSuitNum() == suiteFlushCardN )
                                              val |= card.getValueNum();
                                          return val;
                                      } );

    //            for ( auto card : board.getBoard() ) {
    //                if ( card.getSuitNum() == suiteFlushCardN )
    //                    valFlushCardsN |= card.getValueNum();
    //            }

#define STRAIT_BOARD( first, second, last )                                                                            \
    constexpr uint32_t straitBoard_##first##_##last = static_cast< uint32_t >( lp::Card::valCard::_##first ) |         \
                                                      static_cast< uint32_t >( lp::Card::valCard::_##second ) |        \
                                                      static_cast< uint32_t >( lp::Card::valCard::_##last )

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
    constexpr uint32_t straitBoard_##first##_##last = static_cast< uint32_t >( lp::Card::valCard::_##first ) |         \
                                                      static_cast< uint32_t >( lp::Card::valCard::_##second ) |        \
                                                      static_cast< uint32_t >( lp::Card::valCard::_##third ) |         \
                                                      static_cast< uint32_t >( lp::Card::valCard::_##last )

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
        if ( hero.getLCard().getValueNum() == static_cast< uint32_t >( lp::Card::valCard::_##match ) ||                \
             hero.getRCard().getValueNum() == static_cast< uint32_t >( lp::Card::valCard::_##match ) )                 \
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
    auto ev = std::make_unique< lp::EV >();
    ev->heroEV = 1.0f;
    ev->oppEV = 0.0f;
    ev->tieEV = 0.0f;

    if ( !hsHeroIsBlockHighest ) {
        if ( ( hsOpp->containSD() && hsOpp->containFD() ) ||
             ( hsOpp->containFlush() && ( hsOpp->containSD() || hsOpp->containGutShot() ) ) ||
             ( hsOpp->containStrait() && hsOpp->containFD() ) ) {
            constexpr float _oppEV = 1.0f / lp::Deck::getNumRemainedCards< lp::Board::boardState::TURN >();
            constexpr float _heroEV = 1.0f - _oppEV;
            ev->heroEV = _heroEV;
            ev->oppEV = _oppEV;
            ev->tieEV = 0.0f;
        }

        if ( hsOpp->containStraitFlush() ) {
            ev->heroEV = 0.0f;
            ev->oppEV = 1.0f;
            ev->tieEV = 0.0f;
        }
    }
    return ev;
}

static std::unique_ptr< lp::EV > kareVSall
    [[nodiscard]] ( const lp::Hand & hero, const lp::Hand & opp, const lp::Board & board ) {

    auto boardPtr = std::make_unique< lp::Board >( board );
    boardPtr->calcTraits();

    auto hsHero = std::make_unique< lp::HandStrength >( hero, *boardPtr );
    auto hsOpp = std::make_unique< lp::HandStrength >( opp, *boardPtr );

    auto ev = std::make_unique< lp::EV >();
    ev->heroEV = 1.0f;
    ev->oppEV = 0.0f;
    ev->tieEV = 0.0f;

    if ( hsOpp->containSet() ) {
        if ( opp.isPair() ) {
            if ( hero.isPair() ) {
                if ( hero.getLCard().getValueNum() < opp.getLCard().getValueNum() ) {
                    constexpr float _oppEV = 1.0f / lp::Deck::getNumRemainedCards< lp::Board::boardState::TURN >();
                    constexpr float _heroEV = 1.0f - _oppEV;
                    ev->heroEV = _heroEV;
                    ev->oppEV = _oppEV;
                    ev->tieEV = 0.0f;
                }
            } else if ( hero.getLCard().getValueNum() != opp.getLCard().getValueNum() &&
                        hero.getRCard().getValueNum() != opp.getLCard().getValueNum() ) {
                uint32_t numMatchCards = 0;
                for ( uint8_t count0 = 0; count0 < 2; ++count0 ) {
                    for ( uint8_t count1 = count0 + 1; count1 < boardPtr->getBoard().size(); ++count1 ) {
                        if ( boardPtr->getBoard().at( count0 ).getValueNum() ==
                             boardPtr->getBoard().at( count1 ).getValueNum() ) {
                            numMatchCards = boardPtr->getBoard().at( count0 ).getValueNum();
                            break;
                        }
                    }
                    if ( numMatchCards != 0 )
                        break;
                }
                if ( opp.getLCard().getValueNum() > numMatchCards ) {
                    constexpr float _oppEV = 1.0f / lp::Deck::getNumRemainedCards< lp::Board::boardState::TURN >();
                    constexpr float _heroEV = 1.0f - _oppEV;
                    ev->heroEV = _heroEV;
                    ev->oppEV = _oppEV;
                    ev->tieEV = 0.0f;
                }
            }
        }
    } else if ( hsOpp->containKare() ) {
        if ( boardPtr->isQuad() ) {
            if ( hero.getHigerCard().getValueNum() == opp.getHigerCard().getValueNum() ) {
                ev->heroEV = 0.5f;
                ev->oppEV = 0.5f;
                ev->tieEV = 1.0f;
            } else if ( hero.getHigerCard().getValueNum() > opp.getHigerCard().getValueNum() ) {
                uint8_t eqCards = hero.isPair() ? 2 : 3;
                ev->heroEV = 1.0f;
                ev->oppEV = 0.0f;
                ev->tieEV = boardPtr->getBoard().at( 0 ).getValueNum() < hero.getHigerCard().getValueNum()
                                ? static_cast< float >( hero.getHigerCard().howHigerValues() * 4 + eqCards ) /
                                      lp::Deck::getNumRemainedCards< lp::Board::boardState::TURN >()
                                : static_cast< float >( ( hero.getHigerCard().howHigerValues() - 1 ) * 4 + eqCards ) /
                                      lp::Deck::getNumRemainedCards< lp::Board::boardState::TURN >();
            } else {
                uint8_t eqCards = opp.isPair() ? 2 : 3;
                ev->heroEV = 0.0f;
                ev->oppEV = 1.0f;
                ev->tieEV = boardPtr->getBoard().at( 0 ).getValueNum() < opp.getHigerCard().getValueNum()
                                ? static_cast< float >( opp.getHigerCard().howHigerValues() * 4 + eqCards ) /
                                      lp::Deck::getNumRemainedCards< lp::Board::boardState::TURN >()
                                : static_cast< float >( ( opp.getHigerCard().howHigerValues() - 1 ) * 4 + eqCards ) /
                                      lp::Deck::getNumRemainedCards< lp::Board::boardState::TURN >();
            }
        } else if ( hero.getLCard().getValueNum() < opp.getLCard().getValueNum() ) {
            ev->heroEV = 0.0f;
            ev->oppEV = 1.0f;
            ev->tieEV = 0.0f;
        }
    } else if ( ( hsOpp->containSD() && hsOpp->containFD() ) ||
                ( hsOpp->containFlush() && ( hsOpp->containSD() || hsOpp->containGutShot() ) ) ||
                ( hsOpp->containStrait() && hsOpp->containFD() ) ) {
        constexpr float _heroEV = 1.0f - 1.0f / lp::Deck::getNumRemainedCards< lp::Board::boardState::TURN >();
        ev->heroEV = _heroEV;
        constexpr float _oppEV = 1.0f / lp::Deck::getNumRemainedCards< lp::Board::boardState::TURN >();
        ev->oppEV = _oppEV;
        ev->tieEV = 0.0f;
    } else if ( hsOpp->containStraitFlush() ) {
        ev->heroEV = 0.0f;
        ev->oppEV = 1.0f;
        ev->tieEV = 0.0f;
    }
    return ev;
}

static std::unique_ptr< lp::EV > fullhouseVSall[[maybe_unused]]
    [[nodiscard]] ( const lp::Hand & hero [[maybe_unused]], const lp::Hand & opp [[maybe_unused]], const lp::Board & board [[maybe_unused]] ) {

    auto ev = std::make_unique< lp::EV >();

    return ev;
}

static std::unique_ptr< lp::EV > flushVSall[[maybe_unused]]
    [[nodiscard]] ( const lp::Hand & hero [[maybe_unused]], const lp::Hand & opp [[maybe_unused]], const lp::Board & board [[maybe_unused]] ) {

    auto ev = std::make_unique< lp::EV >();

    return ev;
}

static std::unique_ptr< lp::EV > straitVSall[[maybe_unused]]
    [[nodiscard]] ( const lp::Hand & hero [[maybe_unused]], const lp::Hand & opp [[maybe_unused]], const lp::Board & board [[maybe_unused]] ) {

    auto ev = std::make_unique< lp::EV >();

    return ev;
}

static std::unique_ptr< lp::EV > setVSall[[maybe_unused]]
    [[nodiscard]] ( const lp::Hand & hero [[maybe_unused]], const lp::Hand & opp [[maybe_unused]], const lp::Board & board [[maybe_unused]] ) {

    auto ev = std::make_unique< lp::EV >();

    return ev;
}

static std::unique_ptr< lp::EV > twopairsVSall[[maybe_unused]]
    [[nodiscard]] ( const lp::Hand & hero [[maybe_unused]], const lp::Hand & opp [[maybe_unused]], const lp::Board & board [[maybe_unused]] ) {

    auto ev = std::make_unique< lp::EV >();

    return ev;
}

static std::unique_ptr< lp::EV > pairVSall[[maybe_unused]]
    [[nodiscard]] ( const lp::Hand & hero [[maybe_unused]], const lp::Hand & opp [[maybe_unused]], const lp::Board & board [[maybe_unused]] ) {

    auto ev = std::make_unique< lp::EV >();

    return ev;
}

template <>
std::unique_ptr< lp::EV > hiVSall< lp::Board::boardState::TURN >( const lp::Hand & hero, 
                const lp::Hand & opp, const lp::Board & board, const lp::Deck & deck [[maybe_unused]] ) {
	std::cout << "select hiVSall< lp::Board::boardState::TURN >" << std::endl;
    auto boardPtr = std::make_unique< lp::Board >( board );
    boardPtr->calcTraits();

    auto hsHero = std::make_unique< lp::HandStrength >( hero, *boardPtr );
    auto hsOpp = std::make_unique< lp::HandStrength >( opp, *boardPtr );

    auto ev = std::make_unique< lp::EV >();
    ev->heroEV = 0.0f;
    ev->oppEV = 1.0f;
    ev->tieEV = 0.0f;

    if ( hsOpp->containHight() ) {
        if ( hero.getHigerCard().getValueNum() == opp.getHigerCard().getValueNum() ) {
            ev->heroEV = 0.5f;
            ev->oppEV = 0.5f;
            ev->tieEV = 1.0f;

            if ( hero.getLowerCard().getValueNum() > opp.getLowerCard().getValueNum() ) {
                if ( hsHero->containFD() ) {
                    if ( hsOpp->containFD() ) {
			if (boardPtr->isMonotone()){
			    if (hsHero->containSD()){
				if (hsOpp->containSD()){
                                 
			    	} else if ( hsOpp->containGutShot() ) {
									
				} else {

                                }
			    } else {
				if (hsOpp->containSD()){
							
				} else if (hsOpp->containGutShot()) {
									
				} else {
				    if ( hero.getLowerCard() > boardPtr->getLowerCard() ) {
                                        constexpr int8_t numOppAuts = 2;
                                        const int8_t numTieAuts = 
/*deck.howHighterCards( hero.getLowerCard() ) + */static_cast<int8_t>( 13 - hero.getLowerCard().howHigerValues() );
                                        const int8_t numHeroAuts = 
lp::Deck::getNumRemainedCards< lp::Board::boardState::TURN >() - numOppAuts - 
numTieAuts;
                                        const int8_t numOverallAuts = numOppAuts + numHeroAuts;
                                        ev->oppEV = numOppAuts / numOverallAuts;
                                        ev->heroEV = numHeroAuts / numOverallAuts;
                                        ev->tieEV = numTieAuts / 
lp::Deck::getNumRemainedCards< lp::Board::boardState::TURN >();
                                    }
				}
			    }
			} else if (boardPtr->isTwoTone()){
							
			} else {
							
			}
                    } else {
                    }
                } else {
                }
            }

            /* incomplite impl */
        } else if ( hero.getHigerCard().getValueNum() > opp.getHigerCard().getValueNum() ) {
            if ( hero.getLowerCard().getValueNum() == opp.getLowerCard().getValueNum() ) {
                constexpr float _oppEV = 3.0f / lp::Deck::getNumRemainedCards< lp::Board::boardState::TURN >();
                constexpr float _heroEV [[maybe_unused]] = 1.0f - _oppEV;
            }
        }

    } else if ( hsOpp->containPair() ) {

    } else if ( hsHero->containFD() ) {

    } else if ( hsHero->containSD() ) {

    } else if ( hsHero->containGutShot() ) {

    } else if ( ( hsHero->containSD() || hsHero->containGutShot() ) && hsHero->containFD() ) {
    }

    return ev;
}

namespace lp {

//---------------------------------------------------------------------------------------------------------------------------
// Eval::Eval( const Hand & hero, const Hand & opp )
//    : ev->heroEV( 0 ), ev->oppEV( 0 ), ev->tieEV( 0 ), hero( hero ), opp( opp ) {}
//---------------------------------------------------------------------------------------------------------------------------
Eval::Eval( Hand && hero, Hand && opp )
    : hero( std::move( hero ) ), opp( std::move( opp ) ) /*,
       heroHsl( HandStrengthList{} ), oppHsl( HandStrengthList{} )*/
{
    assert( this->opp != this->hero );
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
void Eval::setHeroH( const std::string & lCardStr, const std::string & rCardStr ) {
    hero.setHand( lCardStr, rCardStr );
}
//---------------------------------------------------------------------------------------------------------------------------
void Eval::setOppH( const std::string & lCardStr, const std::string & rCardStr ) { opp.setHand( lCardStr, rCardStr ); }
//---------------------------------------------------------------------------------------------------------------------------
void Eval::setHeroH( Hand && hero ) { this->hero = std::move( hero ); }
//---------------------------------------------------------------------------------------------------------------------------
void Eval::setOppH( Hand && opp ) { this->opp = std::move( opp ); }
//---------------------------------------------------------------------------------------------------------------------------
const Hand & Eval::getHeroH() const { return hero; }
//---------------------------------------------------------------------------------------------------------------------------
const Hand & Eval::getOppH() const { return opp; }
//---------------------------------------------------------------------------------------------------------------------------
bool Eval::isEqHands() const { return ( hero == opp ); }
//---------------------------------------------------------------------------------------------------------------------------
void Eval::calc( const Board & __board ) {
    auto boardPtr = std::make_unique< Board >( __board );
    boardPtr->calcTraits();
    auto deck = std::make_unique< Deck >(__board, this->hero, this->opp);
    auto hsHero = std::make_unique< HandStrength >( hero, *boardPtr );
    auto hsOpp = std::make_unique< HandStrength >( opp, *boardPtr );

    switch ( boardPtr->getState() ) {
    case Board::boardState::FLOP:
        break;

    case Board::boardState::TURN: {

        if ( hsHero->containStraitFlush() ) {
            ev.reset( straitflushVSall( hero, opp, boardPtr.operator*() ).release() );
        }

        else if ( hsHero->containKare() ) {
            ev.reset( kareVSall( hero, opp, boardPtr.operator*() ).release() );
        }

        else if ( hsHero->containFullHouse() ) {
            ev->heroEV = 1.0f;
            ev->oppEV = 0.0f;
            ev->tieEV = 0.0f;
        }

        else if ( hsHero->containFlush() ) {
        }

        else if ( hsHero->containStrait() ) {
        }

        else if ( hsHero->containSet() ) {
        }

        else if ( hsHero->containTwoPairs() ) {
        }

        else if ( hsHero->containSet() ) {
        }

        else if ( hsHero->containPair() ) {
        }

        else if ( hsHero->containHight() ) {
            ev.reset( hiVSall< Board::boardState::TURN >( hero, opp, boardPtr.operator*(), deck.operator*() ).release() );
        }

        break;
    }

    case Board::boardState::RIVER:
        break;
    default:
        break;
    }
} // namespace lp
//---------------------------------------------------------------------------------------------------------------------------
void Eval::print() const {
    std::cout << "Hero eq = " << ev->heroEV << std::endl;
    std::cout << "Opp eq = " << ev->oppEV << std::endl;
    std::cout << "Equal eq = " << ev->tieEV << std::endl;
}

} // namespace lp
