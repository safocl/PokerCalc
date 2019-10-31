//#pragma once
#ifndef BOARD_H
#define BOARD_H

namespace lp {
class ParallelGenBoard;
class Board;
struct Card;
struct Deck;
struct Hand;
class HandStrengthList;
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
    bool _isCalcTraits{false}, _isQuad{false}, _isTripple{false}, _isParied{false}, _isMonotone{false},
        _isTwoTone{false}, _isRainbow{false}, _isAllConnected{false};

  public:
    Board();
    Board( const Board & other ) = default;
    Board( Board && other ) noexcept = default;
    ~Board() = default;
    Board & operator=( const Board & other ) = default;
    Board & operator=( Board && other ) noexcept = default;
    enum class boardState : uint8_t { PREFLOP, FLOP, TURN, RIVER };
    boardState getState() const;
    const std::vector< Card > & getBoard() const;
    bool pushNewCardToBoard( const Hand & hero, const Hand & opp, const Card & card );
    bool checkCardOnBoard( const Card & card ) const;
    void calcTraits();
    bool isQuad() const;
    bool isTripple() const;
    bool isParied() const;
    bool isMonotone() const;
    bool isTwoTone() const;
    bool isRainbow() const;
    bool isAllConnected() const;

  private:
    void __isQuad();
    void __isTripple();
    void __isParied();
    void __isMonotone();
    void __isTwoTone();
    void __isRainbow();
    void __isAllConnected();
};

// class ParallelGenBoard {
//    int nCpus;
//    int8_t maxPos;
//    std::queue< std::thread > threadQueue;

//  public:
//    ParallelGenBoard( const Eval & ev );
//    ~ParallelGenBoard();
//    void start( Eval & ev );
//    void join();
//};

} // namespace lp

#endif // BOARD_H