#ifndef EQUITY_H
#define EQUITY_H


#include <functional>
#include "Board.h"
#include "Deck.h"


void genOneBoardCard(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h, std::function<void()> f_action);
void parallel_genOneBoardCard(vector<Card> board, Deck deck, const Hand hero_h, const Hand opp_h, 
                               const unsigned long & min_pos, const unsigned long & max_pos,
                                unsigned long long & hight, unsigned long long & pair, unsigned long long & twopair,
                                unsigned long long & set, unsigned long long & strait, unsigned long long & flash, 
                                unsigned long long & fullhouse, unsigned long long & kare, unsigned long long & straitflash);
void genFlop(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h, unsigned long long &hight, unsigned long long &pair, unsigned long long &twopair, unsigned long long &set, unsigned long long &strait, unsigned long long &flash, unsigned long long &fullhouse, unsigned long long &kare, unsigned long long &straitflash);
void sumHandStrength(const Hand & pl_h, const vector<Card> & board,
                     unsigned long long &hight, unsigned long long &pair, unsigned long long &twopair,
                     unsigned long long &set, unsigned long long &strait, unsigned long long &flash, 
                     unsigned long long &fullhouse, unsigned long long &kare, unsigned long long &straitflash);

#endif // EQUITY_H
