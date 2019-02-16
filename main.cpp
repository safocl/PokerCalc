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



int main()
{
//        const int hero_h1_v = 0, hero_h2_v = 0, hero_h1_s = 0, hero_h2_s = 1;
        unique_ptr<HandStrengthList> hsl(new HandStrengthList);
//        hsl->straitflash=0;hsl->kare=0;hsl->fullhouse=0;hsl->flash=0;hsl->strait=0;hsl->set=0; hsl->twopair=0; hsl->pair=0; hsl->hight=0;
        
//        for (int hero_h1_s = 0; (hero_h1_s < Card::sizeSuitCardArr); ++hero_h1_s)
//        {
//            for (int hero_h2_s = hero_h1_s + 1; (hero_h2_s < Card::sizeSuitCardArr); ++hero_h2_s) 
//            {
//                if (hero_h1_s != hero_h2_s)
//                {
        Hand hero_h{"kd","kd"};

    brutforcePreFlop_Flop(hero_h, hero_h, hsl);
//                }
//            }
//        }
        unsigned long long sum_cycle = hsl->hight+hsl->pair+hsl->set+hsl->twopair+hsl->strait+hsl->flash+hsl->fullhouse+hsl->straitflash+hsl->kare;
        
        cout << "hi : " << "\t\t\t" << hsl->hight << "\t" << static_cast<double>(hsl->hight) / sum_cycle * 100 << "%" << endl;
        cout << "pairs : " << "\t\t" << hsl->pair <<  "\t" << static_cast<double>(hsl->pair) / sum_cycle * 100 << "%" << endl;
        cout << "sets : " << "\t\t" << hsl->set <<  "\t" << static_cast<double>(hsl->set) / sum_cycle * 100 << "%" << endl;
        cout << "two pairs : " << "\t\t" << hsl->twopair <<  "\t" << static_cast<double>(hsl->twopair) / sum_cycle * 100 << "%" << endl;
        cout << "straits : " << "\t\t" << hsl->strait <<  "\t" << static_cast<double>(hsl->strait) / sum_cycle * 100 << "%" << endl;
        cout << "flashes : " << "\t\t" << hsl->flash <<  "\t" << static_cast<double>(hsl->flash) / sum_cycle * 100 << "%" << endl;
        cout << "fullhouses : " << "\t\t" << hsl->fullhouse <<  "\t" << static_cast<double>(hsl->fullhouse) / sum_cycle * 100 << "%" << endl;
        cout << "straitflashes : " << "\t" << hsl->straitflash <<  "\t" << static_cast<double>(hsl->straitflash) / sum_cycle * 100 << "%" << endl;
        cout << "kares : " << "\t\t" << hsl->kare <<  "\t" << static_cast<double>(hsl->kare) / sum_cycle * 100 << "%" << endl;
        cout << "sum_cycle : " << sum_cycle << endl;

    return 0;
}
