#include "Deck.h"
#include "Board.h"

Deck::Deck() : deckArr(new QVector<Card>) {deckArr->reserve(Deck::SIZE_DeckArr);}
//---------------------------------------------------------------------------------------------------------------------------
//Deck::Deck(const Deck & other){this->deckArr = other.deckArr;}
//---------------------------------------------------------------------------------------------------------------------------
Deck::Deck(Deck && other){*this = std::move(other);}
//---------------------------------------------------------------------------------------------------------------------------
Deck & Deck::operator = (Deck && other){this->deckArr = std::move(other.deckArr);
                                        return *this;}
//---------------------------------------------------------------------------------------------------------------------------
const unique_ptr< QVector<Card> > & Deck::getDeckArr() const {return deckArr;}
//---------------------------------------------------------------------------------------------------------------------------
int Deck::size() const {return deckArr->size();}
//---------------------------------------------------------------------------------------------------------------------------
//const int & Deck::capacity() const {return Deck::SIZE_DeckArr;}
//---------------------------------------------------------------------------------------------------------------------------
void Deck::gen(const unique_ptr< QVector<Card> > & board_ptr, const Hand &heroHand, const Hand &oppHand)
{
//    deckArr.reserve(Deck::SIZE_DeckArr);
    
    if (!deckArr->empty())
        deckArr->clear();
    
    Card card;
    
    for (int numValueCard = 0; numValueCard < Card::sizeValueCardArr; ++numValueCard)
    {
        for (int numSuitCard = 0; numSuitCard < Card::sizeSuitCardArr; ++numSuitCard)
        {
           card.SetCard(numValueCard, numSuitCard);
           
           if (card != heroHand.getCard1() && 
                card != heroHand.getCard2() && 
                card != oppHand.getCard1() && 
                card != oppHand.getCard2() &&
                !brute_force_matching_cards(board_ptr, card))
            {
                deckArr->push_back(card);
            }
        }
    }
}