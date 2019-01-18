#pragma once



#include <iostream>
#include <vector>
#include "Hand.h"
#include "Deck.h"
#include "defines.h"


using namespace std;



bool pushNewCardToBoard(vector<Card> &board, const Hand &heroHand, const Hand &oppHand, const Card &card);
bool brute_force_matching_cards(const vector<Card> &board, const Card &card);
