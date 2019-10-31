#include "combo.h"
#include "handstrength.h"
#include <algorithm>
#include <cassert>

namespace lp {

//---------------------------------------------------------------------------------------------------------------------------
Combo::Combo( const Hand & hand, const Board & board ) : combo( std::vector< Card >{board.getBoard()} ) {
    combo.reserve( 7 );
    combo.push_back( hand.getLCard() );
    combo.push_back( hand.getRCard() );
}

} // namespace lp