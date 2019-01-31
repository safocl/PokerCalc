#include "handstrength.h"


HandStrengthList::HandStrengthList() : hight(0), pair(0), twopair(0), set(0), strait(0), flash(0), fullhouse(0), kare(0), straitflash(0) {}
//---------------------------------------------------------------------------------------------------------------------------
HandStrength::HandStrength(const HandStrength & other){this->curr_strength = other.curr_strength;};
//---------------------------------------------------------------------------------------------------------------------------
HandStrength::HandStrength(const Hand &hand, const unique_ptr<QVector<Card> > &board_ptr)
{
    curr_strength = checkCurrStrength(hand, board_ptr);
}
//---------------------------------------------------------------------------------------------------------------------------
const HandStrength::strength & HandStrength::getCurrStrength() const {return curr_strength;}
//---------------------------------------------------------------------------------------------------------------------------
HandStrength::strength HandStrength::checkCurrStrength(const Hand &hand, const unique_ptr<QVector<Card> > &board_ptr) const
{
    if (board_ptr->empty())
    {
        // проверка на пару, если борд пуст
        if (hand.getCard1().GetValueCardNum() == hand.getCard2().GetValueCardNum())
        {
            return HandStrength::strength::PAIR;
        }
    }// проверка на пару, если борд пуст
    else //проверка, если борд не пуст
    {
        unique_ptr<QVector<Card> > combo_ptr(new QVector<Card>);
        combo_ptr->reserve(board_ptr->size()+2);
        *combo_ptr = *board_ptr;
        combo_ptr->push_back(hand.getCard1());
        combo_ptr->push_back(hand.getCard2());
        
        
        // проверка на стрит-флеш
        if (match_straitflash(combo_ptr))
            return HandStrength::strength::STRAIT_FLUSH;
        
        // проверка на карэ
        if (match_kare(combo_ptr))
            return HandStrength::strength::KARE;
        
        // проверка на фулл-хаус
        if (match_fullhouse(combo_ptr))
            return HandStrength::strength::FULL_HOUSE;
        
        // проверка на флеш
        if (match_flush(combo_ptr))
            return HandStrength::strength::FLASH;
        
        // проверка на стрит
        if (match_strait(combo_ptr))
            return HandStrength::strength::STRAIT;
        
        // проверка на сет
        if (match_set(combo_ptr))
            return HandStrength::strength::SET;
        
        // проверка на две пары
        if (match_twopairs(combo_ptr))
            return HandStrength::strength::TWO_PAIRS;
        
        // проверка на пару
        if ([&board_ptr, &hand](){
            for (auto el : *board_ptr)
            {
                if (hand.getCard1().GetValueCardNum() == el.GetValueCardNum()
                    || hand.getCard2().GetValueCardNum() == el.GetValueCardNum())
                {
                    return true;
                }
            }
            return false;
            }()
            || hand.getCard1().GetValueCardNum() == hand.getCard2().GetValueCardNum())
        {
            return HandStrength::strength::PAIR;
        }// проверка на пару
    }//проверка, если борд не пуст
            
    return HandStrength::strength::HIGHT;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на стрит-флеш
bool HandStrength::match_straitflash(const unique_ptr<QVector<Card> > & combo_ptr) const
{
    if (combo_ptr->size() < 5)
        return false;
    else
    {
        unique_ptr<QVector<Card> > temp_arr_ptr(new QVector<Card>);
        temp_arr_ptr->reserve(combo_ptr->size());
        
        for (int match_num = 0; (combo_ptr->size() - match_num) > 4; ++match_num)
        {
            temp_arr_ptr->clear();
            temp_arr_ptr->push_back(combo_ptr->at(match_num));
            for (int match_subnum = match_num + 1; match_subnum < combo_ptr->size(); ++match_subnum)
            {
                if (combo_ptr->at(match_num).GetSuitCardNum() == combo_ptr->at(match_subnum).GetSuitCardNum())
                    temp_arr_ptr->push_back(combo_ptr->at(match_subnum));
            }
        }
        if (temp_arr_ptr->size() > 4)
        {
            temp_arr_ptr = sort_cards(temp_arr_ptr);
            
            for (int match_num = 0; (combo_ptr->size() - match_num) >= 5; ++match_num)
            {
                if ((temp_arr_ptr->at(match_num).GetValueCardNum() + 1 == temp_arr_ptr->at(match_num + 1).GetValueCardNum()) &&
                    (temp_arr_ptr->at(match_num).GetValueCardNum() + 2 == temp_arr_ptr->at(match_num + 2).GetValueCardNum()) &&
                    (temp_arr_ptr->at(match_num).GetValueCardNum() + 3 == temp_arr_ptr->at(match_num + 3).GetValueCardNum()) &&
                    (temp_arr_ptr->at(match_num).GetValueCardNum() + 4 == temp_arr_ptr->at(match_num + 4).GetValueCardNum()))
                    return true;                                                        
                else if (temp_arr_ptr->at(match_num).GetValueCardNum() == 0)                     
                {                                                                       
                    if ((temp_arr_ptr->at(match_num).GetValueCardNum() + 1 == temp_arr_ptr->at(match_num + 1).GetValueCardNum()) &&
                        (temp_arr_ptr->at(match_num).GetValueCardNum() + 2 == temp_arr_ptr->at(match_num + 2).GetValueCardNum()) &&
                        (temp_arr_ptr->at(match_num).GetValueCardNum() + 3 == temp_arr_ptr->at(match_num + 3).GetValueCardNum()) &&
                        (temp_arr_ptr->at(match_num).GetValueCardNum() + 12 == temp_arr_ptr->back().GetValueCardNum()))
                        return true;
                }
            }
        }
    }
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------
//проверка на карэ
bool HandStrength::match_kare(const unique_ptr<QVector<Card> > & combo_ptr) const
{
    int c_true;
    
    for (int count = 0; (combo_ptr->size() - count) >= 4; ++count)
    {
        c_true = 0;
        
        for (int subcount = count + 1; subcount < combo_ptr->size(); ++subcount)
        {
            if (combo_ptr->at(count).GetValueCardNum() == combo_ptr->at(subcount).GetValueCardNum())
                ++c_true;
        }
        
        if (c_true > 2)
            return true;
    }
    
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на фулл-хаус
bool HandStrength::match_fullhouse(const unique_ptr<QVector<Card> > & combo_ptr) const
{
    unique_ptr<QVector<Card> > temp_arr_ptr(new QVector<Card>);
    temp_arr_ptr = sort_cards(combo_ptr);
    
    for (int count = 0; (temp_arr_ptr->size() - count) >= 5; ++count)
    {
        if (temp_arr_ptr->at(count).GetValueCardNum() == temp_arr_ptr->at(count + 1).GetValueCardNum() &&
            temp_arr_ptr->at(count).GetValueCardNum() == temp_arr_ptr->at(count + 2).GetValueCardNum())
        {
            temp_arr_ptr->erase(temp_arr_ptr->begin() + count, temp_arr_ptr->begin() + count + 2);
            for (int subcount = 0; (temp_arr_ptr->size() - subcount) >= 2; ++subcount) {
                if (temp_arr_ptr->at(subcount).GetValueCardNum() == temp_arr_ptr->at(subcount + 1).GetValueCardNum())
                    return true;
            }
            return false;
        }
    }
    
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на флеш
bool HandStrength::match_flush(const unique_ptr<QVector<Card> > & combo_ptr) const
{
    if (combo_ptr->size() < 5)
        return false;
    else
    {
        for (int match_num = 0; (combo_ptr->size() - match_num) > 4; ++match_num)
        {
            int match_true = 0, match_false = 0;
            for (int match_subnum = match_num + 1; match_subnum < combo_ptr->size(); ++match_subnum)
            {
                if (combo_ptr->at(match_num).GetSuitCardNum() == combo_ptr->at(match_subnum).GetSuitCardNum())
                    ++match_true;
                else {
                    ++match_false;
                    if ((combo_ptr->size() - match_num - match_false) < 5)
                        return false;
                }
            }
            
            if (match_true > 3)
                return true;
        }
    }

    return false;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на стрит
bool HandStrength::match_strait(const unique_ptr<QVector<Card> > & combo_ptr) const
{
    if (combo_ptr->size() < 5)
        return false;
    else {
        unique_ptr<QVector<Card> > temp_arr_ptr(new QVector<Card>);
        temp_arr_ptr = sort_cards(combo_ptr);
        
        for (int match_num = 0; (combo_ptr->size() - match_num) >= 5; ++match_num)
        {
            if ((temp_arr_ptr->at(match_num).GetValueCardNum() + 1 == temp_arr_ptr->at(match_num + 1).GetValueCardNum()) &&
                (temp_arr_ptr->at(match_num).GetValueCardNum() + 2 == temp_arr_ptr->at(match_num + 2).GetValueCardNum()) &&
                (temp_arr_ptr->at(match_num).GetValueCardNum() + 3 == temp_arr_ptr->at(match_num + 3).GetValueCardNum()) &&
                (temp_arr_ptr->at(match_num).GetValueCardNum() + 4 == temp_arr_ptr->at(match_num + 4).GetValueCardNum()))
                return true;
            else if (temp_arr_ptr->at(match_num).GetValueCardNum() == 0)
            {
                if ((temp_arr_ptr->at(match_num + 1).GetValueCardNum() == 1) &&
                    (temp_arr_ptr->at(match_num + 2).GetValueCardNum() == 2) &&
                    (temp_arr_ptr->at(match_num + 3).GetValueCardNum() == 3) &&
                    (temp_arr_ptr->back().GetValueCardNum() == 12))
                    return true;
            }
        }
    }
    
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на сет
bool HandStrength::match_set(const unique_ptr<QVector<Card> > & combo_ptr) const
{
    unique_ptr<QVector<Card> > temp_arr_ptr(new QVector<Card>);
    temp_arr_ptr = sort_cards(combo_ptr);
    
    for (int count = 0; (temp_arr_ptr->size() - count) >= 3; ++count)
    {
        if (temp_arr_ptr->at(count).GetValueCardNum() == temp_arr_ptr->at(count + 1).GetValueCardNum() &&
            temp_arr_ptr->at(count).GetValueCardNum() == temp_arr_ptr->at(count + 2).GetValueCardNum())
            return true;
    }
    
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на две пары
bool HandStrength::match_twopairs(const unique_ptr<QVector<Card> > & combo_ptr) const
{
    unique_ptr<QVector<Card> > temp_arr_ptr(new QVector<Card>);
    temp_arr_ptr = sort_cards(combo_ptr);
    
    for (int count = 0; (temp_arr_ptr->size() - count) >= 4; ++count)
    {
        if (temp_arr_ptr->at(count).GetValueCardNum() == temp_arr_ptr->at(count + 1).GetValueCardNum())
        {
            temp_arr_ptr->erase(temp_arr_ptr->begin() + count, temp_arr_ptr->begin() + count + 2);
            for (int subcount = 0; (temp_arr_ptr->size() - subcount) >= 2; ++subcount) {
                if (temp_arr_ptr->at(subcount).GetValueCardNum() == temp_arr_ptr->at(subcount + 1).GetValueCardNum())
                    return true;
            }
            return false;
        }
    }
    
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------
unique_ptr<QVector<Card> > sort_cards(const unique_ptr<QVector<Card> > & combo_ptr)
{
    unique_ptr<QVector<Card> > temp_arr_ptr(new QVector<Card>); 
    *temp_arr_ptr = *combo_ptr;
    
    Card temp_card;
    
    for (int count = 0; count < temp_arr_ptr->size(); ++count) {
        for (int subcount = count + 1; subcount < temp_arr_ptr->size(); ++subcount) {
            if (temp_arr_ptr->at(count) > temp_arr_ptr->at(subcount))
            {
                temp_card = temp_arr_ptr->at(count);
                temp_arr_ptr->operator[](count) = temp_arr_ptr->at(subcount);
                temp_arr_ptr->operator[](subcount) = temp_card;
            }
                
        }
    }
    
    return temp_arr_ptr;
}