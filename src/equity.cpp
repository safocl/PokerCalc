#include <iostream>
#include <thread>
#include <equity.h>
#include "handstrength.h"


#ifdef __GNUC__
#define UNUSED __attribute((unused))
#else
#define UNUSED
#endif


//---------------------------------------------------------------------------------------------------------------------------
void genOneBoardCard(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h, std::function<void()> f_action)
{
    deck.gen(board,hero_h,opp_h);
    for (auto el : deck.getDeckArr())
    {
        if (pushNewCardToBoard(board, hero_h, opp_h, el))
        {
            f_action();
            board.erase(board.end() - 1);
            deck.gen(board ,hero_h, opp_h);
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void parallel_genOneBoardCard(vector<Card> board, Deck deck, const Hand hero_h, const Hand opp_h, 
                              const unsigned long & min_pos, const unsigned long & max_pos,
                              std::atomic<unsigned long long> & hight UNUSED, std::atomic<unsigned long long> & pair UNUSED, std::atomic<unsigned long long> & twopair UNUSED,
                              std::atomic<unsigned long long> & set UNUSED, std::atomic<unsigned long long> & strait UNUSED, std::atomic<unsigned long long> & flash UNUSED, 
                              std::atomic<unsigned long long> & fullhouse UNUSED, std::atomic<unsigned long long> & kare UNUSED, std::atomic<unsigned long long> & straitflash UNUSED,
                              std::function<void()> f_action)
{
    deck.gen(board ,hero_h, opp_h);
    for (unsigned long count = min_pos; count < max_pos; ++count)
    {
        if (pushNewCardToBoard(board, hero_h, opp_h, deck.getDeckArr().at(count)))
        {
            f_action();
            board.erase(board.end() - 1);
            deck.gen(board ,hero_h, opp_h);
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void genFlop(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h,
             std::atomic<unsigned long long> & hight, std::atomic<unsigned long long> & pair, std::atomic<unsigned long long> & twopair,
             std::atomic<unsigned long long> & set, std::atomic<unsigned long long> & strait, std::atomic<unsigned long long> & flash, 
             std::atomic<unsigned long long> & fullhouse, std::atomic<unsigned long long> & kare, std::atomic<unsigned long long> & straitflash)
{
    auto lambda_sum = [ &hero_h, board, &hight, &pair, &twopair, &set, &strait, &flash, &fullhouse, &kare, &straitflash]()
                        {sumHandStrength(hero_h, board, hight, pair, twopair, set, strait, flash, fullhouse, kare, straitflash);};
            deck.gen(board, hero_h, hero_h);
            unsigned long min_pos1 = 0;
            auto max_pos1 = deck.size() / 4;
            
            parallel_genOneBoardCard( board, deck, hero_h, opp_h, min_pos1, max_pos1,
                           ref(hight), ref(pair), ref(twopair),ref(set),ref(strait),
                           ref(flash),ref(fullhouse),ref(kare),ref(straitflash), [ &hero_h, board, &hight, &pair, &twopair, &set, &strait, &flash, &fullhouse, &kare, &straitflash]()
            {sumHandStrength(hero_h, board, hight, pair, twopair, set, strait, flash, fullhouse, kare, straitflash);});
            auto min_pos2 = max_pos1;
            auto max_pos2 = max_pos1 * 2;
            parallel_genOneBoardCard( board, deck, hero_h, opp_h, min_pos2, max_pos2,
                           ref(hight), ref(pair), ref(twopair),ref(set),ref(strait),
                           ref(flash),ref(fullhouse),ref(kare),ref(straitflash), [ &hero_h, board, &hight, &pair, &twopair, &set, &strait, &flash, &fullhouse, &kare, &straitflash]()
            {sumHandStrength(hero_h, board, hight, pair, twopair, set, strait, flash, fullhouse, kare, straitflash);});
            auto min_pos3 = max_pos2;
            auto max_pos3 = max_pos1 * 3;
            parallel_genOneBoardCard( board, deck, hero_h, opp_h, min_pos3, max_pos3,
                           ref(hight), ref(pair), ref(twopair),ref(set),ref(strait),
                           ref(flash),ref(fullhouse),ref(kare),ref(straitflash), [ &hero_h, board, &hight, &pair, &twopair, &set, &strait, &flash, &fullhouse, &kare, &straitflash]()
            {sumHandStrength(hero_h, board, hight, pair, twopair, set, strait, flash, fullhouse, kare, straitflash);});
            auto min_pos4 = max_pos3;
            auto max_pos4 = deck.size();
            parallel_genOneBoardCard( board, deck, hero_h, opp_h, min_pos4, max_pos4,
                           ref(hight), ref(pair), ref(twopair),ref(set),ref(strait),
                           ref(flash),ref(fullhouse),ref(kare),ref(straitflash), [ &hero_h, board, &hight, &pair, &twopair, &set, &strait, &flash, &fullhouse, &kare, &straitflash]()
            {sumHandStrength(hero_h, board, hight, pair, twopair, set, strait, flash, fullhouse, kare, straitflash);});

//            thread1.join();
//            thread2.join();
//            thread3.join();
//            thread4.join();

}
//---------------------------------------------------------------------------------------------------------------------------
void sumHandStrength(const Hand & hero_h, const vector<Card> & board,
                     std::atomic<unsigned long long> & hight, std::atomic<unsigned long long> & pair, std::atomic<unsigned long long> & twopair,
                     std::atomic<unsigned long long> & set, std::atomic<unsigned long long> & strait, std::atomic<unsigned long long> & flash, 
                     std::atomic<unsigned long long> & fullhouse, std::atomic<unsigned long long> & kare, std::atomic<unsigned long long> & straitflash)
{
    HandStrength pl_strangth{hero_h, board};
    switch (pl_strangth.getCurrStrength()) {
    case HandStrength::strength::HIGHT : hight.operator++(); return;
    case HandStrength::strength::PAIR : ++pair; return;
    case HandStrength::strength::SET : ++set; return;
    case HandStrength::strength::TWO_PAIRS : ++twopair;return;
    case HandStrength::strength::STRAIT : ++strait;return;
    case HandStrength::strength::FLASH : ++flash;return;
    case HandStrength::strength::FULL_HOUSE : ++fullhouse;return;
    case HandStrength::strength::STRAIT_FLASH : ++straitflash;return;
    case HandStrength::strength::KARE : ++kare;return;
    }
}