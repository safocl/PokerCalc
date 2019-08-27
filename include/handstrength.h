//#pragma once
#ifndef HANDSTRENGTH_H
#define HANDSTRENGTH_H

namespace lp {
class Eval;
struct Hand;
struct Card;
struct HandStrengthList;
class Board;
} // namespace lp

//#include "Hand.h"
#include "defines.h"
#include <atomic>
#include <vector>

namespace lp {

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
    strength checkCurrStrength( const std::vector< Card > & combo );

  private:
    strength curr_strength;
    bool matchStraitflush( const std::vector< Card > & combo_ptr, const uint32_t & combo ) const;
    bool matchKare( const std::vector< Card > & combo_ptr ) const;
    bool matchFullhouse( const std::vector< Card > & combo_ptr ) const;
    bool matchFlush( const std::vector< Card > & combo_ptr, const uint32_t & combo ) const;
    bool matchStrait( const uint32_t & combo ) const;
    bool matchSet( const std::vector< Card > & combo_ptr ) const;
    bool matchTwopairs( const std::vector< Card > & combo_ptr ) const;
    std::unique_ptr< std::vector< Card > > sortCards( const std::vector< Card > & combo_ptr ) const;
};

struct HandStrengthList final {
    HandStrengthList();
    HandStrengthList( const HandStrengthList & other );
    void accumulate( const Hand & hand, const Board & board );
    void print();
    void calcPercents();
    friend class Eval;
    unsigned long long getSum() const;

  private:
    float hightP, pairP, twopairP, setP, straitP, flushP, fullhouseP, kareP, straitflushP;
    //    unsigned long long sum_cycle;
    std::atomic< unsigned long long > hight, pair, twopair, set, strait, flush, fullhouse, kare, straitflush;
};

} // namespace lp

#endif // HANDSTRENGTH_H