#include <iostream>
#include <vector>
#include "Card.h"
#include "Hand.h"
#include "Board.h"
#include "Deck.h"




using namespace std;

size_num combos (vector<Card> deckArr)
{
    size_num combosNum = 0;
    for (size_num firstCardIndex = 0; firstCardIndex < deckArr.size(); firstCardIndex++)
    {
        for (size_num secondCardIndex = firstCardIndex + 1; secondCardIndex < deckArr.size(); secondCardIndex++)
        {
            combosNum++;
        }
    }
    return combosNum;
}



int main()
{

    try
    {
        vector<Card> board{};
        board.reserve(5);
    Deck::Refrash(board, Hand(1,2,2,3), Hand(3,2,8,3));
        
        cout << endl << combos(Deck::getDeckArr()) << endl;
    } 
    
    catch (const char *str) 
    {
        cout << str << endl;
    }


    return 0;
}
