#include "handstrength.h"
#include <cassert>


HandStrengthList::HandStrengthList() : hight(0), pair(0), twopair(0), set(0), strait(0), flash(0), fullhouse(0), kare(0), straitflash(0) {}
//---------------------------------------------------------------------------------------------------------------------------
HandStrength::HandStrength(const HandStrength & other){this->curr_strength = other.curr_strength;};
//---------------------------------------------------------------------------------------------------------------------------
HandStrength::HandStrength(const Hand &hand, const unique_ptr<vector<Card> > &board_ptr)
{
    curr_strength = checkCurrStrength(hand, board_ptr);
}
//---------------------------------------------------------------------------------------------------------------------------
const HandStrength::strength & HandStrength::getCurrStrength() const {return curr_strength;}
//---------------------------------------------------------------------------------------------------------------------------
HandStrength::strength HandStrength::checkCurrStrength(const Hand &hand, const unique_ptr<vector<Card> > &board_ptr) const
{
    if (board_ptr->size() < 3) {
        assert(board_ptr->size() == 0 && "invalid board");
        
        // проверка на пару, если борд пуст
        if (hand.getCard1().getValueNum() == hand.getCard2().getValueNum()) {
            return HandStrength::strength::PAIR;
        }
    }
    else {
        assert(board_ptr->size() < 6 && "invalid board");
        assert((hand.getCard1().getValueNum() != 0 && hand.getCard1().getSuitNum() != 0) &&
               (hand.getCard2().getValueNum() != 0 && hand.getCard2().getSuitNum() != 0) &&
               "invalid hand initialization");
        unique_ptr< vector<Card>> combo_ptr;
        combo_ptr->reserve(board_ptr->size() + 2);
        for (auto const & card : *board_ptr) {
            combo_ptr->push_back(card);
        }
        combo_ptr->push_back(hand.getCard1());
        combo_ptr->push_back(hand.getCard2());
        
        uint32_t combo = 0;
        for (auto const & card : *board_ptr) {
            combo |= (card.getValueNum() | card.getSuitNum());
        }
        
        combo |= (hand.getCard1().getValueNum() | hand.getCard1().getSuitNum()) | (hand.getCard2().getValueNum() | hand.getCard2().getSuitNum());
        
        // проверка на стрит-флеш
        if (match_straitflash(combo_ptr, combo))
            return HandStrength::strength::STRAIT_FLUSH;
        
        // проверка на карэ
        if (match_kare(combo_ptr))
            return HandStrength::strength::KARE;
        
        // проверка на фулл-хаус
        if (match_fullhouse(combo_ptr))
            return HandStrength::strength::FULL_HOUSE;
        
        // проверка на флеш
        if (match_flush(combo_ptr, combo))
            return HandStrength::strength::FLASH;
        
        // проверка на стрит
        if (match_strait(combo))
            return HandStrength::strength::STRAIT;
        
        // проверка на сет
        if (match_set(combo_ptr))
            return HandStrength::strength::SET;
        
        // проверка на две пары
        if (match_twopairs(combo_ptr))
            return HandStrength::strength::TWO_PAIRS;
        
        // проверка на пару
        if ([&board_ptr, &hand](){
            for (auto const & el : *board_ptr) {
                if (hand.getCard1().getValueNum() == el.getValueNum() ||
                    hand.getCard2().getValueNum() == el.getValueNum()) {
                    return true;
                }
            }
            return false;
            }()
            || hand.getCard1().getValueNum() == hand.getCard2().getValueNum())
        {
            return HandStrength::strength::PAIR;
        }// проверка на пару
    }//проверка, если борд не пуст
            
    return HandStrength::strength::HIGHT;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на стрит-флеш
bool HandStrength::match_straitflash(const unique_ptr<vector<Card> > & combo_ptr, const uint32_t & combo) const {
    bool res = false;
    uint32_t combo_val = combo & Card::value_mask;
    uint8_t combo_suit = combo & Card::suit_mask;
    if (match_strait(combo_val) && (combo_suit == 0x1 || combo_suit == 0x2 || combo_suit == 0x4 || combo_suit == 0x8))
        res = true;
    else if ((combo_ptr->size() == 6 && (combo_suit == 0x7 || combo_suit == 0xe|| combo_suit == 0xd || combo_suit == 0xb)) ||
             (combo_ptr->size() == 7 && combo_suit == 0xf))
        ;
    else if (match_strait(combo_val)) {
    
            unique_ptr<vector<Card> > temp_arr_ptr(new vector<Card>);
            temp_arr_ptr->reserve(combo_ptr->size());
            
            for (unsigned match_num = 0; ((combo_ptr->size() - match_num) > 4) && (temp_arr_ptr->size() < 5); ++match_num)
            {
                temp_arr_ptr->clear();
                temp_arr_ptr->push_back(combo_ptr->at(match_num));
                for (unsigned match_subnum = match_num + 1; match_subnum < combo_ptr->size(); ++match_subnum)
                {
                    if (combo_ptr->at(match_num).getSuitNum() == combo_ptr->at(match_subnum).getSuitNum())
                        temp_arr_ptr->push_back(combo_ptr->at(match_subnum));
                }
            }
            
            combo_val = 0;
            for (auto const & card : *temp_arr_ptr)
            {
                combo_val |= (card.getValueNum() & Card::value_mask);
            }
            res = match_strait(combo_val);
            
// для проверки разницы в скорасти вычисления            
//            if (temp_arr_ptr->size() > 4)
//            {
//                temp_arr_ptr = sort_cards(temp_arr_ptr);
                
//                for (unsigned match_num = 0; (combo_ptr->size() - match_num) >= 5; ++match_num)
//                {
//                    if ((temp_arr_ptr->at(match_num).getValueNum() + 1 == temp_arr_ptr->at(match_num + 1).getValueNum()) &&
//                        (temp_arr_ptr->at(match_num).getValueNum() + 2 == temp_arr_ptr->at(match_num + 2).getValueNum()) &&
//                        (temp_arr_ptr->at(match_num).getValueNum() + 3 == temp_arr_ptr->at(match_num + 3).getValueNum()) &&
//                        (temp_arr_ptr->at(match_num).getValueNum() + 4 == temp_arr_ptr->at(match_num + 4).getValueNum()))
//                        res = true;                                                        
//                    else if (temp_arr_ptr->at(match_num).getValueNum() == 0)                     
//                    {                                                                       
//                        if ((temp_arr_ptr->at(match_num).getValueNum() + 1 == temp_arr_ptr->at(match_num + 1).getValueNum()) &&
//                            (temp_arr_ptr->at(match_num).getValueNum() + 2 == temp_arr_ptr->at(match_num + 2).getValueNum()) &&
//                            (temp_arr_ptr->at(match_num).getValueNum() + 3 == temp_arr_ptr->at(match_num + 3).getValueNum()) &&
//                            (temp_arr_ptr->at(match_num).getValueNum() + 12 == temp_arr_ptr->back().getValueNum()))
//                            res = true;
//                    }
//                }
//            }
    
    }
    return res;
}
//---------------------------------------------------------------------------------------------------------------------------
//проверка на карэ
bool HandStrength::match_kare(const unique_ptr<vector<Card> > & combo_ptr) const {
    bool res = false;
    int match_true;
    
    for (unsigned count = 0; (combo_ptr->size() - count) > 3; ++count) {
        match_true = 0;
        
        for (unsigned subcount = count + 1; subcount < combo_ptr->size(); ++subcount) {
            if (combo_ptr->at(count).getValueNum() == combo_ptr->at(subcount).getValueNum())
                ++match_true;
        }
        
        if (match_true > 2) {
            res = true;
            break;
        }
    }
    
    return res;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на фулл-хаус
bool HandStrength::match_fullhouse(const unique_ptr<vector<Card> > & combo_ptr) const {
    unique_ptr<vector<Card> > temp_arr_ptr(new vector<Card>);
    temp_arr_ptr = sort_cards(combo_ptr);
    bool res = false;
    
    for (unsigned count = 0; (temp_arr_ptr->size() - count) > 4; ++count)
    {
        if (temp_arr_ptr->at(count).getValueNum() == temp_arr_ptr->at(count + 1).getValueNum() &&
            temp_arr_ptr->at(count).getValueNum() == temp_arr_ptr->at(count + 2).getValueNum())
        {
            temp_arr_ptr->erase(temp_arr_ptr->begin() + count, temp_arr_ptr->begin() + count + 2);
            for (unsigned subcount = 0; (temp_arr_ptr->size() - subcount) >= 2; ++subcount) {
                if (temp_arr_ptr->at(subcount).getValueNum() == temp_arr_ptr->at(subcount + 1).getValueNum())
                    res = true;
            }
        }
    }
    
    return res;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на флеш
bool HandStrength::match_flush(const unique_ptr<vector<Card> > & combo_ptr, const uint32_t & combo) const {
    bool res = false;
    uint8_t combo_suit = combo & Card::suit_mask;
    
    if (combo_suit == 0x1 || combo_suit == 0x2 || combo_suit == 0x4 || combo_suit == 0x8)
        res = true;
    else if ((combo_ptr->size() == 6 && (combo_suit == 0x7 || combo_suit == 0xe|| combo_suit == 0xd || combo_suit == 0xb)) ||
             (combo_ptr->size() == 7 && combo_suit == 0xf))
        ;
    else {
        for (unsigned match_num = 0; (combo_ptr->size() - match_num) > 4; ++match_num)
        {
            unsigned match_true = 0, match_false = 0;
            for (unsigned match_subnum = match_num + 1; match_subnum < combo_ptr->size(); ++match_subnum)
            {
                if (combo_ptr->at(match_num).getSuitNum() == combo_ptr->at(match_subnum).getSuitNum())
                    ++match_true;
                else {
                    ++match_false;
                    if ((combo_ptr->size() - match_num - match_false) < 5)
                        break;
                }
            }
            
            if (match_true > 3) {
                res = true;
                break;
            }
        }
    }
        
    return res;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на стрит
bool HandStrength::match_strait(const uint32_t & combo) const {    
    return ((combo & 0x1F000000) == 0x1F000000 || (combo & 0xF800000) == 0xF800000 || (combo & 0x7C00000) == 0x7C00000 || (combo & 0x3E00000) == 0x3E00000 ||
            (combo & 0x1F00000 ) == 0x1F00000  || (combo & 0xF80000 ) == 0xF80000  || (combo & 0x7C0000 ) == 0x7C0000  || (combo & 0x3E0000 ) == 0x3E0000  ||
            (combo & 0x1F0000  ) == 0x1F0000   || (combo & 0x100F0000) == 0x100F0000);
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на сет
bool HandStrength::match_set(const unique_ptr<vector<Card> > & combo_ptr) const {
    unique_ptr<vector<Card> > temp_arr_ptr(new vector<Card>);
    temp_arr_ptr = sort_cards(combo_ptr);
    bool res = false;
    
    for (unsigned count = 0; (temp_arr_ptr->size() - count) >= 3; ++count) {
        if (temp_arr_ptr->at(count).getValueNum() == temp_arr_ptr->at(count + 1).getValueNum() &&
            temp_arr_ptr->at(count).getValueNum() == temp_arr_ptr->at(count + 2).getValueNum())
            res = true;
    }
    
    return res;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на две пары
bool HandStrength::match_twopairs(const unique_ptr<vector<Card> > & combo_ptr) const {
    unique_ptr<vector<Card> > temp_arr_ptr(new vector<Card>);
    temp_arr_ptr = sort_cards(combo_ptr);
    bool res = false;
    
    for (unsigned count = 0; (temp_arr_ptr->size() - count) >= 4; ++count)
    {
        if (temp_arr_ptr->at(count).getValueNum() == temp_arr_ptr->at(count + 1).getValueNum())
        {
            temp_arr_ptr->erase(temp_arr_ptr->begin() + count, temp_arr_ptr->begin() + count + 2);
            for (unsigned subcount = 0; (temp_arr_ptr->size() - subcount) >= 2; ++subcount) {
                if (temp_arr_ptr->at(subcount).getValueNum() == temp_arr_ptr->at(subcount + 1).getValueNum())
                    res = true;
            }
        }
    }
    
    return res;
}
//---------------------------------------------------------------------------------------------------------------------------
unique_ptr<vector<Card> > && sort_cards(const unique_ptr<vector<Card> > & combo_ptr) {
    unique_ptr<vector<Card> > temp_arr_ptr(new vector<Card>); 
    *temp_arr_ptr = *combo_ptr;
    
    Card temp_card;
    
    for (unsigned count = 0; count < temp_arr_ptr->size(); ++count) {
        for (unsigned subcount = count + 1; subcount < temp_arr_ptr->size(); ++subcount) {
            if (temp_arr_ptr->at(count) > temp_arr_ptr->at(subcount))
            {
                temp_card = temp_arr_ptr->at(count);
                temp_arr_ptr->at(count) = temp_arr_ptr->at(subcount);
                temp_arr_ptr->at(subcount) = temp_card;
            }
                
        }
    }
    
    return move(temp_arr_ptr);
}