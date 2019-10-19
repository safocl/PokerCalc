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
	Eval( const Hand & hero, const Hand & opp );
    Eval( Hand && hero, Hand && opp );
    void setHeroH( const Card::valCard lCardV, const Card::suitCard lCardS, const Card::valCard rCardV,
                   const Card::suitCard rCardS );
    void setOppH( const Card::valCard lCardV, const Card::suitCard lCardS, const Card::valCard rCardV,
                  const Card::suitCard rCardS );
    void setHeroH( const std::string lCardStr, const std::string rCardStr );
    void setOppH( const std::string lCardStr, const std::string rCardStr );
    void setHeroH( const Hand & hero );
    void setOppH( const Hand & opp );
    const Hand & getHeroH() const;
    const Hand & getOppH() const;

    void calc( const Board & board );
    void print() const;

    bool isEqHands() const;
};

} // namespace lp

#endif // EQUITY_H
