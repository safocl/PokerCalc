#include "equity.h"
#include "Board.h"
#include "Hand.h"
#include "handstrength.h"
#include <iostream>
#include <thread>
#include <cassert>

// namespace lp {


//---------------------------------------------------------------------------------------------------------------------------
//void sumHandStrength( const Hand & hand, const Board & board, HandStrengthList & hsl ) {
//    HandStrength pl_strangth{ hand, board };
//    switch ( pl_strangth.getCurrStrength() ) {
//    case HandStrength::strength::HIGHT:
//        ++hsl.hight;
//		break;
//    case HandStrength::strength::PAIR:
//        ++hsl.pair;
//        break;
//    case HandStrength::strength::SET:
//        ++hsl.set;
//        break;
//    case HandStrength::strength::TWO_PAIRS:
//        ++hsl.twopair;
//        break;
//    case HandStrength::strength::STRAIT:
//        ++hsl.strait;
//        break;
//    case HandStrength::strength::FLUSH:
//        ++hsl.FLUSH;
//        break;
//    case HandStrength::strength::FULL_HOUSE:
//        ++hsl.fullhouse;
//        break;
//    case HandStrength::strength::STRAIT_FLUSH:
//        ++hsl.straitFLUSH;
//        break;
//    case HandStrength::strength::KARE:
//        ++hsl.kare;
//        break;
//	case HandStrength::strength::NODEF:
//		assert(false && "is no define strength");
//    }
//}

//} // namespace lp