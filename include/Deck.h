#pragma once


#include <vector>
#include "Card.h"
#include "Hand.h"
#include "Board.h"
#include "defines.h"

using namespace std;


class Deck
{
public:
    Deck();
    ~Deck();

    static void Refrash(vector<Card> &board, const Hand &heroHand, const Hand &oppHand);

    static void DeckPrint();
    
    static size_num capacity();
    
    static const vector<Card> & getDeckArr();

private:
    static vector<Card> deckArr;
    static const size_num SIZE_DeckArr = 52;
};
