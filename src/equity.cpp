#include <iostream>
#include <thread>
#include "equity.h"
#include "handstrength.h"


//#ifdef __GNUC__
//#define UNUSED __attribute((unused))
//#else
//#define UNUSED
//#endif


//---------------------------------------------------------------------------------------------------------------------------
void genOneBoardCard(vector<Card> & board, Deck & deck, const Hand & hero_h, const Hand & opp_h,
                     unique_ptr<HandStrengthList> & hsl, const size_t & count_cycles)
{
    
    size_t tmp_count_cycles;
    deck.gen(board ,hero_h, opp_h);
    for (auto deck_el : deck.getDeckArr())
    {
        if (pushNewCardToBoard(board, hero_h, opp_h, deck_el))
        {
            if (count_cycles > 1){
                tmp_count_cycles = count_cycles - 1;
                genOneBoardCard(board, deck, hero_h, opp_h, hsl, tmp_count_cycles);
            }
            else
                sumHandStrength(hero_h, board, hsl);
            
            board.erase(board.end() - 1);
            deck.gen(board ,hero_h, opp_h);
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void parallel_genOneBoardCard(vector<Card> board, Deck deck, const Hand hero_h, const Hand opp_h, 
                              const unsigned long & min_pos, const unsigned long & max_pos,
                              unique_ptr<HandStrengthList> & hsl, const size_t count_cycles)
{
    size_t tmp_count_cycles;
    deck.gen(board ,hero_h, opp_h);
    for (unsigned long count = min_pos; count < max_pos; ++count)
    {
        if (count_cycles > 0){
            tmp_count_cycles = count_cycles - 1;
            if (pushNewCardToBoard(board, hero_h, opp_h, deck.getDeckArr().at(count)))
            {
                genOneBoardCard(board, deck, hero_h, opp_h, hsl, tmp_count_cycles);
                board.erase(board.end() - 1);
                deck.gen(board ,hero_h, opp_h);
            }
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void genPreFlop_Flop(vector<Card> & board, Deck & deck, const Hand & hero_h, const Hand & opp_h,
             unique_ptr<HandStrengthList> & hsl)
{
    size_t count_cycles = 3;

    deck.gen(board, hero_h, hero_h);
    unsigned long min_pos1 = 0;
    auto max_pos1 = deck.size() / 4;
    thread thread1(parallel_genOneBoardCard, board, deck, hero_h, opp_h, min_pos1, max_pos1, std::ref(hsl), count_cycles);
    
    auto min_pos2 = max_pos1;
    auto max_pos2 = max_pos1 * 2;
    thread thread2(parallel_genOneBoardCard, board, deck, hero_h, opp_h, min_pos2, max_pos2, std::ref(hsl), count_cycles);
    
    auto min_pos3 = max_pos2;
    auto max_pos3 = max_pos1 * 3;
    thread thread3(parallel_genOneBoardCard, board, deck, hero_h, opp_h, min_pos3, max_pos3, std::ref(hsl), count_cycles);
    
    auto min_pos4 = max_pos3;
    auto max_pos4 = deck.size();
    thread thread4(parallel_genOneBoardCard, board, deck, hero_h, opp_h, min_pos4, max_pos4, std::ref(hsl), count_cycles);

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

}
//---------------------------------------------------------------------------------------------------------------------------
void sumHandStrength(const Hand & hero_h, const vector<Card> & board, unique_ptr<HandStrengthList> & hsl)
{
    HandStrength pl_strangth{hero_h, board};
    switch (pl_strangth.getCurrStrength()) {
    case HandStrength::strength::HIGHT : ++hsl->hight; return;
    case HandStrength::strength::PAIR : ++hsl->pair; return;
    case HandStrength::strength::SET : ++hsl->set; return;
    case HandStrength::strength::TWO_PAIRS : ++hsl->twopair;return;
    case HandStrength::strength::STRAIT : ++hsl->strait;return;
    case HandStrength::strength::FLASH : ++hsl->flash;return;
    case HandStrength::strength::FULL_HOUSE : ++hsl->fullhouse;return;
    case HandStrength::strength::STRAIT_FLUSH : ++hsl->straitflash;return;
    case HandStrength::strength::KARE : ++hsl->kare;return;
    }
}