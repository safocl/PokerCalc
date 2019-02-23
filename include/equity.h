//#pragma once
#ifndef EQUITY_H
#define EQUITY_H

struct Hand;
struct HandStrengthList;
class Board;


#include <atomic>
#include <functional>
#include <memory>

//namespace lp {

// void bruteForceCards(unique_ptr<vector<Card>> && board, Deck & deck, const Hand & hero_h, const Hand & opp_h,
//                     unique_ptr<HandStrengthList> & hsl,const int &cycles_count);
// void bruteForceFirstCard(const Hand & hero_h, const Hand & opp_h,
//                                const unsigned long & min_pos, const unsigned long & max_pos,
//                                unique_ptr<HandStrengthList> & hsl, const int &cycles_count);
// void brutforcePreFlop_Flop(const Hand & hero_h, const Hand & opp_h, unique_ptr<HandStrengthList> & hsl);
//void sumHandStrength( const Hand & hand, const Board & board, HandStrengthList & hsl );

//} // namespace lp

#endif // EQUITY_H
