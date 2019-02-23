//#pragma once
#ifndef HAND_H
#define HAND_H

// namespace lp {
struct Hand;
class Board;
struct Card;
//} // namespace lp

#include "Card.h"
#include "defines.h"
#include <vector>

// namespace lp {

struct Hand final {
  public:
    Hand();
    Hand( const Hand & other );
    Hand( Hand && other );
    Hand( Card::valCard lCardV, Card::suitCard lCardS, Card::valCard rCardV, Card::suitCard rCardS );
    Hand( const std::string str1, const std::string str2 );
    ~Hand();

    void setHand( const std::string lCard_, const std::string rCard_ );
    void setHand( Card::valCard lCardV, Card::suitCard lCardS, Card::valCard rCardV, Card::suitCard rCardS );
    void setHand( const Card & lCard, const Card & rCard );

    /**
     * @brief getHand() getting the value of a hand into variables of type std::string
     * @param lCard_str string buffer for the first card
     * @param rCard_str string buffer for the second card
     */
    void getHand( std::string & lCard_str, std::string & rCard_str ) const;
    void getCards( Card & lCard_, Card & rCard_ ) const;
    const Card & getlCard() const;
    const Card & getCard2() const;
    bool operator==( const Hand & other ) const;
    bool operator!=( const Hand & other ) const;
    Hand & operator=( const Hand & other );
    Hand & operator=( Hand && other );

  private:
    std::unique_ptr< Card > lCard, rCard;
};

//} // namespace lp

#endif // HAND_H