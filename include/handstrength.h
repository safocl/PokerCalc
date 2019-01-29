#ifndef HANDSTRENGTH_H
#define HANDSTRENGTH_H


#include <atomic>
#include <vector>
#include "Card.h"
#include "Hand.h"
#include "Board.h"
#include "defines.h"

using namespace std;


struct HandStrength final
{
    HandStrength(const Hand &hand, const vector<Card> &board);
    HandStrength(const HandStrength & other);
    enum class strength {HIGHT, PAIR, TWO_PAIRS, SET, STRAIT, FLASH, FULL_HOUSE, KARE, STRAIT_FLUSH 
//                         ,ROYAL_FLASH
                        };
    const strength & getCurrStrength() const;
    
private:
    strength curr_strength;
    strength checkCurrStrength(const Hand &hand, const vector<Card> &board) const;
    bool match_straitflash(const vector<Card> &combo) const;
    bool match_kare(const vector<Card> &combo) const;
    bool match_fullhouse(const vector<Card> &combo) const;
    bool match_flush(const vector<Card> &combo) const;
    bool match_strait(const vector<Card> &combo) const;
    bool match_set(const vector<Card> &combo) const;
    bool match_twopairs(const vector<Card> &combo) const;
};

struct HandStrengthList final
{
    HandStrengthList();
    std::atomic<unsigned long long> hight, pair, twopair, set, strait, flash, fullhouse, kare, straitflash;
};

vector<Card> sort_cards(const vector<Card> &combo);

#endif // HANDSTRENGTH_H