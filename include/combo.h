#ifndef COMBO_H
#define COMBO_H

namespace lp {
struct Hand;
class Combo;
struct Card;
class Board;
} // namespace lp

#include "Board.h"
#include "Card.h"
#include "Hand.h"
#include <vector>

namespace lp {

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

#endif // COMBO_H
