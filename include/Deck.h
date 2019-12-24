
//#ifndef DECK_H
//#define DECK_H

namespace lp {
struct Card;
struct Deck;
class Board;
class Combo;
struct EV;
class Eval;
struct Hand;
class HandStrength;
} // namespace lp

#pragma once

#include "Board.h"
#include "Card.h"
#include "Hand.h"
#include "defines.h"
#include <utility>
#include <vector>

namespace lp {

struct Deck final {
    Deck() = delete;
    Deck( const Board & board, const Hand & hero, const Hand & opp );
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
    //    auto howHighterCards( const lp::Card & matchingCard ) const -> uint8_t;

    template < Board::boardState S > constexpr static int8_t getNumRemainedCards() {
        if constexpr ( S == Board::boardState::PREFLOP )
            return 48;
        else if constexpr ( S == Board::boardState::FLOP )
            return 45;
        else if constexpr ( S == Board::boardState::TURN )
            return 44;
        else if constexpr ( S == Board::boardState::RIVER )
            return 43;
    }
    // template <> constexpr int8_t getNumRemainedCards< Board::boardState::PREFLOP >() { return 48; }
    // template <> constexpr int8_t getNumRemainedCards< Board::boardState::FLOP >() { return 45; }
    // template <> constexpr int8_t getNumRemainedCards< Board::boardState::TURN >() { return 44; }
    // template <> constexpr int8_t getNumRemainedCards< Board::boardState::RIVER >() { return 43; }

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

//#endif // DECK_H
