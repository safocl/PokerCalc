#include "handstrength.h"

HandStrength::strength HandStrength::getCurrStrength() const {return curr_strength;}

HandStrength::strength HandStrength::checkCurrStrength(const Hand &hand, const vector<Card> &board) const
{
    if (board.empty())
    {
        // проверка на пару, если борд пуст
        if (hand.getCard1().GetValueCardNum() == hand.getCard2().GetValueCardNum())
        {
            return HandStrength::PAIR;
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
            return HandStrength::STRAIT_FLASH;
        
        // проверка на карэ
        if (match_kare(combo))
            return HandStrength::CARE;
        
        // проверка на фулл-хаус
        if (match_fullhouse(combo))
            return HandStrength::FULL_HOUSE;
        
        // проверка на флеш
        if (match_flash(combo))
            return HandStrength::FLASH;
        
        // проверка на стрит
        if (match_strait(combo))
            return HandStrength::STRAIT;
        
        
        
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
            return HandStrength::PAIR;
        }// проверка на пару
    }//проверка, если борд не пуст
            
    return HandStrength::HIGHT;
}

// проверка на стрит-флеш
bool HandStrength::match_straitflash(const vector<Card> &combo) const
{
    if (match_flash(combo) && match_strait(combo))
        return true;
    
    return false;
}

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

// проверка на фулл-хаус
bool HandStrength::match_fullhouse(const vector<Card> &combo) const
{
    vector<Card> temp_arr = sort_cards(combo);
    
    for (size_num count = 0; (combo.size() - count) >= 5; ++count)
    {
        if (temp_arr.at(count) == temp_arr.at(count + 1) &&
            temp_arr.at(count) == temp_arr.at(count + 2))
        {
            temp_arr.erase(temp_arr.begin() + count, temp_arr.begin() + count + 2);
            for (size_num subcount = 0; (combo.size() - count) >= 2; ++subcount) {
                if (temp_arr.at(subcount) == temp_arr.at(subcount + 1))
                    return true;
            }
        }
    }
    
    return false;
}

// проверка на флеш
bool HandStrength::match_flash(const vector<Card> &combo) const
{
    if (combo.size() < 5)
        return false;
    else
    {
        for (size_num match_num = 0; match_num < combo.size(); ++match_num)
        {
            size_num match_true = 0, match_false = 0;
            for (size_num match_subnum = match_num; match_subnum < combo.size();)
            {
                ++match_subnum;
                
                if (combo.at(match_num).GetSuitCardNum() == combo.at(match_subnum).GetSuitCardNum())
                    ++match_true;
                else {
                    if ((combo.size() - match_num - ++match_false) < 5)
                        return false;
                }
            }
            
            if (match_true >= 5)
                return true;
        }
    }

    return false;
}

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
        }
    }
    
    return false;
}

vector<Card> sort_cards(const vector<Card> &combo)
{
    vector<Card> temp_arr = combo;
    
    Card temp_card;
    
    for (size_num count = 0; count < combo.size(); ++count) {
        for (size_num subcount = count + 1; subcount < combo.size(); ++subcount) {
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