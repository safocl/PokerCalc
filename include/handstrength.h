//#pragma once
#ifndef HANDSTRENGTH_H
#define HANDSTRENGTH_H

// namespace lp {
struct Hand;
struct Card;
struct HandStrengthList;
class Board;
//}

//#include "Hand.h"
#include "defines.h"
#include <atomic>
#include <vector>

// namespace lp {

struct HandStrength final {
    HandStrength( const Hand & hand, const Board & board );
    HandStrength( const HandStrength & other );
    enum class strength {
        NODEF = -1,
        HIGHT,
        PAIR,
        TWO_PAIRS,
        SET,
        STRAIT,
        FLUSH,
        FULL_HOUSE,
        KARE,
        STRAIT_FLUSH
        //                         ,ROYAL_FLUSH
    };
    const strength & getCurrStrength() const;
    strength checkCurrStrength( const Hand & hand, const Board & board );

  private:
    strength curr_strength;
    bool match_straitFLUSH( const std::vector< Card > & combo_ptr, const uint32_t & combo ) const;
    bool match_kare( const std::vector< Card > & combo_ptr ) const;
    bool match_fullhouse( const std::vector< Card > & combo_ptr ) const;
    bool match_flush( const std::vector< Card > & combo_ptr, const uint32_t & combo ) const;
    bool match_strait( const uint32_t & combo ) const;
    bool match_set( const std::vector< Card > & combo_ptr ) const;
    bool match_twopairs( const std::vector< Card > & combo_ptr ) const;
    std::unique_ptr< std::vector< Card > > sort_cards( const std::vector< Card > & combo_ptr ) const;
};

struct HandStrengthList final {
    HandStrengthList();
    void accumulate( const Hand & hand, const Board & board );
	void print() const;
	
  private:
    std::atomic< unsigned long long > hight, pair, twopair, set, strait, flush, fullhouse, kare, straitflush;
};

//} // namespace lp

#endif // HANDSTRENGTH_H