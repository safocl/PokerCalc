#ifndef CARD_H
#define CARD_H

#include <utility>
#include "defines.h"
#include <cstdint>

//using namespace std;

struct Card final
{
    Card();
    Card(int &&numValueCard,
		 int &&numSuitCard);
    Card(const Card & other); // Конструктор копирования карты в создаваемый объект типа Card
    Card(Card && other);
    ~Card();
    
    enum class valCard : uint32_t { NODEF = 0,
                                  _2 = 0x10000, //0b1000000000000000
                                  _3 = 0x20000, //0b10000000000000000
                                  _4 = 0x40000, //0b100000000000000000
                                  _5 = 0x80000, //0b1000000000000000000
                                  _6 = 0x100000, //0b10000000000000000000
                                  _7 = 0x200000, //0b100000000000000000000
                                  _8 = 0x400000, //0b1000000000000000000000
                                  _9 = 0x800000, //0b10000000000000000000000
                                  _T = 0x1000000, //0b100000000000000000000000
                                  _J = 0x2000000, //0b1000000000000000000000000
                                  _Q = 0x4000000, //0b10000000000000000000000000
                                  _K = 0x8000000, //0b100000000000000000000000000
                                  _A = 0x10000000}; //0b100000000000000000000000000
    
    enum class suitCard : uint32_t {NODEF = 0,
                                    _d = 0x1, //0b1
                                    _s = 0x2, //0b10
                                    _c = 0x4, //0b100
                                    _h = 0x8}; //0b1000
    

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