//#pragma once
#ifndef _DECK_H_
#define _DECK_H_


#include <vector>
#include "Card.h"
#include "Hand.h"
//#include "Board.h"
#include "defines.h"

using namespace std;


struct Deck final
{
    void Refrash(const vector<Card> &board, const Hand &heroHand, const Hand &oppHand);

    const size_num & capacity() const;
    
    unsigned long size() const;
    
    const vector<Card> & getDeckArr() const;

private:
    vector<Card> deckArr;
    const size_num SIZE_DeckArr = 52;
};



#endif // _DECK_H_