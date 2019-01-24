#include <iostream>
#include <thread>
#include <mutex>
#include <equity.h>
#include "handstrength.h"

//---------------------------------------------------------------------------------------------------------------------------
void genOneBoardCard(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h, std::function<void()> f_action)
{
    deck.Refrash(board,hero_h,opp_h);
    for (auto el : deck.getDeckArr())
    {
        if (pushNewCardToBoard(board, hero_h, opp_h, el))
        {
            f_action();
            board.erase(board.end() - 1);
            deck.Refrash(board ,hero_h, opp_h);
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void parallel1_genOneBoardCard(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h,
                               unsigned long long & hight, unsigned long long & pair, unsigned long long & twopair,
                               unsigned long long & set, unsigned long long & strait, unsigned long long & flash, 
                               unsigned long long & fullhouse, unsigned long long & kare, unsigned long long & straitflash)
{
    deck.Refrash(board,hero_h,opp_h);
    auto sizeArr = deck.size() / 4;

    for (size_num count = 0; count < sizeArr; ++count)
    {
        if (pushNewCardToBoard(board, hero_h, opp_h, deck.getDeckArr().at(count)))
        {

            sumHandStrength(hero_h, board, hight, pair, twopair, set, strait, flash, fullhouse, kare, straitflash);
            board.erase(board.end() - 1);
            deck.Refrash(board ,hero_h, opp_h);
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void parallel2_genOneBoardCard(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h, std::function<void()> f_action)
{
    deck.Refrash(board,hero_h,opp_h);
    auto sizeArr = deck.size() / 4;
    for (auto count = sizeArr; count < sizeArr * 2; ++count)
    {
        if (pushNewCardToBoard(board, hero_h, opp_h, deck.getDeckArr().at(count)))
        {

            f_action();
            board.erase(board.end() - 1);
            deck.Refrash(board ,hero_h, opp_h);
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void parallel3_genOneBoardCard(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h, std::function<void()> f_action)
{
    deck.Refrash(board,hero_h,opp_h);
    auto sizeArr = deck.size() / 4;

    for (auto count = sizeArr * 2; count < sizeArr * 3; ++count)
    {
        if (pushNewCardToBoard(board, hero_h, opp_h, deck.getDeckArr().at(count)))
        {

            f_action();
            board.erase(board.end() - 1);
            deck.Refrash(board ,hero_h, opp_h);
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void parallel4_genOneBoardCard(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h, std::function<void()> f_action)
{
    deck.Refrash(board,hero_h,opp_h);
    auto sizeArr = deck.size() / 4;

    for (auto count = sizeArr * 3; count < deck.size(); ++count)
    {
        if (pushNewCardToBoard(board, hero_h, opp_h, deck.getDeckArr().at(count)))
        {

            f_action();
            board.erase(board.end() - 1);
            deck.Refrash(board ,hero_h, opp_h);
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------------
void genFlop(vector<Card> & board, Deck & deck, const Hand hero_h, const Hand opp_h, std::function<void()> f_action)
{
    genOneBoardCard(board, deck, hero_h, opp_h, [&](){
        genOneBoardCard(board, deck, hero_h, opp_h, [&](){
            genOneBoardCard(board, deck, hero_h, opp_h, [&](){
                f_action();
            });
        });
    });
}
//---------------------------------------------------------------------------------------------------------------------------
void sumHandStrength(const Hand & pl_h, const vector<Card> & board,
                     unsigned long long & hight, unsigned long long & pair, unsigned long long & twopair,
                     unsigned long long & set, unsigned long long & strait, unsigned long long & flash, 
                     unsigned long long & fullhouse, unsigned long long & kare, unsigned long long & straitflash)
{
    HandStrength pl_strangth{pl_h, board};
    switch (pl_strangth.getCurrStrength()) {
    case HandStrength::strength::HIGHT : ++hight; break;
    case HandStrength::strength::PAIR : ++pair; break;
    case HandStrength::strength::SET : ++set; break;
    case HandStrength::strength::TWO_PAIRS : ++twopair; break;
    case HandStrength::strength::STRAIT : ++strait; break;
    case HandStrength::strength::FLASH : ++flash; break;
    case HandStrength::strength::FULL_HOUSE : ++fullhouse; break;
    case HandStrength::strength::STRAIT_FLASH : ++straitflash; break;
    case HandStrength::strength::KARE : ++kare; break;
    }
}