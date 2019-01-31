#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include "Card.h"
#include "Hand.h"
#include "Deck.h"
#include "defines.h"


using namespace std;


bool pushNewCardToBoard(unique_ptr< QVector<Card> > & board_ptr, const Hand &heroHand, const Hand &oppHand, const Card &card);
bool brute_force_matching_cards(const unique_ptr< QVector<Card> > & board_ptr, const Card &card);

#endif //BOARD_H