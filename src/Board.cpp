#include "Board.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "equity.h"
#include "handstrength.h"
#include <thread>

 namespace lp {

Board::Board() : board_ptr( std::make_unique< std::vector< Card > >() ) { board_ptr->reserve( MAX_SIZE ); }
//---------------------------------------------------------------------------------------------------------------------------
const std::vector< Card > & Board::getVector() const { return *board_ptr; }
//---------------------------------------------------------------------------------------------------------------------------
bool Board::pushNewCardToBoard( const Hand & heroHand, const Hand & oppHand, const Card & card ) const {
    bool res = false;
    if ( !board_ptr->empty() && checkCardOnBoard( card ) )
        ;
    else if ( card != heroHand.getlCard() && card != heroHand.getCard2() && card != oppHand.getlCard() &&
              card != oppHand.getCard2() ) {
        board_ptr->push_back( card );
        res = true;
    }

    return res;
}
//---------------------------------------------------------------------------------------------------------------------------
bool Board::checkCardOnBoard( const Card & card ) const {
    bool res = false;
    if ( !board_ptr->empty() ) {
        for ( auto const & el : *board_ptr ) {
            if ( card == el ) {
                res = true;
                break;
            }
        }
    }

    return res;
}
//---------------------------------------------------------------------------------------------------------------------------
void Board::bruteForceCards( Deck & deck, const Hand & hero, const Hand & opp, HandStrengthList & hsl,
                             const int & cycles_count ) {
    int tmp_cycles_count;
    deck.gen( *this, hero, opp );
    for ( auto const & deck_el : deck.getDeckArr() ) {
        if ( pushNewCardToBoard( hero, opp, deck_el ) ) {
            if ( cycles_count > 1 ) {
                tmp_cycles_count = cycles_count - 1;
                bruteForceCards( deck, hero, opp, hsl, tmp_cycles_count );
            } else
                hsl.accumulate( hero, *this );

            board_ptr->erase( board_ptr->end() - 1 );
            deck.gen( *this, hero, opp );
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void Board::bruteForceFirstCard( Deck & deck, const Hand & hero, const Hand & opp, HandStrengthList & hsl,
                                 const int & cycles_count ) {
    int tmp_cycles_count;
    deck.gen( *this, hero, opp );
    for ( unsigned count = static_cast< unsigned >( deck.getMinPos() );
          count < static_cast< unsigned >( deck.getMaxPos() ); ++count ) {
        if ( cycles_count > 0 ) {
            tmp_cycles_count = cycles_count - 1;
            if ( pushNewCardToBoard( hero, opp, deck.getDeckArr().at( count ) ) ) {
                bruteForceCards( deck, hero, opp, hsl, tmp_cycles_count );
                board_ptr->erase( board_ptr->end() - 1 );
                deck.gen( *this, hero, opp );
            }
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void Board::brutforcePreFlop_Flop( Deck & deck, const Hand & hero, const Hand & opp, HandStrengthList & hsl ) {
    int cycles_count = 3;
    bruteForceFirstCard( deck, hero, opp, std::ref( hsl ), cycles_count );
}
//---------------------------------------------------------------------------------------------------------------------------
ParallelGenBoard::ParallelGenBoard( const Hand & hero, const Hand & opp )
    : nCpus( static_cast< int >( std::thread::hardware_concurrency() ) ), maxPos( hero == opp ? 50 : 48 ),
      hero( std::make_unique< Hand >( hero ) ), opp( std::make_unique< Hand >( opp ) ),
      threadQueue( new std::queue< std::thread > ) {}
//---------------------------------------------------------------------------------------------------------------------------
ParallelGenBoard::~ParallelGenBoard() { join(); }
//---------------------------------------------------------------------------------------------------------------------------
void ParallelGenBoard::start( HandStrengthList & hsl ) {
    auto minPos = maxPos / nCpus;
    for ( ; static_cast< int >( threadQueue->size() ) < ( nCpus ); threadQueue->push( std::thread(
              []( Deck &&deck, const Hand hero, const Hand opp, HandStrengthList &hsl ) -> void {
                  auto board = std::make_unique< Board >();
                  board->brutforcePreFlop_Flop( deck, hero, opp, hsl );
              },
              Deck( ( static_cast< int >( threadQueue->size() ) * minPos ),
                    ( ( static_cast< int >( threadQueue->size() ) + 1 ) * minPos ) ),
              Hand( *hero ), Hand( *opp ), std::ref( hsl ) ) ) ) {
    }

    threadQueue->push( std::thread(
        []( Deck && deck, const Hand hero, const Hand opp, HandStrengthList & hsl ) -> void {
            auto board = std::make_unique< Board >();
            board->brutforcePreFlop_Flop( deck, hero, opp, hsl );
        },
        Deck( ( static_cast< int >( threadQueue->size() ) * minPos ), maxPos ), Hand( *hero ), Hand( *opp ),
        std::ref( hsl ) ) );
}
//---------------------------------------------------------------------------------------------------------------------------
void ParallelGenBoard::join() {
    for ( ; ( !threadQueue->empty() ) && threadQueue->front().joinable(); threadQueue->pop() )
        threadQueue->front().join();
}
//---------------------------------------------------------------------------------------------------------------------------

} // namespace lp