#include "handstrength.h"

//---------------------------------------------------------------------------------------------------------------------------
HandStrength::HandStrength(const Hand &hand, const vector<Card> &board)
{
    curr_strength = checkCurrStrength(hand, board);
}
//---------------------------------------------------------------------------------------------------------------------------
const HandStrength::strength & HandStrength::getCurrStrength() const {return curr_strength;}
//---------------------------------------------------------------------------------------------------------------------------
HandStrength::strength HandStrength::checkCurrStrength(const Hand &hand, const vector<Card> &board) const
{
    if (board.empty())
    {
        // проверка на пару, если борд пуст
        if (hand.getCard1().GetValueCardNum() == hand.getCard2().GetValueCardNum())
        {
            return HandStrength::strength::PAIR;
        }
    }// проверка на пару, если борд пуст
    else //проверка, если борд не пуст
    {
        vector<Card> combo;
        combo.reserve(board.size()+2);
        combo = board;
        combo.push_back(hand.getCard1());
        combo.push_back(hand.getCard2());
        
        
        // проверка на стрит-флеш
        if (match_straitflash(combo))
            return HandStrength::strength::STRAIT_FLASH;
        
        // проверка на карэ
        if (match_kare(combo))
            return HandStrength::strength::KARE;
        
        // проверка на фулл-хаус
        if (match_fullhouse(combo))
            return HandStrength::strength::FULL_HOUSE;
        
        // проверка на флеш
        if (match_flash(combo))
            return HandStrength::strength::FLASH;
        
        // проверка на стрит
        if (match_strait(combo))
            return HandStrength::strength::STRAIT;
        
        // проверка на сет
        if (match_set(combo))
            return HandStrength::strength::SET;
        
        // проверка на две пары
        if (match_twopairs(combo))
            return HandStrength::strength::TWO_PAIRS;
        
        // проверка на пару
        if ([&board, &hand](){
            for (auto el : board)
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
bool HandStrength::match_straitflash(const vector<Card> &combo) const
{
    if (combo.size() < 5)
        return false;
    else
    {
        vector<Card> temp_arr;
        temp_arr.reserve(combo.size());
        for (size_num match_num = 0; (combo.size() - match_num) > 4; ++match_num)
        {
            temp_arr.clear();
            temp_arr.push_back(combo.at(match_num));
            for (size_num match_subnum = match_num + 1; match_subnum < combo.size(); ++match_subnum)
            {
                if (combo.at(match_num).GetSuitCardNum() == combo.at(match_subnum).GetSuitCardNum())
                    temp_arr.push_back(combo.at(match_subnum));
            }
        }
        if (temp_arr.size() > 4)
        {
            auto temp = sort_cards(temp_arr);
            
            for (size_num match_num = 0; (combo.size() - match_num) >= 5; ++match_num)
            {
                if ((temp.at(match_num).GetValueCardNum() + 1 == temp.at(match_num + 1).GetValueCardNum()) &&
                    (temp.at(match_num).GetValueCardNum() + 2 == temp.at(match_num + 2).GetValueCardNum()) &&
                    (temp.at(match_num).GetValueCardNum() + 3 == temp.at(match_num + 3).GetValueCardNum()) &&
                    (temp.at(match_num).GetValueCardNum() + 4 == temp.at(match_num + 4).GetValueCardNum()))
                    return true;
                else if (temp.at(match_num).GetValueCardNum() == 0)
                {
                    if ((temp.at(match_num).GetValueCardNum() + 1 == temp.at(match_num + 1).GetValueCardNum()) &&
                        (temp.at(match_num).GetValueCardNum() + 2 == temp.at(match_num + 2).GetValueCardNum()) &&
                        (temp.at(match_num).GetValueCardNum() + 3 == temp.at(match_num + 3).GetValueCardNum()) &&
                        (temp.at(match_num).GetValueCardNum() + 12 == temp.back().GetValueCardNum()))
                        return true;
                }
            }
        }
    }
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------
//проверка на карэ
bool HandStrength::match_kare(const vector<Card> &combo) const
{
    size_num c_true;
    
    for (size_num count = 0; (combo.size() - count) >= 4; ++count)
    {
        c_true = 0;
        
        for (size_num subcount = count + 1; subcount < combo.size(); ++subcount)
        {
            if (combo.at(count).GetValueCardNum() == combo.at(subcount).GetValueCardNum())
                ++c_true;
        }
        
        if (c_true == 4)
            return true;
    }
    
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на фулл-хаус
bool HandStrength::match_fullhouse(const vector<Card> &combo) const
{
    vector<Card> temp_arr = sort_cards(combo);
    
    for (size_num count = 0; (temp_arr.size() - count) >= 5; ++count)
    {
        if (temp_arr.at(count).GetValueCardNum() == temp_arr.at(count + 1).GetValueCardNum() &&
            temp_arr.at(count).GetValueCardNum() == temp_arr.at(count + 2).GetValueCardNum())
        {
            temp_arr.erase(temp_arr.begin() + count, temp_arr.begin() + count + 2);
            for (size_num subcount = 0; (temp_arr.size() - subcount) >= 2; ++subcount) {
                if (temp_arr.at(subcount).GetValueCardNum() == temp_arr.at(subcount + 1).GetValueCardNum())
                    return true;
            }
            return false;
        }
    }
    
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на флеш
bool HandStrength::match_flash(const vector<Card> &combo) const
{
    if (combo.size() < 5)
        return false;
    else
    {
        for (size_num match_num = 0; (combo.size() - match_num) > 4; ++match_num)
        {
            size_num match_true = 0, match_false = 0;
            for (size_num match_subnum = match_num + 1; match_subnum < combo.size(); ++match_subnum)
            {
                if (combo.at(match_num).GetSuitCardNum() == combo.at(match_subnum).GetSuitCardNum())
                    ++match_true;
                else {
                    ++match_false;
                    if ((combo.size() - match_num - match_false) < 5)
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
bool HandStrength::match_strait(const vector<Card> &combo) const
{
    if (combo.size() < 5)
        return false;
    else {
        vector<Card> temp = sort_cards(combo);
        
        for (size_num match_num = 0; (combo.size() - match_num) >= 5; ++match_num)
        {
            if ((temp.at(match_num).GetValueCardNum() + 1 == temp.at(match_num + 1).GetValueCardNum()) &&
                (temp.at(match_num).GetValueCardNum() + 2 == temp.at(match_num + 2).GetValueCardNum()) &&
                (temp.at(match_num).GetValueCardNum() + 3 == temp.at(match_num + 3).GetValueCardNum()) &&
                (temp.at(match_num).GetValueCardNum() + 4 == temp.at(match_num + 4).GetValueCardNum()))
                return true;
            else if (temp.at(match_num).GetValueCardNum() == 0)
            {
                if ((temp.at(match_num + 1).GetValueCardNum() == 1) &&
                    (temp.at(match_num + 2).GetValueCardNum() == 2) &&
                    (temp.at(match_num + 3).GetValueCardNum() == 3) &&
                    (temp.back().GetValueCardNum() == 12))
                    return true;
            }
        }
    }
    
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на сет
bool HandStrength::match_set(const vector<Card> &combo) const
{
    vector<Card> temp_arr = sort_cards(combo);
    
    for (size_num count = 0; (temp_arr.size() - count) >= 3; ++count)
    {
        if (temp_arr.at(count).GetValueCardNum() == temp_arr.at(count + 1).GetValueCardNum() &&
            temp_arr.at(count).GetValueCardNum() == temp_arr.at(count + 2).GetValueCardNum())
            return true;
    }
    
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на две пары
bool HandStrength::match_twopairs(const vector<Card> &combo) const
{
    vector<Card> temp_arr = sort_cards(combo);
    
    for (size_num count = 0; (temp_arr.size() - count) >= 4; ++count)
    {
        if (temp_arr.at(count).GetValueCardNum() == temp_arr.at(count + 1).GetValueCardNum())
        {
            temp_arr.erase(temp_arr.begin() + count, temp_arr.begin() + count + 2);
            for (size_num subcount = 0; (temp_arr.size() - subcount) >= 2; ++subcount) {
                if (temp_arr.at(subcount).GetValueCardNum() == temp_arr.at(subcount + 1).GetValueCardNum())
                    return true;
            }
            return false;
        }
    }
    
    return false;
}
//---------------------------------------------------------------------------------------------------------------------------
vector<Card> sort_cards(const vector<Card> &combo)
{
    vector<Card> temp_arr = combo;
    
    Card temp_card;
    
    for (size_num count = 0; count < temp_arr.size(); ++count) {
        for (size_num subcount = count + 1; subcount < temp_arr.size(); ++subcount) {
            if (temp_arr.at(count) > temp_arr.at(subcount))
            {
                temp_card = temp_arr.at(count);
                temp_arr.at(count) = temp_arr.at(subcount);
                temp_arr.at(subcount) = temp_card;
            }
                
        }
    }
    
    return temp_arr;
}