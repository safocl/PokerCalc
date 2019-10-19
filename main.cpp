#include "Board.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "combo.h"
#include "defines.h"
#include "handstrength.h"
//#include <atomic>
#include <iostream>
#include <vector>
//#include <string>
#include "equity.h"
#include <chrono>

int main() {
    lp::Board board{};
    lp::Card card{};
    lp::Deck deck{};
    lp::Hand hero{"Kd", "Qh"};
    lp::Hand opp{"Tc", "Jd"};
    lp::Eval ev{hero, opp};
    lp::Combo combo{hero, board};
    lp::HandStrength hs{hero, board};

    std::cout << "board = " << sizeof( board ) << "\n"
              << "card = " << sizeof( card ) << "\n"
              << "deck = " << sizeof( deck ) << "\n"
              << "hand = " << sizeof( hero ) << "\n"
              << "eval = " << sizeof( ev ) << "\n"
              << "combo = " << sizeof( combo ) << "\n"
              << "hs = " << sizeof( hs )<< "\n";
    return 0;
}
