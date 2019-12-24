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

#include "Board.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "combo.h"
#include "equity.h"
#include "handstrength.h"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <stdexcept>
#include <thread>

namespace lp {

static bool isQuadImpl( const Board & board );
static bool isTrippleImpl( const Board & board );
static bool isPariedImpl( const Board & board );
static bool isMonotoneImpl( const Board & board );
static bool isTwoToneImpl( const Board & board );
static bool isRainbowImpl( const Board & board );
static bool isAllConnectedImpl( const Board & board );

//---------------------------------------------------------------------------------------------------------------------------
Board::Board()
    : board( std::vector< Card >{} ) /*, _isCalcTraits( false ), _isQuad( false ), _isTripple( false ), _isParied( false
       ), _isMonotone( false ), _isTwoTone( false ), _isRainbow( false ), _isAllConnected( false )*/
{
    board.reserve( MAX_SIZE );
}
//---------------------------------------------------------------------------------------------------------------------------
// Board::Board( const Board & other ) : board( std::vector< Card >{other.getBoard()} ) {}
//---------------------------------------------------------------------------------------------------------------------------
const std::vector< Card > & Board::getBoard() const {
    if ( getState() == boardState::INVALID )
        throw std::runtime_error( "invalid board" );
    return board;
}
//---------------------------------------------------------------------------------------------------------------------------
Board::boardState Board::getState() const {
    switch ( board.size() ) {
    case 0:
        return boardState::PREFLOP;
    case 3:
        return boardState::FLOP;
    case 4:
        return boardState::TURN;
    case 5:
        return boardState::RIVER;
    default:
        return boardState::INVALID;
        //        throw std::runtime_error( "invalid board" );
    }
}
//---------------------------------------------------------------------------------------------------------------------------
bool Board::pushNewCardToBoard( const Hand & hero, const Hand & opp, const Card & card ) {
    if ( !checkCardOnBoard( card ) && card != hero.getLCard() && card != hero.getRCard() && card != opp.getLCard() &&
         card != opp.getRCard() && getState() != boardState::RIVER ) {
        board.push_back( card );
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------
bool Board::checkCardOnBoard( const Card & card ) const {
    //    bool res = false;
    if ( !board.empty() ) {
        if ( std::any_of( board.cbegin(), board.cend(), [&card]( const Card & el ) { return card == el; } ) )
            return true;

        //        for ( auto const & el : board ) {
        //            if ( card == el ) {
        //                res = true;
        //                break;
        //            }
        //        }
    }

    //    return res;
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------
void Board::calcTraits() {
    _isQuad = isQuadImpl( *this );
    if ( !_isQuad ) {
        _isTripple = isTrippleImpl( *this );
        if ( !_isTripple ) {
            _isParied = isPariedImpl( *this );

            if ( !( _isParied ) ) {
                _isMonotone = isMonotoneImpl( *this );
                _isAllConnected = isAllConnectedImpl( *this );

                if ( !_isMonotone )
                    _isTwoTone = isTwoToneImpl( *this );
            }
        }
    }
    if ( !( _isMonotone || _isTwoTone ) )
        _isRainbow = isRainbowImpl( *this );
    _isCalcTraits = true;
}
//---------------------------------------------------------------------------------------------------------------------------
static bool isQuadImpl( const Board & board ) {
    if ( static_cast< uint8_t >( board.getState() ) < static_cast< uint8_t >( Board::boardState::TURN ) )
        throw std::runtime_error( "checking with not valid board size" );
    else {
        uint8_t match = 0;
        for ( uint8_t count1 = 0; count1 < board.getBoard().size() - 4; ++count1 ) {
            match = 0;
            for ( uint8_t count2 = count1 + 1; count2 < board.getBoard().size(); ++count2 ) {
                if ( board.getBoard().at( count1 ).getValueNum() == board.getBoard().at( count2 ).getValueNum() )
                    ++match;
            }
        }
        return match == 3;
    }
}
//---------------------------------------------------------------------------------------------------------------------------
static bool isTrippleImpl( const Board & board ) {
    if ( static_cast< uint8_t >( board.getState() ) < static_cast< uint8_t >( Board::boardState::FLOP ) )
        throw std::runtime_error( "checking with not valid board size" );
    else {
        uint8_t match = 0;
        for ( uint8_t count1 = 0; count1 < board.getBoard().size() - 3; ++count1 ) {
            match = 0;
            for ( uint8_t count2 = count1 + 1; count2 < board.getBoard().size(); ++count2 ) {
                if ( board.getBoard().at( count1 ).getValueNum() == board.getBoard().at( count2 ).getValueNum() )
                    ++match;
            }
        }
        return match == 2;
    }
}
//---------------------------------------------------------------------------------------------------------------------------
static bool isPariedImpl( const Board & board ) {
    if ( static_cast< uint8_t >( board.getState() ) < static_cast< uint8_t >( Board::boardState::FLOP ) )
        throw std::runtime_error( "checking with not valid board size" );
    else {
        uint8_t match = 0;
        for ( uint8_t count1 = 0; count1 < board.getBoard().size() - 2; ++count1 ) {
            match = 0;
            for ( uint8_t count2 = count1 + 1; count2 < board.getBoard().size(); ++count2 ) {
                if ( board.getBoard().at( count1 ).getValueNum() == board.getBoard().at( count2 ).getValueNum() )
                    ++match;
            }
        }
        return match == 1;
    }
}
//---------------------------------------------------------------------------------------------------------------------------
static bool isMonotoneImpl( const Board & board ) {
    if ( static_cast< uint8_t >( board.getState() ) < static_cast< uint8_t >( Board::boardState::FLOP ) )
        throw std::runtime_error( "checking with not valid board size" );
    else {
        for ( uint8_t count = 1; count < board.getBoard().size(); ++count ) {
            if ( board.getBoard().at( 0 ).getSuitNum() != board.getBoard().at( count ).getSuitNum() )
                return false;
        }
    }
    return true;
}
//---------------------------------------------------------------------------------------------------------------------------
static bool isTwoToneImpl( const Board & board ) {
    if ( static_cast< uint8_t >( board.getState() ) < static_cast< uint8_t >( Board::boardState::TURN ) )
        throw std::runtime_error( "checking with not valid board size" );
    else {
        switch ( board.getState() ) {
        case Board::boardState::TURN:
            return ( ( board.getBoard().at( 0 ).getSuitNum() == board.getBoard().at( 1 ).getSuitNum() ) &&
                     ( board.getBoard().at( 2 ).getSuitNum() == board.getBoard().at( 3 ).getSuitNum() ) ) ||
                   ( ( board.getBoard().at( 0 ).getSuitNum() == board.getBoard().at( 2 ).getSuitNum() ) &&
                     ( board.getBoard().at( 1 ).getSuitNum() == board.getBoard().at( 3 ).getSuitNum() ) ) ||
                   ( ( board.getBoard().at( 0 ).getSuitNum() == board.getBoard().at( 3 ).getSuitNum() ) &&
                     ( board.getBoard().at( 1 ).getSuitNum() == board.getBoard().at( 2 ).getSuitNum() ) );
        case Board::boardState::RIVER:
            return ( 
                    (
                     (
                      board.getBoard().at( 0 ).getSuitNum() == 
                      board.getBoard().at( 1 ).getSuitNum()
                     ) &&  
                     (
                      board.getBoard().at( 2 ).getSuitNum() ==
                      board.getBoard().at( 0 ).getSuitNum()
                     ) 
                    ) &&
                    (
                     board.getBoard().at( 3 ).getSuitNum() == 
                     board.getBoard().at( 4 ).getSuitNum() 
                    )
                   ) ||
                   (
                    (
                     (
                      board.getBoard().at( 1 ).getSuitNum() == 
                      board.getBoard().at( 2 ).getSuitNum()
                     ) &&
                     (
                      board.getBoard().at( 3 ).getSuitNum() ==
                      board.getBoard().at( 1 ).getSuitNum()
                     ) 
                    ) &&
                    ( 
                     board.getBoard().at( 0 ).getSuitNum() == 
                     board.getBoard().at( 4 ).getSuitNum() 
                    )
                   ) ||
                   (
                    (
                     board.getBoard().at( 2 ).getSuitNum() ==
                     board.getBoard().at( 3 ).getSuitNum() &&
                     board.getBoard().at( 4 ).getSuitNum() ==
                     board.getBoard().at( 2 ).getSuitNum()
                    ) &&
                    (board.getBoard().at( 0 ).getSuitNum() ==
                     board.getBoard().at( 2 ).getSuitNum() 
                    )
                   ) ||
                   (
                    (
                     board.getBoard().at( 0 ).getSuitNum() ==
                     board.getBoard().at( 2 ).getSuitNum() &&
                     board.getBoard().at( 3 ).getSuitNum() ==
                     board.getBoard().at( 0 ).getSuitNum()
                    ) &&
                    (
                     board.getBoard().at( 1 ).getSuitNum() ==
                     board.getBoard().at( 4 ).getSuitNum()
                    )
                   ) ||
                   (
                    (
                     board.getBoard().at( 1 ).getSuitNum() ==
                     board.getBoard().at( 3 ).getSuitNum() &&
                     board.getBoard().at( 4 ).getSuitNum() ==
                     board.getBoard().at( 1 ).getSuitNum()
                    ) &&
                    (
                     board.getBoard().at( 0 ).getSuitNum() == 
                     board.getBoard().at( 2 ).getSuitNum() 
                    )
                   ) ||
                   (
                    (
                     board.getBoard().at( 0 ).getSuitNum() ==
                     board.getBoard().at( 1 ).getSuitNum() &&
                     board.getBoard().at( 3 ).getSuitNum() ==
                     board.getBoard().at( 0 ).getSuitNum()
                    ) &&
                    (
                     board.getBoard().at( 2 ).getSuitNum() ==
                     board.getBoard().at( 4 ).getSuitNum() 
                    )
                   ) ||
                   (
                    (
                     board.getBoard().at( 1 ).getSuitNum() ==
                     board.getBoard().at( 2 ).getSuitNum() &&
                     board.getBoard().at( 4 ).getSuitNum() ==
                     board.getBoard().at( 1 ).getSuitNum()
                    ) &&
                    (
                     board.getBoard().at( 0 ).getSuitNum() ==
                     board.getBoard().at( 3 ).getSuitNum() 
                    )
                   ) ||
                   (
                    (
                     board.getBoard().at( 0 ).getSuitNum() ==
                     board.getBoard().at( 2 ).getSuitNum() &&
                     board.getBoard().at( 4 ).getSuitNum() ==
                     board.getBoard().at( 0 ).getSuitNum()
                    ) &&
                    (
                     board.getBoard().at( 1 ).getSuitNum() ==
                     board.getBoard().at( 3 ).getSuitNum() 
                    )
                   );

        default:
            return false;
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
static bool isRainbowImpl( const Board & board ) {
    switch ( board.getState() ) {
    case Board::boardState::RIVER:
        return false;

    default:
        uint8_t match = 0;
        for ( uint8_t count1 = 0; count1 < board.getBoard().size() - 1; ++count1 ) {
            for ( uint8_t count2 = count1 + 1; count2 < board.getBoard().size(); ++count2 ) {
                if ( board.getBoard().at( count1 ) == board.getBoard().at( count2 ) )
                    ++match;
            }
        }
        return match == 0;
    }
}
//---------------------------------------------------------------------------------------------------------------------------
static bool isAllConnectedImpl( const Board & board ) {
    if ( board.getState() != Board::boardState::PREFLOP ) {
        auto sortArrPtr = std::make_unique< std::vector< Card > >( sortCards( board.getBoard() ) );

        switch ( board.getState() ) {
        case Board::boardState::FLOP: {
            uint32_t sortCombo = static_cast< uint32_t >( sortArrPtr->at( 0 ).getValueNum() ) |
                                 static_cast< uint32_t >( sortArrPtr->at( 1 ).getValueNum() ) |
                                 static_cast< uint32_t >( sortArrPtr->at( 2 ).getValueNum() );
            uint64_t connected = static_cast< uint32_t >( Card::valCard::_2 ) |
                                 static_cast< uint32_t >( Card::valCard::_3 ) |
                                 static_cast< uint32_t >( Card::valCard::_4 );
            constexpr uint64_t connectedMAX =
                1 + ( static_cast< uint32_t >( Card::valCard::_Q ) | static_cast< uint32_t >( Card::valCard::_K ) |
                      static_cast< uint32_t >( Card::valCard::_A ) );

            for ( ; connected < connectedMAX; connected <<= 1 ) {
                if ( sortCombo == connected ) {
                    return true;
                }
            }

            break;
        }
        case Board::boardState::TURN: {
            uint32_t sortCombo = static_cast< uint32_t >( sortArrPtr->at( 0 ).getValueNum() ) |
                                 static_cast< uint32_t >( sortArrPtr->at( 1 ).getValueNum() ) |
                                 static_cast< uint32_t >( sortArrPtr->at( 2 ).getValueNum() ) |
                                 static_cast< uint32_t >( sortArrPtr->at( 4 ).getValueNum() );
            uint64_t connected =
                static_cast< uint32_t >( Card::valCard::_2 ) | static_cast< uint32_t >( Card::valCard::_3 ) |
                static_cast< uint32_t >( Card::valCard::_4 ) | static_cast< uint32_t >( Card::valCard::_5 );

            constexpr uint64_t connectedMAX =
                1 + ( static_cast< uint32_t >( Card::valCard::_J ) | static_cast< uint32_t >( Card::valCard::_Q ) |
                      static_cast< uint32_t >( Card::valCard::_K ) | static_cast< uint32_t >( Card::valCard::_A ) );

            for ( ; connected < connectedMAX; connected <<= 1 ) {
                if ( sortCombo == connected ) {
                    return true;
                }
            }
            break;
        }
        case Board::boardState::RIVER: {
            uint32_t sortCombo = static_cast< uint32_t >( sortArrPtr->at( 0 ).getValueNum() ) |
                                 static_cast< uint32_t >( sortArrPtr->at( 1 ).getValueNum() ) |
                                 static_cast< uint32_t >( sortArrPtr->at( 2 ).getValueNum() ) |
                                 static_cast< uint32_t >( sortArrPtr->at( 4 ).getValueNum() ) |
                                 static_cast< uint32_t >( sortArrPtr->at( 5 ).getValueNum() );
            uint64_t connected26 =
                static_cast< uint32_t >( Card::valCard::_2 ) | static_cast< uint32_t >( Card::valCard::_3 ) |
                static_cast< uint32_t >( Card::valCard::_4 ) | static_cast< uint32_t >( Card::valCard::_5 ) |
                static_cast< uint32_t >( Card::valCard::_6 );

            constexpr uint64_t connectedMAX =
                1 + static_cast< uint32_t >( Card::valCard::_T ) | static_cast< uint32_t >( Card::valCard::_J ) |
                static_cast< uint32_t >( Card::valCard::_Q ) | static_cast< uint32_t >( Card::valCard::_K ) |
                static_cast< uint32_t >( Card::valCard::_A );

            constexpr uint32_t connectedA5 =
                static_cast< uint32_t >( Card::valCard::_A ) | static_cast< uint32_t >( Card::valCard::_2 ) |
                static_cast< uint32_t >( Card::valCard::_3 ) | static_cast< uint32_t >( Card::valCard::_4 ) |
                static_cast< uint32_t >( Card::valCard::_5 );

            if ( sortCombo == connectedA5 )
                return true;

            for ( ; connected26 < connectedMAX; connected26 <<= 1 ) {
                if ( sortCombo == connected26 ) {
                    return true;
                }
            }
            break;
        }
        default:
            break;
        }
    }
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------
bool Board::isQuad() const { return _isQuad; }
//---------------------------------------------------------------------------------------------------------------------------
bool Board::isTripple() const { return _isTripple; }
//---------------------------------------------------------------------------------------------------------------------------
bool Board::isParied() const { return _isParied; }
//---------------------------------------------------------------------------------------------------------------------------
bool Board::isMonotone() const { return _isMonotone; }
//---------------------------------------------------------------------------------------------------------------------------
bool Board::isTwoTone() const { return _isTwoTone; }
//---------------------------------------------------------------------------------------------------------------------------
bool Board::isRainbow() const { return _isRainbow; }
//---------------------------------------------------------------------------------------------------------------------------
bool Board::isAllConnected() const { return _isAllConnected; }
//---------------------------------------------------------------------------------------------------------------------------
bool Board::isCalcTraits() const { return _isCalcTraits; }

const Card & Board::getLowerCard() const {
    auto card = std::make_unique< Card >( Card::valCard::_A, Card::suitCard::NODEF );
    for ( const auto & el : board ) {
        if ( el < card.operator*() )
            card.operator*() = el;
    }
    return card.operator*();
}
//---------------------------------------------------------------------------------------------------------------------------
// ParallelGenBoard::ParallelGenBoard( const Eval & ev )
//    : nCpus( static_cast< int >( std::thread::hardware_concurrency() ) ), maxPos( ev.isEqHands() ? 50 : 48 ),
//      threadQueue( std::queue< std::thread >{} ) {}
//---------------------------------------------------------------------------------------------------------------------------
// ParallelGenBoard::~ParallelGenBoard() { join(); }
//---------------------------------------------------------------------------------------------------------------------------
// void ParallelGenBoard::start( Eval & ev ) {
//    auto minPos = maxPos / nCpus;
//    for ( ; static_cast< int >( threadQueue.size() ) < ( nCpus ); threadQueue.push( std::thread(
//              []( Deck &&deck, Eval &ev ) -> void {
//                  auto board = std::make_unique< Board >();
//                  board->brutforcePreFlop_Flop( deck, ev );
//              },
//              Deck( ( static_cast< int >( threadQueue.size() ) * minPos ),
//                    ( ( static_cast< int >( threadQueue.size() ) + 1 ) * minPos ) ),
//              ev ) ) ) {
//    }

//    threadQueue.push( std::thread(
//        []( Deck && deck, Eval & ev ) -> void {
//            auto board = std::make_unique< Board >();
//            board->brutforcePreFlop_Flop( deck, ev );
//        },
//        Deck( ( static_cast< int >( threadQueue.size() ) * minPos ), maxPos ), ev ) );
//}
//---------------------------------------------------------------------------------------------------------------------------
// void ParallelGenBoard::join() {
//    for ( ; ( !threadQueue.empty() ) && threadQueue.front().joinable(); threadQueue.pop() )
//        threadQueue.front().join();
//}
//---------------------------------------------------------------------------------------------------------------------------

} // namespace lp
