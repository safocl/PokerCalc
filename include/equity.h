#ifndef EQUITY_H
#define EQUITY_H


#include <functional>
#include "Board.h"
#include "Deck.h"


void genOneBoardCard(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h, std::function<void()> f_action);
void parallel1_genOneBoardCard(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h,
                               unsigned long long & hight, unsigned long long & pair, unsigned long long & twopair,
                               unsigned long long & set, unsigned long long & strait, unsigned long long & flash, 
                               unsigned long long & fullhouse, unsigned long long & kare, unsigned long long & straitflash);
void parallel2_genOneBoardCard(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h, std::function<void()> f_action);
void parallel3_genOneBoardCard(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h, std::function<void()> f_action);
void parallel4_genOneBoardCard(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h, std::function<void()> f_action);
void genFlop(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h, std::function<void()> f_action);
void sumHandStrength(const Hand & pl_h, const vector<Card> & board,
                     unsigned long long &hight, unsigned long long &pair, unsigned long long &twopair,
                     unsigned long long &set, unsigned long long &strait, unsigned long long &flash, 
                     unsigned long long &fullhouse, unsigned long long &kare, unsigned long long &straitflash);

#endif // EQUITY_H
