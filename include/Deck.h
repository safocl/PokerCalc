
#ifndef DECK_H
#define DECK_H

#include <utility>
#include <QVector>
#include "Card.h"
#include "Hand.h"
#include "defines.h"

using namespace std;


struct Deck final
{
    Deck();
    Deck(Deck && other);
    Deck(const Deck & other) = delete ;
    Deck & operator = (Deck && other);
    void gen(const unique_ptr< QVector<Card> > & board_ptr, const Hand &heroHand, const Hand &oppHand);
//    const int & capacity() const;
    int size() const;
    const unique_ptr<QVector<Card> > &getDeckArr() const;
private:
    unique_ptr< QVector<Card> > deckArr;
    static constexpr int SIZE_DeckArr = 52;
};



#endif // DECK_H