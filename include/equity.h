#ifndef EQUITY_H
#define EQUITY_H

#include <atomic>
#include <functional>
#include "Board.h"
#include "Deck.h"
#include "handstrength.h"

void genOneBoardCard(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h, unique_ptr<HandStrengthList> & hsl,
                     unsigned short & count_cycles);
void parallel_genOneBoardCard(vector<Card> board, Deck deck, const Hand hero_h, const Hand opp_h, 
                              const unsigned long & min_pos, const unsigned long & max_pos,
                              unique_ptr<HandStrengthList> & hsl, unsigned short count_cycles);
void genFlop(vector<Card> & board, Deck & deck, const Hand & hero_h, const Hand & opp_h, unique_ptr<HandStrengthList> & hsl);
void sumHandStrength(const Hand & pl_h, const vector<Card> & board, unique_ptr<HandStrengthList> & hsl);

#endif // EQUITY_H
