#pragma once


#include "Card.h"
#include "defines.h"

//using namespace std;

struct Card final
{
    Card();
    Card(const size_num numValueCard,
		 const size_num numSuitCard);
    Card(const Card & other); // Конструктор копирования карты в создаваемый объект типа Card
    ~Card();

	void SetCard(const char SetValueCard, const char SetSuitCard);	// Устанавливает значение и масть карты
	void SetCard(const size_num numValueCard, const size_num numSuitCard);
	void SetSuitCardNum(const size_num numSuitCard);    // Устанавливает индекс масти карты
    void SetValueCardNum(const size_num numValueCard);    // Устанавливает индекс значения карты
    const char & GetSuitCard(void) const;    // Возвращает масть карты
    const char & GetValueCard(void) const;    // Возвращает значение карты
    const size_num & GetSuitCardNum() const;    // Возвращает индекс массива масти карты
    const size_num & GetValueCardNum() const;    // Возвращает индекс массива значений карты
    bool operator == (const Card &other) const;
    bool operator !=(const Card &other) const;
    const Card & operator = (const Card &other);
    bool operator < (const Card &other) const;
    bool operator > (const Card &other) const;

    static constexpr size_num sizeValueCardArr = 13;
    static constexpr size_num sizeSuitCardArr = 4;

private:
	size_num numValueCard, numSuitCard;

    static const char ValueCardArr[sizeValueCardArr];
	static const char SuitCardArr[sizeSuitCardArr];
};
