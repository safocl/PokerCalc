#include "Deck.h"
#include "Board.h"


Deck::Deck() : deckArr() {deckArr.reserve(Deck::SIZE_DeckArr);}
//---------------------------------------------------------------------------------------------------------------------------
//Deck::Deck(const Deck & other){this->deckArr = other.deckArr;}
//---------------------------------------------------------------------------------------------------------------------------
Deck::Deck(Deck && other) : deckArr(other.deckArr) {other.deckArr.clear();}
//---------------------------------------------------------------------------------------------------------------------------
Deck & Deck::operator = (Deck && other) {
    this->deckArr = other.deckArr;
    other.deckArr.clear();                                     
    return *this;}
//---------------------------------------------------------------------------------------------------------------------------
const vector<Card> &Deck::getDeckArr() const {return deckArr;}
//---------------------------------------------------------------------------------------------------------------------------
unsigned long Deck::size() const {return deckArr.size();}
//---------------------------------------------------------------------------------------------------------------------------
//const int & Deck::capacity() const {return Deck::SIZE_DeckArr;}
//---------------------------------------------------------------------------------------------------------------------------
void Deck::gen(const unique_ptr< vector<Card> > & board_ptr, const Hand &heroHand, const Hand &oppHand)
{
//    deckArr.reserve(Deck::SIZE_DeckArr);
    
    if (!deckArr.empty())
        deckArr.clear();
    
//    Card card;
    
    for (auto card = make_unique<Card>(Card::valCard::_2, Card::suitCard::_d_0x1); card->getValueNum() < Card::sizeValueCardArr; card->inc_val())
    {
        for (; card->getSuitNum() < Card::sizeSuitCardArr; card->inc_suit())
        {
           if (*card != heroHand.getCard1() && 
                *card != heroHand.getCard2() && 
                *card != oppHand.getCard1() && 
                *card != oppHand.getCard2() &&
                !checkCardOnBoard(board_ptr, card))
            {
                deckArr.push_back(*card);
            }
        }
    }
}