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
    {
        std::unique_ptr< lp::HandStrengthList > hslHero( new lp::HandStrengthList{} );
        std::unique_ptr< lp::HandStrengthList > hslOpp( new lp::HandStrengthList{} );

        lp::Hand hero{"2c", "2d"};
        lp::Hand opp{"4c", "4s"};

        //        std::unique_ptr< lp::Board > board( new lp::Board );
        //        std::unique_ptr< lp::Deck > deck( new lp::Deck );
        std::chrono::time_point start = std::chrono::steady_clock::now();
        //        board->brutforcePreFlop_Flop( *deck, hero, hero, *hslHero, *hslOpp );

        lp::ParallelGenBoard pgb{hero, opp};
        pgb.start( *hslHero, *hslOpp );
        pgb.join();

        std::chrono::time_point end = std::chrono::steady_clock::now();

        //                }
        //            }
        //        }
        //        hsl->print();
        lp::Eval ev1{};
        hslHero->calcPercents();
        hslOpp->calcPercents();
        ev1.calc();
        ev1.print();
        std::cout << "time: " << std::chrono::duration_cast< std::chrono::milliseconds >( end - start ).count() << "ms"
                  << std::endl;
    }
    return 0;
}
