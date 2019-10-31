//#pragma once
#ifndef DECK_H
#define DECK_H

namespace lp {
struct Deck;
struct Card;
class Board;
struct Hand;
} // namespace lp

//#include "Board.h"
//#include "Card.h"
//#include "Hand.h"
#include "defines.h"
#include <utility>
#include <vector>

namespace lp {

struct Deck final {
    Deck();
    //    Deck( const int minPos, const int maxPos );
    //    Deck( Deck && other );
    Deck( Deck && other ) noexcept = default;
    Deck( const Deck & other ) = delete;
    ~Deck();
    auto operator=( Deck && other ) noexcept -> Deck &;
    auto operator=( const Deck & other ) -> Deck & = delete;
    void gen( const Board & board, const Hand & hero, const Hand & opp );
    //    const int & capacity() const;
    auto size() const -> unsigned long;
    auto getDeckArr() const -> const std::vector< Card > &;
    //    int getMinPos() const;
    //    int getMaxPos() const;

  private:
    //    struct Range final {
    //        int minPos, maxPos;
    //        Range();
    //        Range( const int minPos, const int maxPos );
    //        bool isValid() const;
    //    };

    std::vector< Card > deckArr;
    static constexpr uint8_t capacity = 52;
    //    Range range;
};

} // namespace lp

#endif // DECK_H