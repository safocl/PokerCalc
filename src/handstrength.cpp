#include "handstrength.h"
#include "Board.h"
#include "Card.h"
#include "Hand.h"
#include <cassert>
#include <iostream>

namespace lp {

HandStrengthList::HandStrengthList()
    : /*hightP( 0 ), pairP( 0 ), twopairP( 0 ), setP( 0 ), straitP( 0 ), flushP( 0 ), fullhouseP( 0 ), kareP( 0 ),
      straitflushP( 0 ),*/
      /*sum_cycle( 0 ),*/ hight( 0 ), pair( 0 ), twopair( 0 ), set( 0 ), strait( 0 ), flush( 0 ), fullhouse( 0 ),
      kare( 0 ), straitflush( 0 ) {}

HandStrengthList::HandStrengthList( const HandStrengthList & other )
    : /*hightP( other.hightP ), pairP( other.pairP ), twopairP( other.twopairP ), setP( other.setP ),
      straitP( other.straitP ), flushP( other.flushP ), fullhouseP( other.fullhouseP ), kareP( other.kareP ),
      straitflushP( other.straitflushP ),*/
      /*sum_cycle( other.sum_cycle ),*/ hight( other.hight.load() ), pair( other.pair.load() ),
      twopair( other.twopair.load() ), set( other.set.load() ), strait( other.strait.load() ),
      flush( other.flush.load() ), fullhouse( other.fullhouse.load() ), kare( other.kare.load() ),
      straitflush( other.straitflush.load() ) {}
//---------------------------------------------------------------------------------------------------------------------------
HandStrength::HandStrength( const HandStrength & other ) : curr_strength( other.curr_strength ){};
//---------------------------------------------------------------------------------------------------------------------------
HandStrength::HandStrength( const Hand & hand, const Board & board )
    : curr_strength( checkCurrStrength( hand, board ) ) {}
//---------------------------------------------------------------------------------------------------------------------------
const HandStrength::strength & HandStrength::getCurrStrength() const { return curr_strength; }
//---------------------------------------------------------------------------------------------------------------------------
HandStrength::strength HandStrength::checkCurrStrength( const Hand & hand, const Board & board ) {
    if ( board.getBoard().size() < 3 ) {
        assert( board.getBoard().size() == 0 && "invalid board" );

        // проверка на пару, если борд пуст
        if ( hand.getLCard().getValueNum() == hand.getRCard().getValueNum() ) {
            return HandStrength::strength::PAIR;
        }
    } else {
        assert( board.getBoard().size() < 6 && "invalid board" );
        assert( ( hand.getLCard().getValueNum() != 0 && hand.getLCard().getSuitNum() != 0 ) &&
                ( hand.getRCard().getValueNum() != 0 && hand.getRCard().getSuitNum() != 0 ) &&
                "invalid hand initialization" );
        std::unique_ptr< std::vector< Card > > combo_ptr( new std::vector< Card > );
        combo_ptr->reserve( board.getBoard().size() + 2 );
        for ( auto const & card : board.getBoard() ) {
            combo_ptr->push_back( card );
        }
        combo_ptr->push_back( hand.getLCard() );
        combo_ptr->push_back( hand.getRCard() );

        uint32_t combo = 0;
        for ( auto const & card : board.getBoard() ) {
            combo |= ( card.getValueNum() | card.getSuitNum() );
        }

        combo |= ( hand.getLCard().getValueNum() | hand.getLCard().getSuitNum() ) |
                 ( hand.getRCard().getValueNum() | hand.getRCard().getSuitNum() );

        // проверка на стрит-флеш
        if ( matchStraitflush( *combo_ptr, combo ) )
            return HandStrength::strength::STRAIT_FLUSH;

        // проверка на карэ
        if ( matchKare( *combo_ptr ) )
            return HandStrength::strength::KARE;

        // проверка на фулл-хаус
        if ( matchFullhouse( *combo_ptr ) )
            return HandStrength::strength::FULL_HOUSE;

        // проверка на флеш
        if ( matchFlush( *combo_ptr, combo ) )
            return HandStrength::strength::FLUSH;

        // проверка на стрит
        if ( matchStrait( combo ) )
            return HandStrength::strength::STRAIT;

        // проверка на сет
        if ( matchSet( *combo_ptr ) )
            return HandStrength::strength::SET;

        // проверка на две пары
        if ( matchTwopairs( *combo_ptr ) )
            return HandStrength::strength::TWO_PAIRS;

        // проверка на пару
        if ( [&board, &hand]() {
                 for ( auto const & el : board.getBoard() ) {
                     if ( hand.getLCard().getValueNum() == el.getValueNum() ||
                          hand.getRCard().getValueNum() == el.getValueNum() ) {
                         return true;
                     }
                 }
                 return false;
             }() ||
             hand.getLCard().getValueNum() == hand.getRCard().getValueNum() ) {
            return HandStrength::strength::PAIR;
        } // проверка на пару
    }     //проверка, если борд не пуст

    return HandStrength::strength::HIGHT;
}

HandStrength::strength HandStrength::checkCurrStrength( const std::vector< Card > & combo ) {
    assert( combo.size() < 6 && "invalid board" );
    if ( combo.size() < 5 ) {
        assert( combo.size() == 2 && "invalid board" );

        // проверка на пару, если борд пуст
        if ( combo.at( 0 ).getValueNum() == combo.at( 1 ).getValueNum() ) {
            return HandStrength::strength::PAIR;
        }
    } else {
        for ( unsigned int i = 0; i < combo.size(); ++i ) {
            
                assert( ( hand.getLCard().getValueNum() != 0 && hand.getLCard().getSuitNum() != 0 ) &&
                        ( hand.getRCard().getValueNum() != 0 && hand.getRCard().getSuitNum() != 0 ) &&
                        "invalid hand initialization" );
            
        }
        std::unique_ptr< std::vector< Card > > combo_ptr( new std::vector< Card > );
        combo_ptr->reserve( board.getBoard().size() + 2 );
        for ( auto const & card : board.getBoard() ) {
            combo_ptr->push_back( card );
        }
        combo_ptr->push_back( hand.getLCard() );
        combo_ptr->push_back( hand.getRCard() );

        uint32_t combo = 0;
        for ( auto const & card : board.getBoard() ) {
            combo |= ( card.getValueNum() | card.getSuitNum() );
        }

        combo |= ( hand.getLCard().getValueNum() | hand.getLCard().getSuitNum() ) |
                 ( hand.getRCard().getValueNum() | hand.getRCard().getSuitNum() );

        // проверка на стрит-флеш
        if ( matchStraitflush( *combo_ptr, combo ) )
            return HandStrength::strength::STRAIT_FLUSH;

        // проверка на карэ
        if ( matchKare( *combo_ptr ) )
            return HandStrength::strength::KARE;

        // проверка на фулл-хаус
        if ( matchFullhouse( *combo_ptr ) )
            return HandStrength::strength::FULL_HOUSE;

        // проверка на флеш
        if ( matchFlush( *combo_ptr, combo ) )
            return HandStrength::strength::FLUSH;

        // проверка на стрит
        if ( matchStrait( combo ) )
            return HandStrength::strength::STRAIT;

        // проверка на сет
        if ( matchSet( *combo_ptr ) )
            return HandStrength::strength::SET;

        // проверка на две пары
        if ( matchTwopairs( *combo_ptr ) )
            return HandStrength::strength::TWO_PAIRS;

        // проверка на пару
        if ( [&board, &hand]() {
                 for ( auto const & el : board.getBoard() ) {
                     if ( hand.getLCard().getValueNum() == el.getValueNum() ||
                          hand.getRCard().getValueNum() == el.getValueNum() ) {
                         return true;
                     }
                 }
                 return false;
             }() ||
             hand.getLCard().getValueNum() == hand.getRCard().getValueNum() ) {
            return HandStrength::strength::PAIR;
        } // проверка на пару
    }     //проверка, если борд не пуст

    return HandStrength::strength::HIGHT;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на стрит-флеш
bool HandStrength::matchStraitflush( const std::vector< Card > & combo_ptr, const uint32_t & combo ) const {
    bool res = false;
    uint32_t combo_val = combo & Card::valueMask;
    uint8_t combo_suit = combo & Card::suitMask;
    if ( matchStrait( combo_val ) &&
         ( combo_suit == 0x1 || combo_suit == 0x2 || combo_suit == 0x4 || combo_suit == 0x8 ) )
        res = true;
    else if ( ( combo_ptr.size() == 6 &&
                ( combo_suit == 0x7 || combo_suit == 0xe || combo_suit == 0xd || combo_suit == 0xb ) ) ||
              ( combo_ptr.size() == 7 && combo_suit == 0xf ) )
        ;
    else if ( matchStrait( combo_val ) ) {

        std::unique_ptr< std::vector< Card > > temp_arr_ptr( new std::vector< Card > );
        temp_arr_ptr->reserve( combo_ptr.size() );

        for ( unsigned match_num = 0; ( ( combo_ptr.size() - match_num ) > 4 ) && ( temp_arr_ptr->size() < 5 );
              ++match_num ) {
            temp_arr_ptr->clear();
            temp_arr_ptr->push_back( combo_ptr.at( match_num ) );
            for ( unsigned match_subnum = match_num + 1; match_subnum < combo_ptr.size(); ++match_subnum ) {
                if ( combo_ptr.at( match_num ).getSuitNum() == combo_ptr.at( match_subnum ).getSuitNum() )
                    temp_arr_ptr->push_back( combo_ptr.at( match_subnum ) );
            }
        }

        combo_val = 0;
        for ( auto const & card : *temp_arr_ptr ) {
            combo_val |= ( card.getValueNum() & Card::valueMask );
        }
        res = matchStrait( combo_val );

        // для проверки разницы в скорасти вычисления
        //                    if (temp_arr_ptr->size() > 4)
        //                    {
        //                        temp_arr_ptr = sortCards(*temp_arr_ptr);

        //                        for (unsigned match_num = 0; (combo_ptr.size() - match_num) >= 5; ++match_num)
        //                        {
        //                            if ((temp_arr_ptr->at(match_num).getValueNum() + 1 == temp_arr_ptr->at(match_num +
        //                            1).getValueNum()) &&
        //                                (temp_arr_ptr->at(match_num).getValueNum() + 2 == temp_arr_ptr->at(match_num +
        //                                2).getValueNum()) && (temp_arr_ptr->at(match_num).getValueNum() + 3 ==
        //                                temp_arr_ptr->at(match_num + 3).getValueNum()) &&
        //                                (temp_arr_ptr->at(match_num).getValueNum() + 4 == temp_arr_ptr->at(match_num +
        //                                4).getValueNum())) res = true;
        //                            else if (temp_arr_ptr->at(match_num).getValueNum() == 0)
        //                            {
        //                                if ((temp_arr_ptr->at(match_num).getValueNum() + 1 ==
        //                                temp_arr_ptr->at(match_num + 1).getValueNum()) &&
        //                                    (temp_arr_ptr->at(match_num).getValueNum() + 2 ==
        //                                    temp_arr_ptr->at(match_num + 2).getValueNum()) &&
        //                                    (temp_arr_ptr->at(match_num).getValueNum() + 3 ==
        //                                    temp_arr_ptr->at(match_num + 3).getValueNum()) &&
        //                                    (temp_arr_ptr->at(match_num).getValueNum() + 12 ==
        //                                    temp_arr_ptr->back().getValueNum())) res = true;
        //                            }
        //                        }
        //                    }
    }
    return res;
}
//---------------------------------------------------------------------------------------------------------------------------
//проверка на карэ
bool HandStrength::matchKare( const std::vector< Card > & combo_ptr ) const {
    bool res = false;
    int match_true;

    for ( unsigned count = 0; ( combo_ptr.size() - count ) > 3; ++count ) {
        match_true = 0;

        for ( unsigned subcount = count + 1; subcount < combo_ptr.size(); ++subcount ) {
            if ( combo_ptr.at( count ).getValueNum() == combo_ptr.at( subcount ).getValueNum() )
                ++match_true;
        }

        if ( match_true > 2 ) {
            res = true;
            break;
        }
    }

    return res;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на фулл-хаус
bool HandStrength::matchFullhouse( const std::vector< Card > & combo_ptr ) const {
    auto temp_arr_ptr = std::make_unique< std::vector< Card > >( *sortCards( combo_ptr ) );
    bool res = false;

    for ( unsigned count = 0; ( temp_arr_ptr->size() - count ) > 2; ++count ) {
        if ( temp_arr_ptr->at( count ).getValueNum() == temp_arr_ptr->at( count + 1 ).getValueNum() &&
             temp_arr_ptr->at( count ).getValueNum() == temp_arr_ptr->at( count + 2 ).getValueNum() ) {
            temp_arr_ptr->erase( temp_arr_ptr->begin() + count, temp_arr_ptr->begin() + count + 3 );
            for ( unsigned subcount = 0; ( temp_arr_ptr->size() - subcount ) >= 2; ++subcount ) {
                if ( temp_arr_ptr->at( subcount ).getValueNum() == temp_arr_ptr->at( subcount + 1 ).getValueNum() ) {
                    res = true;
                    break;
                }
            }
            break;
        }
    }
    return res;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на флеш
bool HandStrength::matchFlush( const std::vector< Card > & combo_ptr, const uint32_t & combo ) const {
    bool res = false;
    uint8_t combo_suit = combo & Card::suitMask;

    if ( combo_suit == 0x1 || combo_suit == 0x2 || combo_suit == 0x4 || combo_suit == 0x8 )
        res = true;
    else if ( ( combo_ptr.size() == 6 &&
                ( combo_suit == 0x7 || combo_suit == 0xe || combo_suit == 0xd || combo_suit == 0xb ) ) ||
              ( combo_ptr.size() == 7 && combo_suit == 0xf ) )
        ;
    else {
        for ( unsigned match_num = 0; ( combo_ptr.size() - match_num ) > 4; ++match_num ) {
            unsigned match_true = 0, match_false = 0;
            for ( unsigned match_subnum = match_num + 1; match_subnum < combo_ptr.size(); ++match_subnum ) {
                if ( combo_ptr.at( match_num ).getSuitNum() == combo_ptr.at( match_subnum ).getSuitNum() )
                    ++match_true;
                else {
                    ++match_false;
                    if ( ( combo_ptr.size() - match_num - match_false ) < 5 )
                        break;
                }
            }

            if ( match_true > 3 ) {
                res = true;
                break;
            }
        }
    }

    return res;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на стрит
bool HandStrength::matchStrait( const uint32_t & combo ) const {
    return ( ( combo & 0x1F000000 ) == 0x1F000000 || ( combo & 0xF800000 ) == 0xF800000 ||
             ( combo & 0x7C00000 ) == 0x7C00000 || ( combo & 0x3E00000 ) == 0x3E00000 ||
             ( combo & 0x1F00000 ) == 0x1F00000 || ( combo & 0xF80000 ) == 0xF80000 ||
             ( combo & 0x7C0000 ) == 0x7C0000 || ( combo & 0x3E0000 ) == 0x3E0000 || ( combo & 0x1F0000 ) == 0x1F0000 ||
             ( combo & 0x100F0000 ) == 0x100F0000 );
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на сет
bool HandStrength::matchSet( const std::vector< Card > & combo_ptr ) const {
    std::unique_ptr< std::vector< Card > > temp_arr_ptr( new std::vector< Card > );
    temp_arr_ptr = sortCards( combo_ptr );
    bool res = false;

    for ( unsigned count = 0; ( temp_arr_ptr->size() - count ) >= 3; ++count ) {
        if ( temp_arr_ptr->at( count ).getValueNum() == temp_arr_ptr->at( count + 1 ).getValueNum() &&
             temp_arr_ptr->at( count ).getValueNum() == temp_arr_ptr->at( count + 2 ).getValueNum() )
            res = true;
    }

    return res;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на две пары
bool HandStrength::matchTwopairs( const std::vector< Card > & combo_ptr ) const {
    std::unique_ptr< std::vector< Card > > temp_arr_ptr( new std::vector< Card > );
    temp_arr_ptr = sortCards( combo_ptr );
    bool res = false;

    for ( unsigned count = 0; ( temp_arr_ptr->size() - count ) >= 4; ++count ) {
        if ( temp_arr_ptr->at( count ).getValueNum() == temp_arr_ptr->at( count + 1 ).getValueNum() ) {
            temp_arr_ptr->erase( temp_arr_ptr->begin() + count, temp_arr_ptr->begin() + count + 2 );
            for ( unsigned subcount = 0; ( temp_arr_ptr->size() - subcount ) >= 2; ++subcount ) {
                if ( temp_arr_ptr->at( subcount ).getValueNum() == temp_arr_ptr->at( subcount + 1 ).getValueNum() )
                    res = true;
            }
        }
    }

    return res;
}
//---------------------------------------------------------------------------------------------------------------------------
std::unique_ptr< std::vector< Card > > HandStrength::sortCards( const std::vector< Card > & combo_ptr ) const {
    auto temp_arr_ptr = std::make_unique< std::vector< Card > >( combo_ptr );
    //    *temp_arr_ptr = *combo_ptr;

    Card temp_card;

    for ( unsigned count = 0; count < temp_arr_ptr->size(); ++count ) {
        for ( unsigned subcount = count + 1; subcount < temp_arr_ptr->size(); ++subcount ) {
            if ( temp_arr_ptr->at( count ) > temp_arr_ptr->at( subcount ) ) {
                temp_card = temp_arr_ptr->at( count );
                temp_arr_ptr->at( count ) = temp_arr_ptr->at( subcount );
                temp_arr_ptr->at( subcount ) = temp_card;
            }
        }
    }

    return temp_arr_ptr;
}
//---------------------------------------------------------------------------------------------------------------------------
void HandStrengthList::accumulate( const Hand & hand, const Board & board ) {
    HandStrength pl_strangth{hand, board};
    switch ( pl_strangth.getCurrStrength() ) {
    case HandStrength::strength::HIGHT:
        ++hight;
        break;
    case HandStrength::strength::PAIR:
        ++pair;
        break;
    case HandStrength::strength::SET:
        ++set;
        break;
    case HandStrength::strength::TWO_PAIRS:
        ++twopair;
        break;
    case HandStrength::strength::STRAIT:
        ++strait;
        break;
    case HandStrength::strength::FLUSH:
        ++flush;
        break;
    case HandStrength::strength::FULL_HOUSE:
        ++fullhouse;
        break;
    case HandStrength::strength::STRAIT_FLUSH:
        ++straitflush;
        break;
    case HandStrength::strength::KARE:
        ++kare;
        break;
    case HandStrength::strength::NODEF:
        assert( false && "is no define strength" );
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void HandStrengthList::print() {
    if ( getSum() == 0 )
        calcPercents();
    assert( getSum() > 0 && "empty counter values" );
    std::cout << "hi : "
              << "\t\t\t" << hight << "\t" << hightP * 100 << "%" << std::endl;
    std::cout << "pairs : "
              << "\t\t" << pair << "\t" << pairP * 100 << "%" << std::endl;
    std::cout << "sets : "
              << "\t\t" << set << "\t" << setP * 100 << "%" << std::endl;
    std::cout << "two pairs : "
              << "\t\t" << twopair << "\t" << twopairP * 100 << "%" << std::endl;
    std::cout << "straits : "
              << "\t\t" << strait << "\t" << straitP * 100 << "%" << std::endl;
    std::cout << "FLUSHes : "
              << "\t\t" << flush << "\t" << flushP * 100 << "%" << std::endl;
    std::cout << "fullhouses : "
              << "\t\t" << fullhouse << "\t" << fullhouseP * 100 << "%" << std::endl;
    std::cout << "straitFLUSHes : "
              << "\t" << straitflush << "\t" << straitflushP * 100 << "%" << std::endl;
    std::cout << "kares : "
              << "\t\t" << kare << "\t" << kareP * 100 << "%" << std::endl;
    std::cout << "sum_cycle : " << getSum() << std::endl;
}
//---------------------------------------------------------------------------------------------------------------------------
unsigned long long HandStrengthList::getSum() const {
    return ( hight + pair + set + twopair + strait + flush + fullhouse + straitflush + kare );
}
//---------------------------------------------------------------------------------------------------------------------------
void HandStrengthList::calcPercents() {
    hightP = static_cast< float >( hight ) / getSum();
    pairP = static_cast< float >( pair ) / getSum();
    setP = static_cast< float >( set ) / getSum();
    twopairP = static_cast< float >( twopair ) / getSum();
    straitP = static_cast< float >( strait ) / getSum();
    flushP = static_cast< float >( flush ) / getSum();
    fullhouseP = static_cast< float >( fullhouse ) / getSum();
    straitflushP = static_cast< float >( straitflush ) / getSum();
    kareP = static_cast< float >( kare ) / getSum();
}

} // namespace lp