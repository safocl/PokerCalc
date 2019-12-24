
//#ifndef EQUITY_H
//#define EQUITY_H

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
#include "defines.h"
#include <memory>
#include <vector>

namespace lp {

struct EV {
    float heroEV{0}, oppEV{0}, tieEV{0};
};

class Eval final {
    std::unique_ptr< EV > ev;
    Hand hero, opp;
    //    HandStrengthList heroHsl, oppHsl;

  public:
    Eval() = delete;
    //    Eval( const Hand & hero, const Hand & opp );
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
    void setHeroH( Hand && hero );
    void setOppH( Hand && opp );
    auto getHeroH() const -> const Hand &;
    auto getOppH() const -> const Hand &;

    void calc( const Board & __board );
    void print() const;

    auto isEqHands() const -> bool;
};

} // namespace lp

//#endif // EQUITY_H
