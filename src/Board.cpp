#include "Board.h"


//---------------------------------------------------------------------------------------------------------------------------
bool pushNewCardToBoard(vector<Card> &board, const Hand &heroHand, const Hand &oppHand, const Card &card)
{
    if (!board.empty())
    {
        if (brute_force_matching_cards(board, card))
            return false;
    }
//    deck.gen(board, heroHand, oppHand);
    if (card != heroHand.getCard1() && 
        card != heroHand.getCard2() && 
        card != oppHand.getCard1() && 
        card != oppHand.getCard2())
    {
        board.push_back(card);

        return true;
    }
    else
        return false;
}
//---------------------------------------------------------------------------------------------------------------------------
bool brute_force_matching_cards(const vector<Card> &board, const Card &card)
{
    if (!board.empty())
    {
        for (auto const & el : board)
        {
            if (card == el)
                return true;
        }        
    }

    return false;
}