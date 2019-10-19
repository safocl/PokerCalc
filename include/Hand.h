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
    Hand( const Hand & other );
    Hand( Hand && other );
    Hand( Card::valCard && __lCardV, Card::suitCard && __lCardS, Card::valCard && __rCardV,
          Card::suitCard && __rCardS );
    Hand( const std::string __lCardStr, const std::string __rCardStr );
    ~Hand();

    void setHand( const std::string __lCard, const std::string __rCard );
    void setHand( Card::valCard __lCardV, Card::suitCard __lCardS, Card::valCard __rCardV, Card::suitCard __rCardS );
    void setHand( const Card & lCard, const Card & rCard );

    /**
     * @brief getHand() getting the value of a hand into variables of type std::string
     * @param lCardStr string buffer for the first card
     * @param rCardStr string buffer for the second card
     */
    void getHand( std::string & __lCardStr, std::string & __rCardStr ) const;
    void getCards( Card & __lCard, Card & __rCard ) const;
	bool isPair() const noexcept;
    const Card & getLCard() const;
    const Card & getRCard() const;
	const Card & getHigerCard() const;
    bool operator==( const Hand & other ) const;
    bool operator!=( const Hand & other ) const;
    Hand & operator=( const Hand & other );
    Hand & operator=( Hand && other );

  private:
    Card lCard, rCard;
};

} // namespace lp

#endif // HAND_H