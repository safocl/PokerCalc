#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Card.h"
#include "Hand.h"
#include "Deck.h"
#include "defines.h"


using namespace std;


bool pushNewCardToBoard(unique_ptr< vector<Card> > & board_ptr, const Hand &heroHand, const Hand &oppHand, const unique_ptr<Card> &card);
bool check_for_a_card(const unique_ptr<vector<Card> > &board_ptr, const unique_ptr<Card> &card);

#endif //BOARD_H