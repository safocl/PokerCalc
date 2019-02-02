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
void genBoardCards(unique_ptr< vector<Card> > & board_ptr, unique_ptr<Deck> & deck_ptr, const Hand & hero_h, const Hand & opp_h,
                     unique_ptr<HandStrengthList> & hsl, const int & cycles_count)
{
    
    int tmp_cycles_count;
    deck_ptr->gen(board_ptr ,hero_h, opp_h);
    for (auto deck_el : deck_ptr->getDeckArr().operator*())
    {
        if (pushNewCardToBoard(board_ptr, hero_h, opp_h, deck_el))
        {
            if (cycles_count > 0){
                tmp_cycles_count = cycles_count - 1;
                genBoardCards(board_ptr, deck_ptr, hero_h, opp_h, hsl, tmp_cycles_count);
            }
            else
                sumHandStrength(hero_h, board_ptr, hsl);
            
            board_ptr->erase(board_ptr->end() - 1);
            deck_ptr->gen(board_ptr ,hero_h, opp_h);
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void parallel_genBoardCards(const Hand & hero_h, const Hand & opp_h, 
                              const unsigned long & min_pos, const unsigned long & max_pos,
                              unique_ptr<HandStrengthList> & hsl, const int & cycles_count)
{
    unique_ptr<Deck> deck_ptr(new Deck);
    unique_ptr< vector<Card> > board_ptr(new vector<Card>);
    board_ptr->reserve(52);
    int tmp_cycles_count;
    deck_ptr->gen(board_ptr ,hero_h, opp_h);
    for (unsigned long count = min_pos; count < max_pos; ++count)
    {
        if (cycles_count > 0){
            tmp_cycles_count = cycles_count - 2;
            if (pushNewCardToBoard(board_ptr, hero_h, opp_h, deck_ptr->getDeckArr()->at(count)))
            {
                genBoardCards(board_ptr, deck_ptr, hero_h, opp_h, hsl, tmp_cycles_count);
                board_ptr->erase(board_ptr->end() - 1);
                deck_ptr.get()->gen(board_ptr ,hero_h, opp_h);
            }
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void brutforcePreFlop_Flop(const Hand &hero_h, const Hand &opp_h,
             unique_ptr<HandStrengthList> & hsl)
{
    int cycles_count = 3;

    int max_pos;
    if (hero_h == opp_h)
        max_pos = 50;
    else
        max_pos = 48;
    
    int min_pos1 = 0;
    int max_pos1 = max_pos / 4;
    thread thread1(parallel_genBoardCards, hero_h, opp_h, min_pos1, max_pos1, std::ref(hsl), cycles_count);
    
    auto min_pos2 = max_pos1;
    auto max_pos2 = max_pos1 * 2;
    thread thread2(parallel_genBoardCards, hero_h, opp_h, min_pos2, max_pos2, std::ref(hsl), cycles_count);
    
    auto min_pos3 = max_pos2;
    auto max_pos3 = max_pos1 * 3;
    thread thread3(parallel_genBoardCards, hero_h, opp_h, min_pos3, max_pos3, std::ref(hsl), cycles_count);
    
    auto min_pos4 = max_pos3;
    auto max_pos4 = max_pos;
    thread thread4(parallel_genBoardCards, hero_h, opp_h, min_pos4, max_pos4, std::ref(hsl), cycles_count);

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

}
//---------------------------------------------------------------------------------------------------------------------------
void sumHandStrength(const Hand & hand, const unique_ptr< vector<Card> > & board_ptr, unique_ptr<HandStrengthList> & hsl)
{
    HandStrength pl_strangth{hand, board_ptr};
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