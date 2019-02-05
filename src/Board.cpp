#include "Board.h"


//---------------------------------------------------------------------------------------------------------------------------
bool pushNewCardToBoard(unique_ptr< vector<Card> > & board_ptr, const Hand & heroHand, const Hand & oppHand, const unique_ptr<Card> & card)
{
    bool res = false;
    if (!board_ptr->empty() && check_for_a_card(board_ptr, card))
        ;
    else if (*card != heroHand.getCard1() && 
            *card != heroHand.getCard2() && 
            *card != oppHand.getCard1() && 
            *card != oppHand.getCard2())
            {
                board_ptr->push_back(*card);
        
                res = true;
            }

    return res;
}
//---------------------------------------------------------------------------------------------------------------------------
bool check_for_a_card(const unique_ptr< vector<Card> > & board_ptr, const unique_ptr<Card> & card)
{
    bool res = false;
    if (!board_ptr->empty())
    {
        for (auto const & el : *board_ptr)
        {
            if (*card == el) {
                res = true; 
                break;
            }
        }        
    }

    return res;
}