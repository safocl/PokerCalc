#include "handstrength.h"
#include "Board.h"
#include "Card.h"
#include "Hand.h"
#include <cassert>
#include <iostream>
#include <numeric>

namespace lp {

// HandStrengthList::HandStrengthList()
//    : hightP( 0 ), pairP( 0 ), twopairP( 0 ), setP( 0 ), straitP( 0 ), flushP( 0 ), fullhouseP( 0 ), kareP( 0 ),
//      straitflushP( 0 ) {}

// HandStrengthList::HandStrengthList( const HandStrengthList & other )
//    : hightP( other.hightP ), pairP( other.pairP ), twopairP( other.twopairP ), setP( other.setP ),
//      straitP( other.straitP ), flushP( other.flushP ), fullhouseP( other.fullhouseP ), kareP( other.kareP ),
//      straitflushP( other.straitflushP ) {}
//---------------------------------------------------------------------------------------------------------------------------
// HandStrength::HandStrength( const HandStrength & other )
//    : hight( other.hight ), pair( other.pair ), twoPairs( other.twoPairs ), set( other.set ), strait( other.strait ),
//      flush( other.flush ), fullHouse( other.fullHouse ), kare( other.kare ), straitFlush( other.straitFlush ),
//      fd( other.fd ), sd( other.sd ), gutShot( other.gutShot ), oneOverCard( other.oneOverCard ),
//      twoOverCards( other.twoOverCards ), backdorFD( other.backdorFD ), backdorSD( other.backdorSD ),
//      backdorGutShot( other.backdorGutShot ){};
//---------------------------------------------------------------------------------------------------------------------------
HandStrength::HandStrength( const Hand & __hand, const Board & __board )
/*: hight( false ), pair( false ), twoPairs( false ), set( false ), strait( false ), flush( false ),
  fullHouse( false ), kare( false ), straitFlush( false ), fd( false ), sd( false ), gutShot( false ),
  oneOverCard( false ), twoOverCards( false ), backdorFD( false ), backdorSD( false ), backdorGutShot( false )*/
{
    calcCurrStrength( __hand, __board );
}
//---------------------------------------------------------------------------------------------------------------------------
HandStrength::HandStrength( const std::vector< Card > & __combo )
    : hight( false ), pair( false ), twoPairs( false ), set( false ), strait( false ), flush( false ),
      fullHouse( false ), kare( false ), straitFlush( false ), fd( false ), sd( false ), gutShot( false ),
      oneOverCard( false ), twoOverCards( false ), backdorFD( false ), backdorSD( false ), backdorGutShot( false ) {
    calcCurrStrength( __combo );
}
//---------------------------------------------------------------------------------------------------------------------------
void HandStrength::calcCurrStrength( const Hand & __hand, const Board & __board ) {
    if ( __board.getBoard().size() < 3 ) {
        assert( __board.getBoard().size() == 0 && "invalid board" );

        // проверка на пару, если борд пуст
        if ( __hand.getLCard().getValueNum() == __hand.getRCard().getValueNum() ) {
            pair = true;
        }
    } else {
        assert( __board.getBoard().size() < 6 && "invalid board" );
        assert( ( __hand.getLCard().getValueNum() != 0 && __hand.getLCard().getSuitNum() != 0 ) &&
                ( __hand.getRCard().getValueNum() != 0 && __hand.getRCard().getSuitNum() != 0 ) &&
                "invalid hand initialization" );
        std::unique_ptr< std::vector< Card > > comboPtr( new std::vector< Card > );
        comboPtr->reserve( __board.getBoard().size() + 2 );
        std::copy( __board.getBoard().cbegin(), __board.getBoard().cend(), comboPtr->begin() );
        comboPtr->push_back( __hand.getLCard() );
        comboPtr->push_back( __hand.getRCard() );

        uint32_t combo = 0;
        combo = std::accumulate( __board.getBoard().cbegin(), __board.getBoard().cend(), combo,
                                 []( uint32_t combo, const Card & card ) {
                                     combo |= ( card.getValueNum() | card.getSuitNum() );
                                     return combo;
                                 } );

        //        for ( auto const & card : __board.getBoard() ) {
        //            combo |= ( card.getValueNum() | card.getSuitNum() );
        //        }

        combo |= ( __hand.getLCard().getValueNum() | __hand.getLCard().getSuitNum() ) |
                 ( __hand.getRCard().getValueNum() | __hand.getRCard().getSuitNum() );

        // проверка на стрит-флеш
        if ( matchStraitflush( *comboPtr, combo ) )
            straitFlush = true;

        // проверка на карэ
        else if ( matchKare( *comboPtr ) )
            kare = true;

        // проверка на фулл-хаус
        else if ( matchFullhouse( *comboPtr ) )
            fullHouse = true;

        // проверка на флеш
        else if ( matchFlush( *comboPtr, combo ) )
            flush = true;

        // проверка на стрит
        else if ( matchStrait( combo ) )
            strait = true;

        // проверка на сет
        else if ( matchSet( *comboPtr ) )
            set = true;

        // проверка на две пары
        else if ( matchTwopairs( *comboPtr ) )
            twoPairs = true;

        // проверка на пару
        else if ( [&__board, &__hand]() {
                      for ( auto const & el : __board.getBoard() ) {
                          if ( __hand.getLCard().getValueNum() == el.getValueNum() ||
                               __hand.getRCard().getValueNum() == el.getValueNum() ) {
                              return true;
                          }
                      }
                      return false;
                  }() ||
                  __hand.getLCard().getValueNum() == __hand.getRCard().getValueNum() )
            pair = true;
        else
            hight = true;
    } //проверка, если борд не пуст

    //    return strength{finishedStrength::HIGHT, drawStrength::NODEF};
}

void HandStrength::calcCurrStrength( const std::vector< Card > & __combo ) {
    assert( __combo.size() < 6 && "invalid board" );
    if ( __combo.size() < 5 ) {
        assert( __combo.size() == 2 && "invalid board" );

        // проверка на пару, если борд пуст
        if ( __combo.at( 0 ).getValueNum() == __combo.at( 1 ).getValueNum() ) {
            pair = true;
        }
    } else {

        uint32_t comboN = 0;
        comboN = std::accumulate( __combo.cbegin(), __combo.cend(), comboN, []( uint32_t combo, const Card & card ) {
            combo |= ( card.getValueNum() | card.getSuitNum() );
            return combo;
        } );
        //        for ( auto const & card : __combo ) {
        //            comboN |= ( card.getValueNum() | card.getSuitNum() );
        //        }

        // проверка на стрит-флеш
        if ( matchStraitflush( __combo, comboN ) )
            straitFlush = true;

        // проверка на карэ
        else if ( matchKare( __combo ) )
            kare = true;

        // проверка на фулл-хаус
        else if ( matchFullhouse( __combo ) )
            fullHouse = true;

        // проверка на флеш
        else if ( matchFlush( __combo, comboN ) )
            flush = true;

        // проверка на стрит
        else if ( matchStrait( comboN ) )
            strait = true;

        // проверка на сет
        else if ( matchSet( __combo ) )
            set = true;

        // проверка на две пары
        else if ( matchTwopairs( __combo ) )
            twoPairs = true;

        // проверка на пару
        else if ( []( const std::vector< Card > & combo ) {
                      for ( unsigned short i = 0; i < combo.size(); ++i ) {
                          for ( unsigned short j = i - 1; j < combo.size(); ++j ) {
                              if ( combo.at( i ).getValueNum() == combo.at( j ).getValueNum() ) {
                                  return true;
                              }
                          }
                      }
                      return false;
                  }( __combo ) )
            pair = true;
        else
            hight = true;
    } //проверка, если борд не пуст

    //    return strength{finishedStrength::HIGHT, drawStrength::NODEF};
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на стрит-флеш
bool HandStrength::matchStraitflush( const std::vector< Card > & combo, const uint32_t & comboN ) {
    bool res = false;
    uint32_t combo_val = comboN & Card::valueMask;
    uint8_t combo_suit = comboN & Card::suitMask;
    if ( matchStrait( combo_val ) &&
         ( combo_suit == 0x1 || combo_suit == 0x2 || combo_suit == 0x4 || combo_suit == 0x8 ) )
        res = true;
    else if ( ( combo.size() == 6 &&
                ( combo_suit == 0x7 || combo_suit == 0xe || combo_suit == 0xd || combo_suit == 0xb ) ) ||
              ( combo.size() == 7 && combo_suit == 0xf ) )
        ;
    else if ( matchStrait( combo_val ) ) {

        std::unique_ptr< std::vector< Card > > temp_arr_ptr( new std::vector< Card > );
        temp_arr_ptr->reserve( combo.size() );

        for ( unsigned match_num = 0; ( ( combo.size() - match_num ) > 4 ) && ( temp_arr_ptr->size() < 5 );
              ++match_num ) {
            temp_arr_ptr->clear();
            temp_arr_ptr->push_back( combo.at( match_num ) );
            for ( unsigned match_subnum = match_num + 1; match_subnum < combo.size(); ++match_subnum ) {
                if ( combo.at( match_num ).getSuitNum() == combo.at( match_subnum ).getSuitNum() )
                    temp_arr_ptr->push_back( combo.at( match_subnum ) );
            }
        }

        combo_val = std::accumulate( temp_arr_ptr->cbegin(), temp_arr_ptr->cend(), combo_val,
                                     []( uint32_t combo, const Card & card ) {
                                         combo |= ( card.getValueNum() & Card::valueMask );
                                         return combo;
                                     } );
        //        for ( auto const & card : *temp_arr_ptr ) {
        //            combo_val |= ( card.getValueNum() & Card::valueMask );
        //        }

        res = matchStrait( combo_val );

        // для проверки разницы в скорасти вычисления
        //                    if (temp_arr_ptr->size() > 4)
        //                    {
        //                        temp_arr_ptr = sortCards(*temp_arr_ptr);

        //                        for (unsigned match_num = 0; (comboPtr.size() - match_num) >= 5; ++match_num)
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
bool HandStrength::matchKare( const std::vector< Card > & combo ) {
    bool res = false;

    for ( uint8_t count = 0; ( combo.size() - count ) > 3; ++count ) {
        uint8_t match_true = 0;

        for ( uint8_t subcount = count + 1; subcount < combo.size(); ++subcount ) {
            if ( combo.at( count ).getValueNum() == combo.at( subcount ).getValueNum() )
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
bool HandStrength::matchFullhouse( const std::vector< Card > & combo ) {
    auto tmpCombo = std::make_unique< std::vector< Card > >( sortCards( combo ) );
    bool res = false;

    for ( uint8_t count = 0; ( tmpCombo->size() - count ) > 2; ++count ) {
        if ( tmpCombo->at( count ).getValueNum() == tmpCombo->at( count + 1 ).getValueNum() &&
             tmpCombo->at( count ).getValueNum() == tmpCombo->at( count + 2 ).getValueNum() ) {
            tmpCombo->erase( tmpCombo->begin() + count, tmpCombo->begin() + count + 3 );
            for ( unsigned subcount = 0; ( tmpCombo->size() - subcount ) >= 2; ++subcount ) {
                if ( tmpCombo->at( subcount ).getValueNum() == tmpCombo->at( subcount + 1 ).getValueNum() ) {
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
bool HandStrength::matchFlush( const std::vector< Card > & combo, const uint32_t & comboN ) {
    bool res = false;
    uint8_t combo_suit = comboN & Card::suitMask;

    if ( combo_suit == 0x1 || combo_suit == 0x2 || combo_suit == 0x4 || combo_suit == 0x8 )
        res = true;
    else if ( ( combo.size() == 6 &&
                ( combo_suit == 0x7 || combo_suit == 0xe || combo_suit == 0xd || combo_suit == 0xb ) ) ||
              ( combo.size() == 7 && combo_suit == 0xf ) )
        ;
    else {
        for ( uint8_t match_num = 0; ( combo.size() - match_num ) > 4; ++match_num ) {
            uint8_t match_true = 0, match_false = 0;
            for ( uint8_t match_subnum = match_num + 1; match_subnum < combo.size(); ++match_subnum ) {
                if ( combo.at( match_num ).getSuitNum() == combo.at( match_subnum ).getSuitNum() )
                    ++match_true;
                else {
                    ++match_false;
                    if ( ( combo.size() - match_num - match_false ) < 5 )
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
bool HandStrength::matchStrait( const uint32_t & comboN ) {
    return ( ( comboN & 0x1F000000 ) == 0x1F000000 || ( comboN & 0xF800000 ) == 0xF800000 ||
             ( comboN & 0x7C00000 ) == 0x7C00000 || ( comboN & 0x3E00000 ) == 0x3E00000 ||
             ( comboN & 0x1F00000 ) == 0x1F00000 || ( comboN & 0xF80000 ) == 0xF80000 ||
             ( comboN & 0x7C0000 ) == 0x7C0000 || ( comboN & 0x3E0000 ) == 0x3E0000 ||
             ( comboN & 0x1F0000 ) == 0x1F0000 || ( comboN & 0x100F0000 ) == 0x100F0000 );
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на сет
bool HandStrength::matchSet( const std::vector< Card > & combo ) {
    auto tmpCombo = std::make_unique< std::vector< Card > >( sortCards( combo ) );
    bool res = false;

    for ( uint8_t count = 0; ( tmpCombo->size() - count ) >= 3; ++count ) {
        if ( tmpCombo->at( count ).getValueNum() == tmpCombo->at( count + 1 ).getValueNum() &&
             tmpCombo->at( count ).getValueNum() == tmpCombo->at( count + 2 ).getValueNum() )
            res = true;
    }

    return res;
}
//---------------------------------------------------------------------------------------------------------------------------
// проверка на две пары
bool HandStrength::matchTwopairs( const std::vector< Card > & combo ) {
    auto tmpCombo = std::make_unique< std::vector< Card > >( sortCards( combo ) );

    for ( uint8_t count = 0; ( tmpCombo->size() - count ) >= 4; ++count ) {
        if ( tmpCombo->at( count ).getValueNum() == tmpCombo->at( count + 1 ).getValueNum() ) {
            tmpCombo->erase( tmpCombo->begin() + count, tmpCombo->begin() + count + 2 );
            for ( uint8_t subcount = 0; ( tmpCombo->size() - subcount ) >= 2; ++subcount ) {
                if ( tmpCombo->at( subcount ).getValueNum() == tmpCombo->at( subcount + 1 ).getValueNum() )
                    return true;
            }
        }
    }

    return false;
}
//---------------------------------------------------------------------------------------------------------------------------
std::vector< Card > HandStrength::sortCards( std::vector< Card > combo ) {
    Card temp_card;

    for ( uint8_t count = 0; count < combo.size(); ++count ) {
        for ( uint8_t subcount = count + 1; subcount < combo.size(); ++subcount ) {
            if ( combo.at( count ) > combo.at( subcount ) ) {
                temp_card = combo.at( count );
                combo.at( count ) = combo.at( subcount );
                combo.at( subcount ) = temp_card;
            }
        }
    }

    return combo;
}
//---------------------------------------------------------------------------------------------------------------------------
bool HandStrength::containHight() const { return hight; }
//---------------------------------------------------------------------------------------------------------------------------
bool HandStrength::containPair() const { return pair; }
//---------------------------------------------------------------------------------------------------------------------------
bool HandStrength::containTwoPairs() const { return twoPairs; }
//---------------------------------------------------------------------------------------------------------------------------
bool HandStrength::containSet() const { return set; }
//---------------------------------------------------------------------------------------------------------------------------
bool HandStrength::containStrait() const { return strait; }
//---------------------------------------------------------------------------------------------------------------------------
bool HandStrength::containFlush() const { return flush; }
//---------------------------------------------------------------------------------------------------------------------------
bool HandStrength::containFullHouse() const { return fullHouse; }
//---------------------------------------------------------------------------------------------------------------------------
bool HandStrength::containKare() const { return kare; }
//---------------------------------------------------------------------------------------------------------------------------
bool HandStrength::containStraitFlush() const { return straitFlush; }
//---------------------------------------------------------------------------------------------------------------------------
bool HandStrength::containFD() const { return fd; }
//---------------------------------------------------------------------------------------------------------------------------
bool HandStrength::containSD() const { return sd; }
//---------------------------------------------------------------------------------------------------------------------------
bool HandStrength::containGutShot() const { return gutShot; }
//---------------------------------------------------------------------------------------------------------------------------
bool HandStrength::containOneOverCard() const { return oneOverCard; }
//---------------------------------------------------------------------------------------------------------------------------
bool HandStrength::containTwoOverCards() const { return twoOverCards; }
//---------------------------------------------------------------------------------------------------------------------------
bool HandStrength::containBackdorFD() const { return backdorFD; }
//---------------------------------------------------------------------------------------------------------------------------
bool HandStrength::containBackdorSD() const { return backdorSD; }
//---------------------------------------------------------------------------------------------------------------------------
bool HandStrength::containBackdorGutShot() const { return backdorGutShot; }
//---------------------------------------------------------------------------------------------------------------------------
// void HandStrengthList::print() {
//    if ( getSum() == 0 )
//        calcPercents();
//    assert( getSum() > 0 && "empty counter values" );
//    std::cout << "hi : "
//              << "\t\t\t" << hight << "\t" << hightP * 100 << "%" << std::endl;
//    std::cout << "pairs : "
//              << "\t\t" << pair << "\t" << pairP * 100 << "%" << std::endl;
//    std::cout << "sets : "
//              << "\t\t" << set << "\t" << setP * 100 << "%" << std::endl;
//    std::cout << "two pairs : "
//              << "\t\t" << twopair << "\t" << twopairP * 100 << "%" << std::endl;
//    std::cout << "straits : "
//              << "\t\t" << strait << "\t" << straitP * 100 << "%" << std::endl;
//    std::cout << "FLUSHes : "
//              << "\t\t" << flush << "\t" << flushP * 100 << "%" << std::endl;
//    std::cout << "fullhouses : "
//              << "\t\t" << fullhouse << "\t" << fullhouseP * 100 << "%" << std::endl;
//    std::cout << "straitFLUSHes : "
//              << "\t" << straitflush << "\t" << straitflushP * 100 << "%" << std::endl;
//    std::cout << "kares : "
//              << "\t\t" << kare << "\t" << kareP * 100 << "%" << std::endl;
//    std::cout << "sum_cycle : " << getSum() << std::endl;
//}
//---------------------------------------------------------------------------------------------------------------------------
// unsigned long long HandStrengthList::getSum() const { return 0 /* implementztion  */; }
//---------------------------------------------------------------------------------------------------------------------------
// void HandStrengthList::calcPercents() {
//    hightP = static_cast< float >( hight ) / getSum();
//    pairP = static_cast< float >( pair ) / getSum();
//    setP = static_cast< float >( set ) / getSum();
//    twopairP = static_cast< float >( twopair ) / getSum();
//    straitP = static_cast< float >( strait ) / getSum();
//    flushP = static_cast< float >( flush ) / getSum();
//    fullhouseP = static_cast< float >( fullhouse ) / getSum();
//    straitflushP = static_cast< float >( straitflush ) / getSum();
//    kareP = static_cast< float >( kare ) / getSum();
//}

} // namespace lp