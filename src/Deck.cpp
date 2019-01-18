#include "Deck.h"

Deck::Deck()
{
    //ctor
}

Deck::~Deck()
{
    //dtor
}

const vector<Card> & Deck::getDeckArr(){return deckArr;}

size_num Deck::capacity(){return SIZE_DeckArr;}

void Deck::Refrash(vector<Card> &board, const Hand &heroHand, const Hand &oppHand)
{
    Deck::deckArr.reserve(SIZE_DeckArr);
    
    if (!deckArr.empty())
        deckArr.clear();
    
    Card card;

    for (size_num numValueCard = 0; numValueCard < Card::sizeValueCardArr; numValueCard++)
    {
        for (size_num numSuitCard = 0; numSuitCard < Card::sizeSuitCardArr; numSuitCard++)
        {
            card.SetCard(numValueCard, numSuitCard);
            
           if (card != heroHand.getCard1() && 
                card != heroHand.getCard2() && 
                card != oppHand.getCard1() && 
                card != oppHand.getCard2() &&
                !brute_force_matching_cards(board, card))
            {
                deckArr.push_back(card);
            }
        }
    }
}

//void Deck::DeckPrint()
//{
//    for (auto el : deckArr)
//    {
//        cout << el.GetValueCard() << el.GetSuitCard() << endl;
//    }
//}

//Card & Deck::GetCard(const size_num indexCard)
//{
//
//}


vector<Card> Deck::deckArr = {};

