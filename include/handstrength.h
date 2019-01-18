#pragma once



#include <vector>
#include "Card.h"
#include "Hand.h"
#include "Board.h"
#include "Deck.h"
#include "handstrength.h"
#include "defines.h"

using namespace std;


struct HandStrength
{
    enum strength {HIGHT, PAIR, TWO_PAIRS, SET, STRAIT, FLASH, FULL_HOUSE, CARE, STRAIT_FLASH, ROYAL_FLASH};
    
    strength getCurrStrength() const;
    
    strength checkCurrStrength(const Hand &hand, const vector<Card> &board);
    
private:
    strength curr_strength;
    bool match_flash(const vector<Card> &combo) const;
    bool match_strait(const vector<Card> &combo) const;
};

vector<Card> sort_cards(const vector<Card> &combo);