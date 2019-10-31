//#pragma once
#ifndef EQUITY_H
#define EQUITY_H

namespace lp {

struct Hand;
// class HandStrengthList;
// class Combo;
class Eval;
struct Card;
class Board;

} // namespace lp

//#include <atomic>
//#include <functional>
//#include "Board.h"
#include "Hand.h"
#include "defines.h"
//#include "handstrength.h"
#include <memory>
#include <vector>

namespace lp {

class Eval final {
    float heroEquity, oppEquity, tieEquity;
    Hand hero, opp;
    //    HandStrengthList heroHsl, oppHsl;

  public:
    Eval() = delete;
    Eval( const Hand & hero, const Hand & opp );
    Eval( Hand && hero, Hand && opp );
    Eval( const Eval & other ) = delete;
    Eval( Eval && other ) noexcept = default;
    Eval & operator=( const Eval & other ) = delete;
    Eval & operator=( Eval && other ) noexcept = default;
    ~Eval() = default;
    void setHeroH( Card::valCard lCardV, Card::suitCard lCardS, Card::valCard rCardV, Card::suitCard rCardS );
    void setOppH( Card::valCard lCardV, Card::suitCard lCardS, Card::valCard rCardV, Card::suitCard rCardS );
    void setHeroH( const std::string & lCardStr, const std::string & rCardStr );
    void setOppH( const std::string & lCardStr, const std::string & rCardStr );
    void setHeroH( const Hand & hero );
    void setOppH( const Hand & opp );
    auto getHeroH() const -> const Hand &;
    auto getOppH() const -> const Hand &;

    void calc( const Board & board );
    void print() const;

    auto isEqHands() const -> bool;
};

} // namespace lp

#endif // EQUITY_H
