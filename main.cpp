#include <iostream>
#include <vector>
#include "Card.h"
#include "Hand.h"
#include "Board.h"
#include "Deck.h"
#include "handstrength.h"
#include <string>




using namespace std;

size_num combos_count (vector<Card> deckArr)
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
        board.push_back(Card(7,2));
        board.push_back(Card(2,1));
        board.push_back(Card(2,0));
        HandStrength player1(Hand(4,1,7,3), board);
        
    Deck::Refrash(board, Hand(1,2,2,3), Hand(3,2,8,3));
        
        cout << endl << combos_count(Deck::getDeckArr()) << endl;
        cout << endl << player1.getCurrStrength() << endl;
    } 
    
    catch (const char *str) 
    {
        cout << str << endl;
    }


    return 0;
}
