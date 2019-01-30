
#ifndef DECK_H
#define DECK_H

#include <utility>
#include <vector>
#include "Card.h"
#include "Hand.h"
#include "defines.h"

using namespace std;


struct Deck final
{
    Deck();
    Deck(Deck && other);
    Deck(const Deck & other);
    Deck & operator = (Deck && other);
    void gen(const vector<Card> &board, const Hand &heroHand, const Hand &oppHand);
//    const int & capacity() const;
    unsigned long size() const;
    const vector<Card> & getDeckArr() const;
private:
    vector<Card> deckArr;
    static constexpr int SIZE_DeckArr = 52;
};



#endif // DECK_H