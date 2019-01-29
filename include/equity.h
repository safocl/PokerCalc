#ifndef EQUITY_H
#define EQUITY_H


#include <atomic>
#include <functional>
#include "Board.h"
#include "Deck.h"
#include "handstrength.h"
#include "defines.h"

void genOneBoardCard(vector<Card> & board, Deck & deck, const Hand & hero_h, const Hand & opp_h, unique_ptr<HandStrengthList> & hsl,
          const size_t &count_cycles);
void parallel_genOneBoardCard(vector<Card> board, Deck deck, const Hand hero_h, const Hand opp_h, 
                   const unsigned long & min_pos, const unsigned long & max_pos,
                   unique_ptr<HandStrengthList> & hsl, const size_t &count_cycles);
void genPreFlop_Flop(vector<Card> & board, Deck & deck, const Hand & hero_h, const Hand & opp_h, unique_ptr<HandStrengthList> & hsl);
void sumHandStrength(const Hand & pl_h, const vector<Card> & board, unique_ptr<HandStrengthList> & hsl);

#endif // EQUITY_H
