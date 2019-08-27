#include "Board.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "equity.h"
#include "handstrength.h"
#include <cassert>
#include <thread>

namespace lp {

//---------------------------------------------------------------------------------------------------------------------------
Board::Board() : board( std::vector< Card >{} ) { board.reserve( MAX_SIZE ); }
//---------------------------------------------------------------------------------------------------------------------------
Board::Board( const Board & other ) : board( std::vector< Card >{other.getBoard()} ) {}
//---------------------------------------------------------------------------------------------------------------------------
const std::vector< Card > & Board::getBoard() const { return board; }
//---------------------------------------------------------------------------------------------------------------------------
bool Board::pushNewCardToBoard( const Hand & heroH, const Hand & oppH, const Card & card ) {
    if ( !checkCardOnBoard( card ) && card != heroH.getLCard() && card != heroH.getRCard() && card != oppH.getLCard() &&
         card != oppH.getRCard() ) {
        board.push_back( card );
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------
bool Board::checkCardOnBoard( const Card & card ) const {
    bool res = false;
    if ( !board.empty() ) {
        for ( auto const & el : board ) {
            if ( card == el ) {
                res = true;
                break;
            }
        }
    }

    return res;
}
//---------------------------------------------------------------------------------------------------------------------------
void Board::bruteForceCards( Deck & deck, Eval ev, const unsigned int & cyclesCount ) {
    assert( cyclesCount < 6 && "Unavaible number cycles count" );
    unsigned int tmpCyclesCount;
    deck.gen( *this, ev.getHeroH(), ev.getOppH() );
    for ( auto const & deck_el : deck.getDeckArr() ) {
        if ( pushNewCardToBoard( ev.getHeroH(), ev.getOppH(), deck_el ) ) {
            if ( cyclesCount > 1 ) {
                tmpCyclesCount = cyclesCount - 1;
                bruteForceCards( deck, ev, tmpCyclesCount );
            } else
                ev.accumulate( *this );
        }

        board.erase( board.end() - 1 );
        deck.gen( *this, ev.getHeroH(), ev.getOppH() );
    }
}
//---------------------------------------------------------------------------------------------------------------------------
template < unsigned int cyclesCount > void Board::bruteForceCardsMT( Deck & deck, Eval & ev ) {
    assert( cyclesCount < 6 && "Unavaible number cycles count" );
    unsigned int tmpCyclesCount;
    deck.gen( *this, ev.getHeroH(), ev.getOppH() );
    for ( unsigned count = static_cast< unsigned >( deck.getMinPos() );
          count < static_cast< unsigned >( deck.getMaxPos() ); ++count ) {
        if ( cyclesCount > 0 ) {
            tmpCyclesCount = cyclesCount - 1;
            if ( pushNewCardToBoard( ev.getHeroH(), ev.getOppH(), deck.getDeckArr().at( count ) ) ) {
                bruteForceCards( deck, ev, tmpCyclesCount );
                board.erase( board.end() - 1 );
                deck.gen( *this, ev.getHeroH(), ev.getOppH() );
            }
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void Board::brutforcePreFlop_Flop( Deck & deck, Eval & ev ) { bruteForceCardsMT< 3 >( deck, ev ); }
//---------------------------------------------------------------------------------------------------------------------------
ParallelGenBoard::ParallelGenBoard( const Eval & ev )
    : nCpus( static_cast< int >( std::thread::hardware_concurrency() ) ), maxPos( ev.isEqHands() ? 50 : 48 ),
      threadQueue( std::queue< std::thread >{} ) {}
//---------------------------------------------------------------------------------------------------------------------------
ParallelGenBoard::~ParallelGenBoard() { join(); }
//---------------------------------------------------------------------------------------------------------------------------
void ParallelGenBoard::start( Eval & ev ) {
    auto minPos = maxPos / nCpus;
    for ( ; static_cast< int >( threadQueue.size() ) < ( nCpus ); threadQueue.push( std::thread(
              []( Deck &&deck, Eval &ev ) -> void {
                  auto board = std::make_unique< Board >();
                  board->brutforcePreFlop_Flop( deck, ev );
              },
              Deck( ( static_cast< int >( threadQueue.size() ) * minPos ),
                    ( ( static_cast< int >( threadQueue.size() ) + 1 ) * minPos ) ),
              ev ) ) ) {
    }

    threadQueue.push( std::thread(
        []( Deck && deck, Eval & ev ) -> void {
            auto board = std::make_unique< Board >();
            board->brutforcePreFlop_Flop( deck, ev );
        },
        Deck( ( static_cast< int >( threadQueue.size() ) * minPos ), maxPos ), ev ) );
}
//---------------------------------------------------------------------------------------------------------------------------
void ParallelGenBoard::join() {
    for ( ; ( !threadQueue.empty() ) && threadQueue.front().joinable(); threadQueue.pop() )
        threadQueue.front().join();
}
//---------------------------------------------------------------------------------------------------------------------------

} // namespace lp