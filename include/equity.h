#ifndef EQUITY_H
#define EQUITY_H

#include <atomic>
#include <functional>
#include "Board.h"
#include "Deck.h"

void genOneBoardCard(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h, std::function<void()> f_action);
void parallel_genOneBoardCard(vector<Card> board, Deck deck, const Hand hero_h, const Hand opp_h, 
                              const unsigned long & min_pos, const unsigned long & max_pos,
                               std::atomic<unsigned long long> & hight, std::atomic<unsigned long long> & pair , std::atomic<unsigned long long> & twopair ,
                               std::atomic<unsigned long long> & set, std::atomic<unsigned long long> & strait , std::atomic<unsigned long long> & flash , 
                               std::atomic<unsigned long long> & fullhouse , std::atomic<unsigned long long> & kare , std::atomic<unsigned long long> & straitflash ,
                              std::function<void()> f_action);
void genFlop(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h,
             std::atomic<unsigned long long> & hight, std::atomic<unsigned long long> & pair, std::atomic<unsigned long long> & twopair,
             std::atomic<unsigned long long> & set, std::atomic<unsigned long long> & strait, std::atomic<unsigned long long> & flash, 
             std::atomic<unsigned long long> & fullhouse, std::atomic<unsigned long long> & kare, std::atomic<unsigned long long> & straitflash);
void sumHandStrength(const Hand & pl_h, const vector<Card> & board,
                     std::atomic<unsigned long long> & hight, std::atomic<unsigned long long> & pair, std::atomic<unsigned long long> & twopair,
                     std::atomic<unsigned long long> & set, std::atomic<unsigned long long> & strait, std::atomic<unsigned long long> & flash, 
                     std::atomic<unsigned long long> & fullhouse, std::atomic<unsigned long long> & kare, std::atomic<unsigned long long> & straitflash);

#endif // EQUITY_H
