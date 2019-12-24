
//#ifndef HANDSTRENGTH_H
//#define HANDSTRENGTH_H

namespace lp {
struct Card;
struct Deck;
class Board;
class Combo;
struct EV;
class Eval;
struct Hand;
class HandStrength;
} // namespace lp

#pragma once

#include "Card.h"
#include "Hand.h"
#include "Board.h"
#include "equity.h"
#include "defines.h"
#include <list>
#include <vector>

namespace lp {

class HandStrength final {
    bool hight{false}, pair{false}, twoPairs{false}, set{false}, strait{false}, flush{false}, fullHouse{false},
        kare{false}, straitFlush{false}, fd{false}, sd{false}, gutShot{false}, oneOverCard{false}, twoOverCards{false},
        backdorFD{false}, backdorSD{false}, backdorGutShot{false} //                         ,royal_flush{false}
    ;

  public:
    HandStrength() = delete;
    HandStrength( const Hand & __hand, const Board & __board );
    explicit HandStrength( const std::vector< Card > & __combo );
    explicit HandStrength( const HandStrength & other ) = default;
    explicit HandStrength( HandStrength && other ) = default;
    ~HandStrength() = default;

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

    void calcCurrStrength( const Hand & __hand, const Board & __board );
    void calcCurrStrength( const std::vector< Card > & __combo );

//    static std::vector< Card > sortCards( std::vector< Card > combo );

  private:
//    static bool matchStraitflush( const std::vector< Card > & combo, const uint32_t & comboN );
//    static bool matchKare( const std::vector< Card > & combo );
//    static bool matchFullhouse( const std::vector< Card > & combo );
//    static bool matchFlush( const std::vector< Card > & combo, const uint32_t & comboN );
//    static bool matchStrait( const uint32_t & comboN );
//    static bool matchSet( const std::vector< Card > & combo );
//    static bool matchTwopairs( const std::vector< Card > & combo );
};

class HandStrengthList final {
public:
    HandStrengthList() = default;
    HandStrengthList( const HandStrengthList & other ) = default;
    HandStrengthList( HandStrengthList && other ) = default;
    ~HandStrengthList() = default;
    void print();
    void calcPercents();
    friend class Eval;
    uint64_t getSum() const;

  private:
    float hightP{0}, pairP{0}, twopairP{0}, setP{0}, straitP{0}, flushP{0}, fullhouseP{0}, kareP{0}, straitflushP{0};
    uint64_t sum_cycle{0}, hight{0}, pair{0}, twopair{0}, set{0}, strait{0}, flush{0}, fullhouse{0}, kare{0},
        straitflush{0};
};

} // namespace lp

//#endif // HANDSTRENGTH_H
