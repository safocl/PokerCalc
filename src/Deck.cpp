#include "Deck.h"
#include "Board.h"

//---------------------------------------------------------------------------------------------------------------------------
const vector<Card> & Deck::getDeckArr() const {return deckArr;}
//---------------------------------------------------------------------------------------------------------------------------
unsigned long Deck::size() const {return deckArr.size();}
//---------------------------------------------------------------------------------------------------------------------------
const size_num & Deck::capacity() const {return SIZE_DeckArr;}
//---------------------------------------------------------------------------------------------------------------------------
void Deck::Refrash(const vector<Card> &board, const Hand &heroHand, const Hand &oppHand)
{
    deckArr.reserve(SIZE_DeckArr);
    
    if (!deckArr.empty())
        deckArr.clear();
    
    Card card;
    
    for (size_num numValueCard = 0; numValueCard < Card::sizeValueCardArr; ++numValueCard)
    {
        for (size_num numSuitCard = 0; numSuitCard < Card::sizeSuitCardArr; ++numSuitCard)
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