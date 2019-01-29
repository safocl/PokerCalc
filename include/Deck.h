
#ifndef DECK_H
#define DECK_H

#include <utility>
#include <QVector>
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
    void gen(const QVector<Card> &board, const Hand &heroHand, const Hand &oppHand);
//    const size_t & capacity() const;
    int size() const;
    const QVector<Card> & getDeckArr() const;
private:
    QVector<Card> deckArr;
    static constexpr size_t SIZE_DeckArr = 52;
};



#endif // DECK_H