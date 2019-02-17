//#pragma once
#ifndef HAND_H
#define HAND_H


#include <vector>
#include "Card.h"
#include "defines.h"

namespace lp {


struct Hand final
{
    Hand();
    Hand(const Hand & other);
    Hand(Hand && other);
    Hand(Card::valCard numValueCard1, Card::suitCard numSuitCard1,
         Card::valCard numValueCard2, Card::suitCard numSuitCard2);
    Hand(const std::string str1, const std::string str2);
    
    ~Hand();

	// Указание руки
	void setHand (const std::string card1_, const std::string card2_);

    void setHand (Card::valCard numValueCard1, Card::suitCard numSuitCard1,
                  Card::valCard numValueCard2, Card::suitCard numSuitCard2);

	void setHand (const Card &card1, const Card &card2);

    /**
     * @brief getHand() getting the value of a hand into variables of type std::string
     * @param card1_str string buffer for the first card
     * @param card2_str string buffer for the second card
     */
    void getHand(std::string & card1_str, std::string & card2_str) const;
    void getCards(Card &card1_, Card &card2_) const;
    const Card & getCard1 () const;
    const Card & getCard2 () const;
    bool operator== (const Hand &other) const;
    bool operator!= (const Hand &other) const;
    Hand & operator = (const Hand & other);
    Hand & operator = (Hand && other);

private:
    Card card1,
		 card2;
};

}

#endif //HAND_H