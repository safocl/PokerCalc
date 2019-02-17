#include "Board.h"
#include <thread>
#include "equity.h"

namespace lp {

Board::Board() : board_ptr( std::make_unique< std::vector< Card > >() ) { board_ptr->reserve(MAX_SIZE); }
//---------------------------------------------------------------------------------------------------------------------------
const std::vector< Card > & Board::getVector() const { return *board_ptr; }
//---------------------------------------------------------------------------------------------------------------------------
bool Board::pushNewCardToBoard( const Hand & heroHand, const Hand & oppHand, const Card & card ) const {
    bool res = false;
    if ( !board_ptr->empty() && checkCardOnBoard( card ) )
        ;
    else if (	card != heroHand.getCard1() && 
				card != heroHand.getCard2() && 
				card != oppHand.getCard1() && 
				card != oppHand.getCard2()) {
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
void Board::genBoardCards( Deck & deck, const Hand & hero, const Hand & opp, HandStrengthList & hsl, const int & cycles_count ) {    
    int tmp_cycles_count;
    deck.gen( *this, hero, opp );
    for ( auto const & deck_el : deck.getDeckArr() ) {
        if ( pushNewCardToBoard( hero, opp, deck_el ) ) {
            if ( cycles_count > 1 ) {
                tmp_cycles_count = cycles_count - 1;
                genBoardCards( deck, hero, opp, hsl, tmp_cycles_count );
            }
            else
                sumHandStrength( hero, *this, hsl );
            
            board_ptr->erase( board_ptr->end() - 1 );
            deck.gen( *this, hero, opp );
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void Board::parallel_genBoardCards( Deck & deck, const Hand & hero, const Hand & opp, HandStrengthList & hsl, const int & cycles_count ) {
    int tmp_cycles_count;
    deck.gen( *this, hero, opp );
    for ( unsigned count = static_cast< unsigned >( deck.getMinPos() ); 
		  count < static_cast< unsigned >( deck.getMaxPos() ); ++count ) {
        if ( cycles_count > 0 ) {
            tmp_cycles_count = cycles_count - 1;
            if (pushNewCardToBoard( hero, opp, deck.getDeckArr().at( count ) ) ) {
                genBoardCards( deck, hero, opp, hsl, tmp_cycles_count );
                board_ptr->erase( board_ptr->end() - 1 );
                deck.gen( *this, hero, opp );
            }
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void Board::brutforcePreFlop_Flop( Deck & deck, const Hand & hero, const Hand & opp, HandStrengthList & hsl ) {
    int cycles_count = 3;

//    int max_pos;
//    if (hero_h == opp_h)
//        max_pos = 50;
//    else
//        max_pos = 48;
    
	parallel_genBoardCards( deck, hero, opp, std::ref( hsl ), cycles_count );
	
//    int min_pos1 = 0;
//    int max_pos1 = max_pos / 4;
//    thread thread1(parallel_genBoardCards, hero_h, opp_h, min_pos1, max_pos1, std::ref(hsl), cycles_count);
    
//    auto min_pos2 = max_pos1;
//    auto max_pos2 = max_pos1 * 2;
//    thread thread2(parallel_genBoardCards, hero_h, opp_h, min_pos2, max_pos2, std::ref(hsl), cycles_count);
    
//    auto min_pos3 = max_pos2;
//    auto max_pos3 = max_pos1 * 3;
//    thread thread3(parallel_genBoardCards, hero_h, opp_h, min_pos3, max_pos3, std::ref(hsl), cycles_count);
    
//    auto min_pos4 = max_pos3;
//    auto max_pos4 = max_pos;
//    thread thread4(parallel_genBoardCards, hero_h, opp_h, min_pos4, max_pos4, std::ref(hsl), cycles_count);

//    thread1.join();
//    thread2.join();
//    thread3.join();
//    thread4.join();

}

}