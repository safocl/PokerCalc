#include <atomic>
#include <iostream>
#include <vector>
#include "Card.h"
#include "Hand.h"
#include "Board.h"
#include "Deck.h"
#include "handstrength.h"
#include "defines.h"
//#include <string>
#include "equity.h"
#include <chrono>



int main()
{
//        const int hero_h1_v = 0, hero_h2_v = 0, hero_h1_s = 0, hero_h2_s = 1;
        std::unique_ptr< lp::HandStrengthList > hsl( new lp::HandStrengthList );
//        hsl->straitFLUSH=0;hsl->kare=0;hsl->fullhouse=0;hsl->FLUSH=0;hsl->strait=0;hsl->set=0; hsl->twopair=0; hsl->pair=0; hsl->hight=0;
        
//        for (int hero_h1_s = 0; (hero_h1_s < Card::sizeSuitCardArr); ++hero_h1_s)
//        {
//            for (int hero_h2_s = hero_h1_s + 1; (hero_h2_s < Card::sizeSuitCardArr); ++hero_h2_s) 
//            {
//                if (hero_h1_s != hero_h2_s)
//                {
        lp::Hand hero{"2c","2d"};
		std::unique_ptr< lp::Board > board( new lp::Board );
		std::unique_ptr< lp::Deck > deck( new lp::Deck );
	std::chrono::time_point start = std::chrono::steady_clock::now();
	board->brutforcePreFlop_Flop( *deck, hero, hero, *hsl );
	std::chrono::time_point end = std::chrono::steady_clock::now();
	
//                }
//            }
//        }
        unsigned long long sum_cycle = hsl->hight+hsl->pair+hsl->set+hsl->twopair+hsl->strait+hsl->FLUSH+hsl->fullhouse+hsl->straitFLUSH+hsl->kare;
        
        std::cout << "hi : " << "\t\t\t" << hsl->hight << "\t" << static_cast<double>(hsl->hight) / sum_cycle * 100 << "%" << std::endl;
        std::cout << "pairs : " << "\t\t" << hsl->pair <<  "\t" << static_cast<double>(hsl->pair) / sum_cycle * 100 << "%" << std::endl;
        std::cout << "sets : " << "\t\t" << hsl->set <<  "\t" << static_cast<double>(hsl->set) / sum_cycle * 100 << "%" << std::endl;
        std::cout << "two pairs : " << "\t\t" << hsl->twopair <<  "\t" << static_cast<double>(hsl->twopair) / sum_cycle * 100 << "%" << std::endl;
        std::cout << "straits : " << "\t\t" << hsl->strait <<  "\t" << static_cast<double>(hsl->strait) / sum_cycle * 100 << "%" << std::endl;
        std::cout << "FLUSHes : " << "\t\t" << hsl->FLUSH <<  "\t" << static_cast<double>(hsl->FLUSH) / sum_cycle * 100 << "%" << std::endl;
        std::cout << "fullhouses : " << "\t\t" << hsl->fullhouse <<  "\t" << static_cast<double>(hsl->fullhouse) / sum_cycle * 100 << "%" << std::endl;
        std::cout << "straitFLUSHes : " << "\t" << hsl->straitFLUSH <<  "\t" << static_cast<double>(hsl->straitFLUSH) / sum_cycle * 100 << "%" << std::endl;
        std::cout << "kares : " << "\t\t" << hsl->kare <<  "\t" << static_cast<double>(hsl->kare) / sum_cycle * 100 << "%" << std::endl;
        std::cout << "sum_cycle : " << sum_cycle << std::endl;
		std::cout << "time: " << std::chrono::duration_cast<std::chrono::milliseconds >( end - start ).count() << "ms" << std::endl;

    return 0;
}
