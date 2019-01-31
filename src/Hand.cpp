#include "Hand.h"


Hand::Hand(const Hand & other){*this = other;};
//---------------------------------------------------------------------------------------------------------------------------
Hand::Hand() : card1(), card2() {}
//---------------------------------------------------------------------------------------------------------------------------
Hand::Hand(Hand && other){*this = std::move(other);}
//---------------------------------------------------------------------------------------------------------------------------
Hand::Hand( const int numValueCard1,
            const int numSuitCard1,
            const int numValueCard2,
            const int numSuitCard2)
{
    
    card1.SetCard(numValueCard1, numSuitCard1);
    card2.SetCard(numValueCard2, numSuitCard2);
}
//---------------------------------------------------------------------------------------------------------------------------
Hand::~Hand(){}
//---------------------------------------------------------------------------------------------------------------------------
// Указание руки
void Hand::SetHand (const char valueCard1,
                    const char suitCard1,
                    const char valueCard2,
                    const char suitCard2)
{
    card1.SetCard(valueCard1, suitCard1);
    card2.SetCard(valueCard2, suitCard2);
}
//---------------------------------------------------------------------------------------------------------------------------
void Hand::SetHand (const int numValueCard1,
                    const int numSuitCard1,
                    const int numValueCard2,
                    const int numSuitCard2)
{
    this->card1.SetCard(numValueCard1, numSuitCard1);
    this->card2.SetCard(numValueCard2, numSuitCard2);
}
//---------------------------------------------------------------------------------------------------------------------------
void Hand::SetHand (const Card &card1, const Card &card2)
{
    this->card1 = card1;
    this->card2 = card2;
}
//---------------------------------------------------------------------------------------------------------------------------
// Получение значения руки в переменные типа char
void Hand::GetHand(char &valueCard1Link,
                   char &suitCard1Link,
                   char &valueCard2Link,
                   char &suitCard2Link) const
{
    valueCard1Link = card1.GetValueCard();
    suitCard1Link = card1.GetSuitCard();
    valueCard2Link = card2.GetValueCard();
    suitCard2Link = card2.GetSuitCard();
}
//---------------------------------------------------------------------------------------------------------------------------
void Hand::GetCards(Card &card1, Card &card2) const
{
    card1.SetValueCardNum(this->card1.GetValueCardNum());
    card1.SetSuitCardNum(this->card1.GetSuitCardNum());
    card2.SetValueCardNum(this->card2.GetValueCardNum());
    card2.SetSuitCardNum(this->card2.GetSuitCardNum());
}
//---------------------------------------------------------------------------------------------------------------------------
const Card & Hand::getCard1 () const {return card1;}
//---------------------------------------------------------------------------------------------------------------------------
const Card & Hand::getCard2 () const {return card2;}
//---------------------------------------------------------------------------------------------------------------------------
bool Hand::operator== (const Hand &other) const
{
    return (((this->card1==other.card1) && (this->card2==other.card2)) || ((this->card1==other.card2) && (this->card2==other.card1)));
}
//---------------------------------------------------------------------------------------------------------------------------
bool Hand::operator!= (const Hand &other) const
{
    return !(((this->card1==other.card1) && (this->card2==other.card2)) || ((this->card1==other.card2) && (this->card2==other.card1)));
}
//---------------------------------------------------------------------------------------------------------------------------
Hand & Hand::operator= (const Hand & other) {this->card1 = other.card1; this->card2 = other.card2;
                                             return *this;}
//---------------------------------------------------------------------------------------------------------------------------
Hand & Hand::operator= (Hand && other) {this->card1 = std::move(other.card1); this->card2 = std::move(other.card2);
                                             return *this;}