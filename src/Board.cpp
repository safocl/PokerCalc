#include "Board.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "equity.h"
#include "handstrength.h"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <stdexcept>
#include <thread>

namespace lp {

//---------------------------------------------------------------------------------------------------------------------------
Board::Board()
    : board( std::vector< Card >{} )/*, _isCalcTraits( false ), _isQuad( false ), _isTripple( false ), _isParied( false ),
      _isMonotone( false ), _isTwoTone( false ), _isRainbow( false ), _isAllConnected( false )*/ {
    board.reserve( MAX_SIZE );
}
//---------------------------------------------------------------------------------------------------------------------------
// Board::Board( const Board & other ) : board( std::vector< Card >{other.getBoard()} ) {}
//---------------------------------------------------------------------------------------------------------------------------
const std::vector< Card > & Board::getBoard() const { return board; }
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
        throw std::runtime_error( "invalid board" );
    }
}
//---------------------------------------------------------------------------------------------------------------------------
bool Board::pushNewCardToBoard( const Hand & hero, const Hand & opp, const Card & card ) {
    if ( !checkCardOnBoard( card ) && card != hero.getLCard() && card != hero.getRCard() && card != opp.getLCard() &&
         card != opp.getRCard() ) {
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
void Board::__isQuad() {
    if ( static_cast< uint8_t >( getState() ) < static_cast< uint8_t >( boardState::TURN ) )
        throw std::runtime_error( "checking with not valid board size" );
    else {
        uint8_t match = 0;
        for ( uint8_t count1 = 0; count1 < board.size() - 4; ++count1 ) {
            match = 0;
            for ( uint8_t count2 = count1 + 1; count2 < board.size(); ++count2 ) {
                if ( board.at( count1 ).getValueNum() == board.at( count2 ).getValueNum() )
                    ++match;
            }
        }
        _isQuad = match == 3;
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void Board::__isTripple() {
    if ( static_cast< uint8_t >( getState() ) < static_cast< uint8_t >( boardState::FLOP ) )
        throw std::runtime_error( "checking with not valid board size" );
    else {
        uint8_t match = 0;
        for ( uint8_t count1 = 0; count1 < board.size() - 3; ++count1 ) {
            match = 0;
            for ( uint8_t count2 = count1 + 1; count2 < board.size(); ++count2 ) {
                if ( board.at( count1 ).getValueNum() == board.at( count2 ).getValueNum() )
                    ++match;
            }
        }
        _isTripple = match == 2;
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void Board::__isParied() {
    if ( static_cast< uint8_t >( getState() ) < static_cast< uint8_t >( boardState::FLOP ) )
        throw std::runtime_error( "checking with not valid board size" );
    else {
        uint8_t match = 0;
        for ( uint8_t count1 = 0; count1 < board.size() - 2; ++count1 ) {
            match = 0;
            for ( uint8_t count2 = count1 + 1; count2 < board.size(); ++count2 ) {
                if ( board.at( count1 ).getValueNum() == board.at( count2 ).getValueNum() )
                    ++match;
            }
        }
        _isParied = match == 1;
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void Board::__isMonotone() {
    if ( static_cast< uint8_t >( getState() ) < static_cast< uint8_t >( boardState::FLOP ) )
        throw std::runtime_error( "checking with not valid board size" );
    else {
        _isMonotone = true;
        for ( uint8_t count = 1; count < board.size(); ++count ) {
            if ( board.at( 0 ).getSuitNum() != board.at( count ).getSuitNum() )
                _isMonotone = false;
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void Board::__isTwoTone() {
    if ( static_cast< uint8_t >( getState() ) < static_cast< uint8_t >( boardState::TURN ) )
        throw std::runtime_error( "checking with not valid board size" );
    else {
        switch ( getState() ) {
        case boardState::TURN:
            _isTwoTone = ( board.at( 0 ).getSuitNum() == board.at( 1 ).getSuitNum() &&
                           board.at( 2 ).getSuitNum() == board.at( 3 ).getSuitNum() ) ||
                         ( board.at( 0 ).getSuitNum() == board.at( 2 ).getSuitNum() &&
                           board.at( 1 ).getSuitNum() == board.at( 3 ).getSuitNum() ) ||
                         ( board.at( 0 ).getSuitNum() == board.at( 3 ).getSuitNum() &&
                           board.at( 1 ).getSuitNum() == board.at( 2 ).getSuitNum() );
            break;

        case boardState::RIVER:
            _isTwoTone = ( board.at( 0 ).getSuitNum() == board.at( 1 ).getSuitNum() == board.at( 2 ).getSuitNum() &&
                           board.at( 3 ).getSuitNum() == board.at( 4 ).getSuitNum() ) ||
                         ( board.at( 1 ).getSuitNum() == board.at( 2 ).getSuitNum() == board.at( 3 ).getSuitNum() &&
                           board.at( 0 ).getSuitNum() == board.at( 4 ).getSuitNum() ) ||
                         ( board.at( 2 ).getSuitNum() == board.at( 3 ).getSuitNum() == board.at( 4 ).getSuitNum() &&
                           board.at( 0 ).getSuitNum() == board.at( 2 ).getSuitNum() ) ||
                         ( board.at( 0 ).getSuitNum() == board.at( 2 ).getSuitNum() == board.at( 3 ).getSuitNum() &&
                           board.at( 1 ).getSuitNum() == board.at( 4 ).getSuitNum() ) ||
                         ( board.at( 1 ).getSuitNum() == board.at( 3 ).getSuitNum() == board.at( 4 ).getSuitNum() &&
                           board.at( 0 ).getSuitNum() == board.at( 2 ).getSuitNum() ) ||
                         ( board.at( 0 ).getSuitNum() == board.at( 1 ).getSuitNum() == board.at( 3 ).getSuitNum() &&
                           board.at( 2 ).getSuitNum() == board.at( 4 ).getSuitNum() ) ||
                         ( board.at( 1 ).getSuitNum() == board.at( 2 ).getSuitNum() == board.at( 4 ).getSuitNum() &&
                           board.at( 0 ).getSuitNum() == board.at( 3 ).getSuitNum() ) ||
                         ( board.at( 0 ).getSuitNum() == board.at( 2 ).getSuitNum() == board.at( 4 ).getSuitNum() &&
                           board.at( 1 ).getSuitNum() == board.at( 3 ).getSuitNum() );
            break;

        default:
            break;
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void Board::__isRainbow() {
    switch ( getState() ) {
    case boardState::RIVER:
        _isRainbow = false;
        break;

    default:
        uint8_t match = 0;
        for ( uint8_t count1 = 0; count1 < board.size() - 1; ++count1 ) {
            for ( uint8_t count2 = count1 + 1; count2 < board.size(); ++count2 ) {
                if ( board.at( count1 ) == board.at( count2 ) )
                    ++match;
            }
        }
        _isRainbow = match == 0;
        break;
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void Board::__isAllConnected() {
    _isAllConnected = false;
    if ( getState() != boardState::PREFLOP ) {
        auto sortArrPtr = std::make_unique< std::vector< Card > >( HandStrength::sortCards( board ) );

        switch ( getState() ) {
        case boardState::FLOP: {
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
                    _isAllConnected = true;
                    break;
                }
            }

            break;
        }
        case boardState::TURN: {
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
                    _isAllConnected = true;
                    break;
                }
            }
            break;
        }
        case boardState::RIVER: {
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
                _isAllConnected = true;

            for ( ; connected26 < connectedMAX; connected26 <<= 1 ) {
                if ( sortCombo == connected26 ) {
                    _isAllConnected = true;
                    break;
                }
            }
            break;
        }
        default:
            break;
        }
    }
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