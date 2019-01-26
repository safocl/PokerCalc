#ifndef EQUITY_H
#define EQUITY_H

#include <atomic>
#include <functional>
#include "Board.h"
#include "Deck.h"
#include "handstrength.h"

void genOneBoardCard(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h, HandStrengthList & hsl,
                     size_num & count_cycles);
void parallel_genOneBoardCard(vector<Card> board, Deck deck, const Hand hero_h, const Hand opp_h, 
                              const unsigned long & min_pos, const unsigned long & max_pos,
                              HandStrengthList & hsl, size_num & count_cycles);
void genFlop(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h, HandStrengthList & hsl);
void sumHandStrength(const Hand & pl_h, const vector<Card> & board, HandStrengthList & hsl);

#endif // EQUITY_H
