#include <iostream>
#include <vector>
#include "Card.h"
#include "Hand.h"
#include "Board.h"
#include "Deck.h"
#include "handstrength.h"
#include <string>
#include "equity.h"
#include <thread>


int main()
{

    try
    {
        Deck deck;
        const size_num hero_h1_v = 0, hero_h2_v = 0, hero_h1_s = 0, hero_h2_s = 1;
        vector<Card> board;
        board.reserve(5);
        
        unsigned long long sum_cycle = 0, straitflash = 0, kare = 0, fullhouse = 0, flash = 0, strait = 0, set = 0, twopair = 0, pair = 0, hight = 0;
        
//        for (size_num hero_h1_s = 0; (hero_h1_s < Card::sizeSuitCardArr); ++hero_h1_s)
//        {
//            for (size_num hero_h2_s = hero_h1_s + 1; (hero_h2_s < Card::sizeSuitCardArr); ++hero_h2_s) 
//            {
//                if (hero_h1_s != hero_h2_s)
//                {
    Hand hero_h{hero_h1_v, hero_h1_s, hero_h2_v, hero_h2_s};
//    thread thread1(parallel1_genOneBoardCard, board, deck, hero_h, hero_h, 
//                   ref(hight), ref(pair), ref(twopair),ref(set),ref(strait),
//                   ref(flash),ref(fullhouse),ref(kare),ref(straitflash));
//    thread thread2(parallel2_genOneBoardCard, board, deck, hero_h, hero_h, 
//                   ref(hight), ref(pair), ref(twopair),ref(set),ref(strait),
//                   ref(flash),ref(fullhouse),ref(kare),ref(straitflash));
//    thread thread3(parallel3_genOneBoardCard, board, deck, hero_h, hero_h, 
//                   ref(hight), ref(pair), ref(twopair),ref(set),ref(strait),
//                   ref(flash),ref(fullhouse),ref(kare),ref(straitflash));
//    thread thread4(parallel4_genOneBoardCard, board, deck, hero_h, hero_h, 
//                   ref(hight), ref(pair), ref(twopair),ref(set),ref(strait),
//                   ref(flash),ref(fullhouse),ref(kare),ref(straitflash));
//    thread1.join();
//    thread2.join();
//    thread3.join();
//    thread4.join();
    
    
    genFlop(board, deck, hero_h, hero_h, 
            hight, pair, twopair,set,strait,
            flash,fullhouse,kare,straitflash);
    
//    parallel1_genOneBoardCard( board, deck, hero_h, hero_h, 
//                               ref(hight), ref(pair), ref(twopair),ref(set),ref(strait),
//                               ref(flash),ref(fullhouse),ref(kare),ref(straitflash));
//    parallel2_genOneBoardCard( board, deck, hero_h, hero_h, 
//                               ref(hight), ref(pair), ref(twopair),ref(set),ref(strait),
//                               ref(flash),ref(fullhouse),ref(kare),ref(straitflash));
//    parallel3_genOneBoardCard( board, deck, hero_h, hero_h, 
//                               ref(hight), ref(pair), ref(twopair),ref(set),ref(strait),
//                               ref(flash),ref(fullhouse),ref(kare),ref(straitflash));
//    parallel4_genOneBoardCard( board, deck, hero_h, hero_h, 
//                               ref(hight), ref(pair), ref(twopair),ref(set),ref(strait),
//                               ref(flash),ref(fullhouse),ref(kare),ref(straitflash));
//    thread thread1(parallel1_genOneBoardCard, board, deck, hero_h, hero_h, 
//                   ref(hight), ref(pair), ref(twopair),ref(set),ref(strait),
//                   ref(flash),ref(fullhouse),ref(kare),ref(straitflash));
//    thread thread2(parallel2_genOneBoardCard, board, deck, hero_h, hero_h, 
//                   ref(hight), ref(pair), ref(twopair),ref(set),ref(strait),
//                   ref(flash),ref(fullhouse),ref(kare),ref(straitflash));
//    thread thread3(parallel3_genOneBoardCard, board, deck, hero_h, hero_h, 
//                   ref(hight), ref(pair), ref(twopair),ref(set),ref(strait),
//                   ref(flash),ref(fullhouse),ref(kare),ref(straitflash));
//    thread thread4(parallel4_genOneBoardCard, board, deck, hero_h, hero_h, 
//                   ref(hight), ref(pair), ref(twopair),ref(set),ref(strait),
//                   ref(flash),ref(fullhouse),ref(kare),ref(straitflash));
    
//    thread thread1(parallel1_genOneBoardCard, board, deck, hero_h, hero_h, 
//                   hight,pair, twopair,set,strait,
//                   flash,fullhouse,kare,straitflash);
    
//    thread1.join();
//    thread2.join();
//    thread3.join();
//    thread4.join();

//                }
//            }
//        }
        cout << "sum_cycle : " << sum_cycle << endl;
        cout << "hi : " << hight << endl;
        cout << "pairs : " << pair << endl;
        cout << "sets : " << set << endl;
        cout << "two pairs : " << twopair << endl;
        cout << "straits : " << strait << endl;
        cout << "flashes : " << flash << endl;
        cout << "fullhouses : " << fullhouse << endl;
        cout << "straitflashes : " << straitflash << endl;
        cout << "kares : " << kare << endl;
    }
    catch (const exception & __exc){cout << __exc.what() << endl;}
    catch (const char *str){cout << str << endl;}
    


    return 0;
}
