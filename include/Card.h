#ifndef CARD_H
#define CARD_H

#include <utility>
#include "defines.h"

//using namespace std;

struct Card final
{
    Card();
    Card(int &&numValueCard,
		 int &&numSuitCard);
    Card(const Card & other); // Конструктор копирования карты в создаваемый объект типа Card
    Card(Card && other);
    ~Card();
    
    enum class vCard {_2, _3, _4, _5, _6, _7, _8, _9, _T, _J, _Q, _K, _A};
    enum class sCard {_d, _s, _c, _h};
    

	void SetCard(char &&SetValueCard, char &&SetSuitCard);	// Устанавливает значение и масть карты
	void SetCard(const int numValueCard, const int numSuitCard);
	void SetSuitCardNum(const int numSuitCard);    // Устанавливает индекс масти карты
    void SetValueCardNum(const int numValueCard);    // Устанавливает индекс значения карты
    char GetSuitCard() const;    // Возвращает масть карты
    char GetValueCard() const;    // Возвращает значение карты
    int GetSuitCardNum() const;    // Возвращает индекс массива масти карты
    int GetValueCardNum() const;    // Возвращает индекс массива значений карты
    bool operator == (const Card &other) const;
    bool operator !=(const Card &other) const;
    Card & operator = (const Card &other);
    Card & operator = (Card && other);
    bool operator < (const Card &other) const;
    bool operator > (const Card &other) const;

    static const int sizeValueCardArr = 13;
    static const int sizeSuitCardArr = 4;

private:
	int numValueCard, numSuitCard;

    static const char ValueCardArr[sizeValueCardArr];
	static const char SuitCardArr[sizeSuitCardArr];
};

#endif