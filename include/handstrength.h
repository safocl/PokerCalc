//#pragma once
#ifndef HANDSTRENGTH_H
#define HANDSTRENGTH_H

namespace lp {
class Eval;
struct Hand;
struct Card;
class HandStrengthList;
class HandStrength;
class Board;
} // namespace lp

//#include "Hand.h"
#include "defines.h"
#include <list>
#include <vector>

namespace lp {

class HandStrength final {
    bool hight, pair, twoPairs, set, strait, flush, fullHouse, kare, straitFlush, fd, sd, gutShot, oneOverCard,
        twoOverCards, backdorFD, backdorSD, backdorGutShot
        //                         ,royal_flush
        ;

  public:
    HandStrength() = delete;
    HandStrength( const Hand & __hand, const Board & __board );
    HandStrength( const std::vector< Card > & __combo );
    HandStrength( const HandStrength & other );

    bool containHight() const;
    bool containPair() const;
    bool containTwoPairs() const;
    bool containSet() const;
    bool containStrait() const;
    bool containFlush() const;
    bool containFullHouse() const;
    bool containKare() const;
    bool containStraitFlush() const;
    bool containFD() const;
    bool containSD() const;
    bool containGutShot() const;
    bool containOneOverCard() const;
    bool containTwoOverCards() const;
    bool containBackdorFD() const;
    bool containBackdorSD() const;
    bool containBackdorGutShot() const;

    void calcCurrStrength( const Hand & hand, const Board & board );
    void calcCurrStrength( const std::vector< Card > & combo );

  private:
    bool matchStraitflush( const std::vector< Card > & combo, const uint32_t & comboN ) const;
    bool matchKare( const std::vector< Card > & combo ) const;
    bool matchFullhouse( const std::vector< Card > & combo ) const;
    bool matchFlush( const std::vector< Card > & combo, const uint32_t & comboN ) const;
    bool matchStrait( const uint32_t & comboN ) const;
    bool matchSet( const std::vector< Card > & combo ) const;
    bool matchTwopairs( const std::vector< Card > & combo ) const;
    std::vector< Card > sortCards( std::vector< Card > combo ) const;
};

class HandStrengthList final {
    HandStrengthList();
    HandStrengthList( const HandStrengthList & other );
    void print();
    void calcPercents();
    friend class Eval;
    uint64_t getSum() const;

  private:
    float hightP, pairP, twopairP, setP, straitP, flushP, fullhouseP, kareP, straitflushP;
    uint64_t sum_cycle, hight, pair, twopair, set, strait, flush, fullhouse, kare, straitflush;
};

} // namespace lp

#endif // HANDSTRENGTH_H