#pragma once



#include "Card.h"
#include "defines.h"




//using namespace std;



class Card
{
public:

    Card ();

    Card (const size_num numValueCard,
		  const size_num numSuitCard);

    // Конструктор копирования карты в создаваемый объект типа Card
    Card(const Card &other);

    ~Card();

	// Устанавливает значение и масть карты
	void SetCard(const char SetValueCard, const char SetSuitCard);

	void SetCard(const size_num numValueCard, const size_num numSuitCard);

    // Устанавливает индекс масти карты
	void SetSuitCardNum(const size_num numSuitCard);

    // Устанавливает индекс значения карты
    void SetValueCardNum(const size_num numValueCard);

    // Возвращает масть карты
    char GetSuitCard(void) const;

    // Возвращает значение карты
    char GetValueCard(void) const;

    // Возвращает индекс массива масти карты
    size_num GetSuitCardNum() const;

    // Возвращает индекс массива значений карты
    size_num GetValueCardNum() const;

    bool operator == (const Card &other) const;

    bool operator !=(const Card &other) const;

    Card & operator = (const Card &other);
    
    bool operator< (const Card &other) const;
    
    bool operator> (const Card &other) const;

    static const size_num sizeValueCardArr = 13;
    static const size_num sizeSuitCardArr = 4;

private:

	size_num numValueCard, numSuitCard;

    static const char ValueCardArr[sizeValueCardArr];
	static const char SuitCardArr[sizeSuitCardArr];

};
