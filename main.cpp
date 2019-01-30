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
        Deck deck;
        const int hero_h1_v = 0, hero_h2_v = 0, hero_h1_s = 0, hero_h2_s = 1;
        std::vector<Card> board;
        board.reserve(5);
        
        unique_ptr<HandStrengthList> hsl(new HandStrengthList);
//        hsl->straitflash=0;hsl->kare=0;hsl->fullhouse=0;hsl->flash=0;hsl->strait=0;hsl->set=0; hsl->twopair=0; hsl->pair=0; hsl->hight=0;
        
//        for (int hero_h1_s = 0; (hero_h1_s < Card::sizeSuitCardArr); ++hero_h1_s)
//        {
//            for (int hero_h2_s = hero_h1_s + 1; (hero_h2_s < Card::sizeSuitCardArr); ++hero_h2_s) 
//            {
//                if (hero_h1_s != hero_h2_s)
//                {
    Hand hero_h{hero_h1_v, hero_h1_s, hero_h2_v, hero_h2_s};

    genPreFlop_Flop(move(board), move(deck), move(hero_h), move(hero_h), hsl);
//                }
//            }
//        }
        unsigned long long sum_cycle = hsl->hight+hsl->pair+hsl->set+hsl->twopair+hsl->strait+hsl->flash+hsl->fullhouse+hsl->straitflash+hsl->kare;
        
        cout << "hi : " << hsl->hight << endl;
        cout << "pairs : " << hsl->pair << endl;
        cout << "sets : " << hsl->set << endl;
        cout << "two pairs : " << hsl->twopair << endl;
        cout << "straits : " << hsl->strait << endl;
        cout << "flashes : " << hsl->flash << endl;
        cout << "fullhouses : " << hsl->fullhouse << endl;
        cout << "straitflashes : " << hsl->straitflash << endl;
        cout << "kares : " << hsl->kare << endl;
        cout << "sum_cycle : " << sum_cycle << endl;

    return 0;
}
