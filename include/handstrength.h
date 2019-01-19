#pragma once



#include <vector>
#include "Card.h"
#include "Hand.h"
#include "Board.h"
#include "Deck.h"
#include "defines.h"

using namespace std;


struct HandStrength
{
    HandStrength(const Hand &hand, const vector<Card> &board);
    
    enum strength {HIGHT, PAIR, TWO_PAIRS, SET, STRAIT, FLASH, FULL_HOUSE, CARE, STRAIT_FLASH, ROYAL_FLASH};
    
    strength getCurrStrength() const;
    

    
private:
    strength curr_strength;
    strength checkCurrStrength(const Hand &hand, const vector<Card> &board) const;
    bool match_straitflash(const vector<Card> &combo) const;
    bool match_kare(const vector<Card> &combo) const;
    bool match_fullhouse(const vector<Card> &combo) const;
    bool match_flash(const vector<Card> &combo) const;
    bool match_strait(const vector<Card> &combo) const;
    bool match_set(const vector<Card> &combo) const;
    bool match_twopairs(const vector<Card> &combo) const;
};

vector<Card> sort_cards(const vector<Card> &combo);