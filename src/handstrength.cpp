#include "handstrength.h"

HandStrength::strength HandStrength::getCurrStrength() const {return curr_strength;}

HandStrength::strength HandStrength::checkCurrStrength(const Hand &hand, const vector<Card> &board)
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
        vector<size_num> arr_num_cards;
        arr_num_cards.reserve(5);
        
        // клонировать массив combo в новый массив и отсортировать последний
        
        for (size_num match_num = 0; match_num < combo.size(); ++match_num)
        {
            arr_num_cards.push_back(match_num);
            
            for (size_num match_subnum = match_num; match_subnum < combo.size();)
            {
                ++match_subnum;
                
                if ((combo.at(arr_num_cards.back()).GetValueCardNum() + 1) == combo.at(match_subnum).GetValueCardNum())
                {
                    arr_num_cards.push_back(match_subnum);
                }
            }
            
            arr_num_cards.clear();
        }
    }
    
    return false;
}

vector<Card> sort_cards(const vector<Card> &combo)
{
    vector<Card> temp_arr;
    temp_arr.reserve(combo.size());
    temp_arr = combo;
    
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