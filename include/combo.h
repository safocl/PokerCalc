
//#ifndef COMBO_H
//#define COMBO_H

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
#include "combo.h"
#include <vector>

namespace lp {

std::vector< Card > sortCards( std::vector< Card > combo );

class Combo final {
    std::vector< Card > combo;

  public:
    Combo( const Hand & hand, const Board & board );
    explicit Combo( const Combo & other ) = default;
    Combo( Combo && other ) noexcept = default;
    Combo & operator=( const Combo & other ) = default;
    Combo & operator=( Combo && other ) noexcept = default;
    ~Combo() = default;
    //    bool operator<( const Combo & other );
    //    bool operator>( const Combo & other );
    //    bool operator==( const Combo & other );
};

} // namespace lp

//#endif // COMBO_H
