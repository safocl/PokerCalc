//#pragma once
#ifndef CARD_H
#define CARD_H

//namespace lp {
struct Card;
//} // namespace lp


#include "defines.h"
#include <cstdint>
#include <string>
#include <utility>

// using namespace std;
//namespace lp {

struct Card final {
    enum class valCard : uint32_t;
    enum class suitCard : uint8_t;

    Card();
    Card( const std::string strCard );
    Card( Card::valCard && numValueCard, Card::suitCard && numSuitCard );
    Card( const Card & other );
    Card( Card && other );
    ~Card();

    /**
     * @brief The valCard enum
     * this is the bitmask of the card values in the range from 0b0000000000001000000000000000 to
     * 0b100000000000000000000000000 0b111111111111100000000000000
     */
    enum class valCard : std::uint32_t {
        NODEF = 0,
        _2 = 0x10000,   // 0b1000000000000000
        _3 = 0x20000,   // 0b10000000000000000
        _4 = 0x40000,   // 0b100000000000000000
        _5 = 0x80000,   // 0b1000000000000000000
        _6 = 0x100000,  // 0b10000000000000000000
        _7 = 0x200000,  // 0b100000000000000000000
        _8 = 0x400000,  // 0b1000000000000000000000
        _9 = 0x800000,  // 0b10000000000000000000000
        _T = 0x1000000, // 0b100000000000000000000000
        _J = 0x2000000, // 0b1000000000000000000000000
        _Q = 0x4000000, // 0b10000000000000000000000000
        _K = 0x8000000, // 0b100000000000000000000000000
        _A = 0x10000000
    }; // 0b100000000000000000000000000
    /**
     * @brief The suitCard enum
     * this is the bitmask of the card values in the range from 0b0000000000000000000000000001 to
     * 0b000000000000000000000001000 0b000000000000000000000001111  <::> _d = 0x1 | _s = 0x2 | _c = 0x4 | _h = 0x8 |
     */
    enum class suitCard : uint8_t {
        NODEF = 0,
        _d_0x1 = 0x1, // 0b1
        _s_0x2 = 0x2, // 0b10
        _c_0x4 = 0x4, // 0b100
        _h_0x8 = 0x8
    }; // 0b1000

    void setCard( const std::string strCard );
    void setCard( const Card & card );
    void setCard( const valCard & value, const suitCard & suit );
    std::string get_string() const noexcept;
    uint8_t getSuitNum() const noexcept;
    uint32_t getValueNum() const noexcept;

    /**
     * @brief inc_val
     * @return
     * increment card value
     */
    Card inc_val() noexcept;

    /**
     * @brief inc_suit
     * @return
     * increment card suit
     */
    Card inc_suit() noexcept;

    /**
     * @brief dec_val
     * @return
     * decrement card value
     */
    Card dec_val() noexcept;

    /**
     * @brief dec_suit
     * @return
     * decrement card suit
     */
    Card dec_suit() noexcept;
    void setSuitNum( const suitCard & suit );
    void setValueNum( const valCard & value );
    bool operator==( const Card & other ) const noexcept;
    bool operator!=( const Card & other ) const noexcept;
    Card & operator=( const Card & other ) noexcept;
    Card & operator=( Card && other ) noexcept;
    bool operator<( const Card & other ) const noexcept;
    bool operator>( const Card & other ) const noexcept;

    /**
     * @brief suit_mask
     * = 0x1f or 0b11111
     */
    static const uint8_t suit_mask = 0x1f;

    /**
     * @brief value_mask
     * = 0x3fff0000 or 0b00111111111111110000000000000000
     */
    static const uint32_t value_mask = 0x3fff0000;

    static const uint32_t sizeValueCardArr = 0x20000000;
    static const uint8_t sizeSuitCardArr = 0x10;

  private:
    uint32_t numCard;

    std::string && getSuit() const noexcept;
    std::string getValue() const noexcept;
    bool check_valid_value( const valCard & value );
    bool check_valid_suit( const suitCard & suit );
};

//} // namespace lp
#endif