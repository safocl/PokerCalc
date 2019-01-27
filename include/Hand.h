#ifndef HAND_H
#define HAND_H


#include <vector>
#include "Card.h"
#include "defines.h"




using namespace std;

struct Hand final
{
    Hand();
    Hand(const Hand & other);
    Hand(Hand && other);
    Hand(const size_t numValueCard1,
         const size_t numSuitCard1,
         const size_t numValueCard2,
         const size_t numSuitCard2);
    
    ~Hand();

	// Указание руки
	void SetHand (const char valueCard1,
                  const char suitCard1,
                  const char valueCard2,
                  const char suitCard2);

    void SetHand (const size_t numValueCard1,
                  const size_t numSuitCard1,
                  const size_t numValueCard2,
                  const size_t numSuitCard2);

	void SetHand (const Card &card1, const Card &card2);

	// Получение значения руки в переменные типа char
    void GetHand(char &valueCard1Link, char &suitCard1Link, char &valueCard2Link, char &suitCard2Link) const;
    void GetCards(Card &card1, Card &card2) const;
    const Card & getCard1 () const;
    const Card & getCard2 () const;
    bool operator== (const Hand &other) const;
    bool operator!= (const Hand &other) const;
    Hand & operator = (const Hand & other);
    Hand & operator = (Hand && other);

private:
    Card card1,
		 card2;
};


#endif //HAND_H