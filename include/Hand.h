//#pragma once
#ifndef HAND_H
#define HAND_H

namespace lp {
struct Hand;
class Board;
struct Card;
} // namespace lp

#include "Card.h"
#include "defines.h"
#include <vector>

namespace lp {

struct Hand final {
  public:
    Hand() = delete;
    Hand( const Hand & other ) = delete;
    Hand( Hand && other ) noexcept;
    Hand( Card::valCard && __lCardV, Card::suitCard && __lCardS, Card::valCard && __rCardV,
          Card::suitCard && __rCardS );
    Hand( const std::string & __lCardStr, const std::string & __rCardStr );
    ~Hand() = default;

    void setHand( const std::string & __lCard, const std::string & __rCard );
    void setHand( Card::valCard __lCardV, Card::suitCard __lCardS, Card::valCard __rCardV, Card::suitCard __rCardS );
    void setHand( const Card & __lCard, const Card & __rCard );

    /**
     * @brief getHand() getting the value of a hand into variables of type std::string
     * @param lCardStr string buffer for the first card
     * @param rCardStr string buffer for the second card
     */
    void getHand( std::string & __lCardStr, std::string & __rCardStr ) const;
    void getCards( Card & __lCard, Card & __rCard ) const;
    auto isPair() const noexcept -> bool;
    auto getLCard() const -> const Card &;
    auto getRCard() const -> const Card &;
    auto getHigerCard() const -> const Card &;
    auto operator==( const Hand & other ) const -> bool;
    auto operator!=( const Hand & other ) const -> bool;
    Hand & operator=( const Hand & other ) = delete;
    Hand & operator=( Hand && other ) noexcept;

  private:
    Card lCard, rCard;
};

} // namespace lp

#endif // HAND_H