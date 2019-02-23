#include "Board.h"
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "defines.h"
#include "handstrength.h"
#include <atomic>
#include <iostream>
#include <vector>
//#include <string>
#include "equity.h"
#include <chrono>

int main() {
    //        const int hero_h1_v = 0, hero_h2_v = 0, hero_h1_s = 0, hero_h2_s = 1;
    std::unique_ptr< HandStrengthList > hsl( new HandStrengthList{} );
    //        hsl->straitFLUSH=0;hsl->kare=0;hsl->fullhouse=0;hsl->FLUSH=0;hsl->strait=0;hsl->set=0; hsl->twopair=0;
    //        hsl->pair=0; hsl->hight=0;

    //        for (int hero_h1_s = 0; (hero_h1_s < Card::suitSize); ++hero_h1_s)
    //        {
    //            for (int hero_h2_s = hero_h1_s + 1; (hero_h2_s < Card::suitSize); ++hero_h2_s)
    //            {
    //                if (hero_h1_s != hero_h2_s)
    //                {
    Hand hero{"2c", "2d"};
    //	std::unique_ptr< lp::Board > board( new lp::Board );
    //	std::unique_ptr< lp::Deck > deck( new lp::Deck );
    std::chrono::time_point start = std::chrono::steady_clock::now();
    //	board->brutforcePreFlop_Flop( *deck, hero, hero, *hsl );
    {
        ParallelGenBoard pgb{hero, hero};
        pgb.start( *hsl );
        pgb.join();
    }
    std::chrono::time_point end = std::chrono::steady_clock::now();

    //                }
    //            }
    //        }
    hsl->print();
    std::cout << "time: " << std::chrono::duration_cast< std::chrono::milliseconds >( end - start ).count() << "ms"
              << std::endl;

    return 0;
}
