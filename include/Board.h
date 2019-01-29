#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include <vector>
#include "Card.h"
#include "Hand.h"
#include "Deck.h"
#include "defines.h"


using namespace std;


bool pushNewCardToBoard(QVector<Card> & board, const Hand &heroHand, const Hand &oppHand, const Card &card);
bool brute_force_matching_cards(const QVector<Card> &board, const Card &card);

#endif //BOARD_H