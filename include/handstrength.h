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
    HandStrength(const Hand &hand, const unique_ptr<vector<Card> > & board_ptr);
    HandStrength(const HandStrength & other);
    enum class strength {HIGHT, PAIR, TWO_PAIRS, SET, STRAIT, FLASH, FULL_HOUSE, KARE, STRAIT_FLUSH 
//                         ,ROYAL_FLASH
                        };
    const strength & getCurrStrength() const;
    
private:
    strength curr_strength;
    strength checkCurrStrength(const Hand &hand, const unique_ptr<vector<Card> > & board_ptr) const;
    bool match_straitflash(const unique_ptr<vector<Card> > & combo_ptr, const uint32_t & combo) const;
    bool match_kare(const unique_ptr<vector<Card> > & combo_ptr) const;
    bool match_fullhouse(const unique_ptr<vector<Card> > & combo_ptr) const;
    bool match_flush(const unique_ptr<vector<Card> > & combo_ptr, const uint32_t & combo) const;
    bool match_strait(const uint32_t & combo) const;
    bool match_set(const unique_ptr<vector<Card> > & combo_ptr) const;
    bool match_twopairs(const unique_ptr<vector<Card> > & combo_ptr) const;
};

struct HandStrengthList final
{
    HandStrengthList();
    std::atomic<unsigned long long> hight, pair, twopair, set, strait, flash, fullhouse, kare, straitflash;
};

unique_ptr<vector<Card> > sort_cards(const unique_ptr<vector<Card> > & combo_ptr);

#endif // HANDSTRENGTH_H