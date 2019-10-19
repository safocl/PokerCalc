#include "combo.h"
#include "handstrength.h"
#include <cassert>

namespace lp {

//---------------------------------------------------------------------------------------------------------------------------
Combo::Combo( const Hand & hand, const Board & board ) : combo( std::vector< Card >{} ) {
    combo.reserve( 7 );
    for ( auto const & card : board.getBoard() ) {
        combo.push_back( card );
    }
    combo.push_back( hand.getLCard() );
    combo.push_back( hand.getRCard() );
}

} // namespace lp