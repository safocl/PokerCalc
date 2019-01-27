#ifndef CARD_H
#define CARD_H

#include <utility>
#include "defines.h"

//using namespace std;

struct Card final
{
    Card();
    Card(const size_t numValueCard,
		 const size_t numSuitCard);
    Card(const Card & other); // Конструктор копирования карты в создаваемый объект типа Card
    Card(Card && other);
    ~Card();

	void SetCard(const char SetValueCard, const char SetSuitCard);	// Устанавливает значение и масть карты
	void SetCard(const size_t numValueCard, const size_t numSuitCard);
	void SetSuitCardNum(const size_t numSuitCard);    // Устанавливает индекс масти карты
    void SetValueCardNum(const size_t numValueCard);    // Устанавливает индекс значения карты
    const char & GetSuitCard(void) const;    // Возвращает масть карты
    const char & GetValueCard(void) const;    // Возвращает значение карты
    const size_t & GetSuitCardNum() const;    // Возвращает индекс массива масти карты
    const size_t & GetValueCardNum() const;    // Возвращает индекс массива значений карты
    bool operator == (const Card &other) const;
    bool operator !=(const Card &other) const;
    Card & operator = (const Card &other);
    Card & operator = (Card && other);
    bool operator < (const Card &other) const;
    bool operator > (const Card &other) const;

    static constexpr size_t sizeValueCardArr = 13;
    static constexpr size_t sizeSuitCardArr = 4;

private:
	size_t numValueCard, numSuitCard;

    static const char ValueCardArr[sizeValueCardArr];
	static const char SuitCardArr[sizeSuitCardArr];
};

#endif