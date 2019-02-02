#ifndef EQUITY_H
#define EQUITY_H

#include <atomic>
#include <functional>
#include <memory>
#include "Board.h"
#include "Deck.h"
#include "handstrength.h"
#include "defines.h"

void genBoardCards(unique_ptr<vector<Card>> && board, Deck & deck, const Hand & hero_h, const Hand & opp_h, 
                     unique_ptr<HandStrengthList> & hsl,const int &cycles_count);
void parallel_genBoardCards(const Hand & hero_h, const Hand & opp_h, 
                                const unsigned long & min_pos, const unsigned long & max_pos,
                                unique_ptr<HandStrengthList> & hsl, const int &cycles_count);
void brutforcePreFlop_Flop(const Hand & hero_h, const Hand & opp_h, unique_ptr<HandStrengthList> & hsl);
void sumHandStrength(const Hand & pl_h, const unique_ptr<vector<Card> > & board_ptr, unique_ptr<HandStrengthList> & hsl);

#endif // EQUITY_H
