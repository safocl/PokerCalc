#ifndef EQUITY_H
#define EQUITY_H

#include <QVector>
#include <atomic>
#include <functional>
#include "Board.h"
#include "Deck.h"
#include "handstrength.h"
#include "defines.h"

void genOneBoardCard(QVector<Card> & board, Deck & deck, const Hand & hero_h, const Hand & opp_h, unique_ptr<HandStrengthList> & hsl,
          const int &count_cycles);
void parallel_genOneBoardCard(QVector<Card> board, Deck deck, const Hand hero_h, const Hand opp_h, 
                   const int &min_pos, const int &max_pos,
                   unique_ptr<HandStrengthList> & hsl, const int &count_cycles);
void genPreFlop_Flop(QVector<Card> & board, Deck & deck, const Hand & hero_h, const Hand & opp_h, unique_ptr<HandStrengthList> & hsl);
void sumHandStrength(const Hand & pl_h, const QVector<Card> & board, unique_ptr<HandStrengthList> & hsl);

#endif // EQUITY_H
