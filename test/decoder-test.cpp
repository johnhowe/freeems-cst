/**
 * @file       decoder-test.cpp
 * @headerfile
 * @author     sean
 * @brief      fe::decoder tests
 *
 * freeems-cst: freeems 'comms smoke test'
 *
 * Copyright (C) 2010,2011 Sean Stasiak sstasiak at gmail
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

/* boost::test */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE decoder-tests
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>

#include "fe.h"
using namespace std;
using namespace fe;

BOOST_AUTO_TEST_CASE( decode_nothing )
{
    vector<uint8_t> const pkt( 0 );
    auto_ptr<vector<uint8_t> const> const v( endec::decode( pkt ) ) ;

    BOOST_REQUIRE( v.get() != 0 );          /**< exists .. */
    BOOST_CHECK( v->empty() );              /**< but empty */
}

BOOST_AUTO_TEST_CASE( decode_something )
{
    uint8_t const data[] = { 0x00, 0x01, 0x02 };
    vector<uint8_t> const pkt( data, data+EDIM(data) );
    auto_ptr<vector<uint8_t> const> const v( endec::decode( pkt ) ) ;

    BOOST_REQUIRE( v.get() != 0 );

    /* nothing was encoded, ends up being a copy straight across */
    BOOST_CHECK_EQUAL_COLLECTIONS( v->begin(), v->end(),
                                   pkt.begin(), pkt.end() );
}

BOOST_AUTO_TEST_CASE( decode_STX_only )
{
    uint8_t const data[] = { endec::ESC, (endec::STX ^ 0xFF) };
    vector<uint8_t> const pkt( data, data+EDIM(data) );
    auto_ptr<vector<uint8_t> const> const v( endec::decode( pkt ) ) ;

    BOOST_REQUIRE( v.get() != 0 );

    uint8_t const expected[] = { endec::STX };
    BOOST_CHECK_EQUAL_COLLECTIONS( v->begin(), v->end(),
                                   expected, expected+sizeof(expected) );
}

BOOST_AUTO_TEST_CASE( decode_ETX_only )
{
    uint8_t const data[] = { endec::ESC, (endec::ETX ^ 0xFF) };
    vector<uint8_t> const pkt( data, data+EDIM(data) );
    auto_ptr<vector<uint8_t> const> const v( endec::decode( pkt ) ) ;

    BOOST_REQUIRE( v.get() != 0 );

    uint8_t const expected[] = { endec::ETX };
    BOOST_CHECK_EQUAL_COLLECTIONS( v->begin(), v->end(),
                                   expected, expected+sizeof(expected) );
}

BOOST_AUTO_TEST_CASE( decode_ESC_only )
{
    uint8_t const data[] = { endec::ESC, (endec::ESC ^ 0xFF) };
    vector<uint8_t> const pkt( data, data+EDIM(data) );
    auto_ptr<vector<uint8_t> const> const v( endec::decode( pkt ) ) ;

    BOOST_REQUIRE( v.get() != 0 );

    uint8_t const expected[] = { endec::ESC };
    BOOST_CHECK_EQUAL_COLLECTIONS( v->begin(), v->end(),
                                   expected, expected+sizeof(expected) );
}

BOOST_AUTO_TEST_CASE( decode_all_framed_by_junk )
{
    uint8_t const data[] = { 0x11,
                             endec::ESC, (endec::ESC ^ 0xFF),
                             endec::ESC, (endec::ETX ^ 0xFF),
                             0x66,
                             endec::ESC, (endec::STX ^ 0xFF),
                             0x22, 0x33 };
    vector<uint8_t> const pkt( data, data+EDIM(data) );
    auto_ptr<vector<uint8_t> const> const v( endec::decode( pkt ) ) ;

    BOOST_REQUIRE( v.get() != 0 );

    uint8_t const expected[] = { 0x11,
                                 endec::ESC,
                                 endec::ETX,
                                 0x66,
                                 endec::STX,
                                 0x22, 0x33 };
    BOOST_CHECK_EQUAL_COLLECTIONS( v->begin(), v->end(),
                                   expected, expected+sizeof(expected) );
}

BOOST_AUTO_TEST_CASE( throw_on_bad_byte_after_ESC )
{
    uint8_t const data[] = { endec::ESC, (0x99 ^ 0xFF) };
    vector<uint8_t> const pkt( data, data+EDIM(data) );

    BOOST_REQUIRE_THROW(
      auto_ptr<vector<uint8_t> const> const v( endec::decode( pkt ) ),
      escxor_error ) ;
}
