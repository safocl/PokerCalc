#include "Card.h"

//---------------------------------------------------------------------------------------------------------------------------
Card::Card (){}
//---------------------------------------------------------------------------------------------------------------------------
Card::Card (const size_num numValueCard,
            const size_num numSuitCard)
{
    if (numValueCard >= sizeValueCardArr)
        throw ("Недопустимое значение карты");
    else
        this->numValueCard = numValueCard;

    if (numSuitCard >= sizeSuitCardArr)
        throw "Недопустимое значение масти карты";
    else
        this->numSuitCard = numSuitCard;
}
//---------------------------------------------------------------------------------------------------------------------------
// Конструктор копирования карты в создаваемый объект типа Card
Card::Card(const Card &other)
{
    this->numValueCard = other.numValueCard;
    this->numSuitCard = other.numSuitCard;
}
//---------------------------------------------------------------------------------------------------------------------------
Card::~Card(){}
//---------------------------------------------------------------------------------------------------------------------------
void Card::SetCard(const char SetValueCard, const char SetSuitCard)
{
    while (numValueCard < sizeValueCardArr)
    {
        if (SetValueCard == ValueCardArr[numValueCard])
            break;
        else numValueCard++;

        if (numValueCard == sizeValueCardArr)
        {
            numValueCard = 0;
            throw "Недопустимое значение карты";
        }

    }

    while (numSuitCard < sizeSuitCardArr)
    {
        if  (SetSuitCard == SuitCardArr[numSuitCard])
            break;
        else
            numSuitCard++;

        if (numSuitCard == sizeSuitCardArr)
        {
            numSuitCard = 0;
            throw "Недопустимое значение масти карты";
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void Card::SetCard(const size_num numValueCard, const size_num numSuitCard)
{
    SetValueCardNum(numValueCard);
    SetSuitCardNum(numSuitCard);
}
//---------------------------------------------------------------------------------------------------------------------------
void Card::SetSuitCardNum(const size_num numSuitCard)
{
    if (numSuitCard >= sizeSuitCardArr)
        throw "Недопустимое значение масти карты";
    else
        this->numSuitCard = numSuitCard;
}

// Устанавливает индекс значения карты
void Card::SetValueCardNum(const size_num numValueCard)
{
    if (numValueCard >= sizeValueCardArr)
        throw "Недопустимое значение карты";
    else
        this->numValueCard = numValueCard;
}
//---------------------------------------------------------------------------------------------------------------------------
// Возвращает масть карты
const char & Card::GetSuitCard() const {return SuitCardArr[numSuitCard];}
//---------------------------------------------------------------------------------------------------------------------------
// Возвращает значение карты
const char & Card::GetValueCard() const {return ValueCardArr[numValueCard];}
//---------------------------------------------------------------------------------------------------------------------------
// Возвращает индекс массива масти карты
const size_num & Card::GetSuitCardNum() const {return numSuitCard;}
//---------------------------------------------------------------------------------------------------------------------------
// Возвращает индекс массива значений карты
const size_num & Card::GetValueCardNum() const {return numValueCard;}
//---------------------------------------------------------------------------------------------------------------------------
bool Card::operator== (const Card &other) const {
    return (this->numSuitCard == other.numSuitCard && this->numValueCard == other.numValueCard);
}
//---------------------------------------------------------------------------------------------------------------------------
bool Card::operator!=(const Card &other) const {
    return !(this->numSuitCard == other.numSuitCard && this->numValueCard == other.numValueCard);
}
//---------------------------------------------------------------------------------------------------------------------------
const Card & Card::operator= (const Card &other) {
    this->SetCard(other.numValueCard, other.numSuitCard);
    return *this;
}
//---------------------------------------------------------------------------------------------------------------------------
bool Card::operator< (const Card &other) const {return (this->GetValueCardNum() < other.GetValueCardNum());}
//---------------------------------------------------------------------------------------------------------------------------
bool Card::operator> (const Card &other) const {return (this->GetValueCardNum() > other.GetValueCardNum());}
//---------------------------------------------------------------------------------------------------------------------------
const char Card::ValueCardArr[Card::sizeValueCardArr] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};
const char Card::SuitCardArr[Card::sizeSuitCardArr] = {'d','s','c','h'};
