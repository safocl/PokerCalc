//#pragma once
#ifndef BOARD_H
#define BOARD_H

namespace lp {
class ParallelGenBoard;
class Board;
struct Card;
struct Deck;
struct Hand;
struct HandStrengthList;
class Eval;

} // namespace lp

#include "Hand.h"
#include "defines.h"
#include "equity.h"
#include <queue>
#include <thread>
#include <vector>

namespace lp {

class Board {
    static constexpr uint8_t MAX_SIZE = 5;
    std::vector< Card > board;

  public:
    Board();
    Board( const Board & other );
    const std::vector< Card > & getBoard() const;
    bool pushNewCardToBoard( const Hand & hero, const Hand & opp, const Card & card );
    bool checkCardOnBoard( const Card & card ) const;
    void brutforcePreFlop_Flop( Deck & deck, Eval & ev );

  private:
    void bruteForceCards( Deck & deck, Eval ev, const unsigned int & cyclesCount );
    template < unsigned int cyclesCount > void bruteForceCardsMT( Deck & deck, Eval & ev );
};

class ParallelGenBoard {
    int nCpus;
    int8_t maxPos;
    std::queue< std::thread > threadQueue;

  public:
    ParallelGenBoard( const Eval & ev );
    ~ParallelGenBoard();
    void start( Eval & ev );
    void join();
};

} // namespace lp

#endif // BOARD_H