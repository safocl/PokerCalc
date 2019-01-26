//#pragma once
#ifndef __DECK_H__
#define __DECK_H__


#include <vector>
#include "Card.h"
#include "Hand.h"
//#include "Board.h"
#include "defines.h"

using namespace std;


struct Deck final
{
    Deck();
//    Deck(Deck && other);
//    Deck(const Deck & other) = delete;
    void gen(const vector<Card> &board, const Hand &heroHand, const Hand &oppHand);
    const size_num & capacity() const;
    unsigned long size() const;
    const vector<Card> & getDeckArr() const;
private:
    vector<Card> deckArr;
    static constexpr size_num SIZE_DeckArr = 52;
};



#endif // __DECK_H__