//#pragma once
#ifndef BOARD_H
#define BOARD_H

namespace lp {

class Board;
// struct Deck;
struct HandStrengthList;
} // namespace lp

#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "defines.h"
#include "handstrength.h"
#include <functional>
#include <queue>
#include <thread>
#include <vector>

namespace lp {

class Board {
    static constexpr uint8_t MAX_SIZE = 5;
    std::unique_ptr< std::vector< Card > > board_ptr;

  public:
    Board();
    const std::vector< Card > & getVector() const;
    bool pushNewCardToBoard( const Hand & hero, const Hand & opp, const Card & card ) const;
    bool checkCardOnBoard( const Card & card ) const;
    void brutforcePreFlop_Flop( Deck & deck, const Hand & hero, const Hand & opp, HandStrengthList & hsl );

  private:
    void genBoardCards( Deck & deck, const Hand & hero, const Hand & opp, HandStrengthList & hsl,
                        const int & cycles_count );
    void parallel_genBoardCards( Deck & deck, const Hand & hero, const Hand & opp, HandStrengthList & hsl,
                                 const int & cycles_count );
};

class ParallelGenBoard {
    int nCpus;
    int8_t maxPos;
    std::unique_ptr< Hand > hero, opp;
    std::unique_ptr< std::queue< std::thread > > threadQueue;

  public:
    ParallelGenBoard( const Hand & hero, const Hand & opp );
    ~ParallelGenBoard();
    void start( HandStrengthList & hsl );
    void join();
};

} // namespace lp

#endif // BOARD_H