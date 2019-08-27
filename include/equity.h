//#pragma once
#ifndef EQUITY_H
#define EQUITY_H

namespace lp {

struct Hand;
struct HandStrengthList;
class Combo;
class Eval;
struct Card;
class Board;

} // namespace lp

//#include <atomic>
//#include <functional>
#include "Board.h"
#include "Hand.h"
#include "handstrength.h"
#include <memory>
#include <vector>

namespace lp {

class Eval final {
    float heroEquity, oppEquity, tieEquity;
    Hand hero, opp;
    HandStrengthList heroHsl, oppHsl;
    unsigned long long wHero, wOpp, wHeroTmp, wOppTmp;

  public:
    Eval();
    void setheroH( const Card::valCard lCardV, const Card::suitCard lCardS, const Card::valCard rCardV,
                      const Card::suitCard rCardS );
    void setoppH( const Card::valCard lCardV, const Card::suitCard lCardS, const Card::valCard rCardV,
                     const Card::suitCard rCardS );
    void setheroH( const std::string lCardStr, const std::string rCardStr );
    void setoppH( const std::string lCardStr, const std::string rCardStr );
    void setheroH( const Hand & hero );
    void setoppH( const Hand & opp );
    const Hand & getHeroH() const;
    const Hand & getOppH() const;

    void accumulate( const Board & board );
    void calc();
    void print() const;

    bool isEqHands() const;
};

class Combo final {
    std::vector< Card > combo;

  public:
    Combo( const Hand & hand, const Board & board );
    bool operator<( const Combo & other );
    bool operator>( const Combo & other );
    bool operator==( const Combo & other );
};

} // namespace lp

#endif // EQUITY_H
