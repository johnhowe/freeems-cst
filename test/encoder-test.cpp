/**
 * @file       encoder-test.cpp
 * @headerfile
 * @author     sean
 * @brief      fe::encoder tests
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
#define BOOST_TEST_MODULE encoder-tests
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>

/* fe:: */
#include "fe.h"
using namespace std;
using namespace fe;

BOOST_AUTO_TEST_CASE( encode_nothing )
{
    vector<uint8_t> const pkt( 0 );
    auto_ptr<vector<uint8_t> const> const v( encode( pkt ) ) ;

    BOOST_REQUIRE( v.get() != 0 );          /**< exists .. */
    BOOST_CHECK( v->empty() );              /**< but empty */
}

BOOST_AUTO_TEST_CASE( encode_something )
{
    uint8_t const data[] = { 0x00, 0x01, 0x02 };
    vector<uint8_t> const pkt( data, data+sizeof(data) );
    auto_ptr<vector<uint8_t> const> const v( encode( pkt ) ) ;

    BOOST_REQUIRE( v.get() != 0 );

    /* nothing was encoded, ends up being a copy straight across */
    BOOST_CHECK_EQUAL_COLLECTIONS( v->begin(), v->end(),
                                   pkt.begin(), pkt.end() );
}

BOOST_AUTO_TEST_CASE( encode_STX_only )
{
    uint8_t const data[] = { STX };
    vector<uint8_t> const pkt( data, data+sizeof(data) );
    auto_ptr<vector<uint8_t> const> const v( encode( pkt ) ) ;

    BOOST_REQUIRE( v.get() != 0 );

    uint8_t const expected[] = { ESC, (STX ^ 0xFF) };
    BOOST_CHECK_EQUAL_COLLECTIONS( v->begin(), v->end(),
                                   expected, expected+sizeof(expected) );
}

BOOST_AUTO_TEST_CASE( encode_ETX_only )
{
    uint8_t const data[] = { ETX };
    vector<uint8_t> const pkt( data, data+sizeof(data) );
    auto_ptr<vector<uint8_t> const> const v( encode( pkt ) ) ;

    BOOST_REQUIRE( v.get() != 0 );

    uint8_t const expected[] = { ESC, (ETX ^ 0xFF) };
    BOOST_CHECK_EQUAL_COLLECTIONS( v->begin(), v->end(),
                                   expected, expected+sizeof(expected) );
}

BOOST_AUTO_TEST_CASE( encode_ESC_only )
{
    uint8_t const data[] = { ESC };
    vector<uint8_t> const pkt( data, data+sizeof(data) );
    auto_ptr<vector<uint8_t> const> const v( encode( pkt ) ) ;

    BOOST_REQUIRE( v.get() != 0 );

    uint8_t const expected[] = { ESC, (ESC ^ 0xFF) };
    BOOST_CHECK_EQUAL_COLLECTIONS( v->begin(), v->end(),
                                   expected, expected+sizeof(expected) );
}

BOOST_AUTO_TEST_CASE( encode_all_framed_by_junk )
{
    uint8_t const data[] = { 0x11,
                             ESC,
                             ETX,
                             STX,
                             0x22, 0x33 };
    vector<uint8_t> const pkt( data, data+sizeof(data) );
    auto_ptr<vector<uint8_t> const> const v( encode( pkt ) ) ;

    BOOST_REQUIRE( v.get() != 0 );

    uint8_t const expected[] = { 0x11,
                                 ESC, (ESC ^ 0xFF),
                                 ESC, (ETX ^ 0xFF),
                                 ESC, (STX ^ 0xFF),
                                 0x22, 0x33 };
    BOOST_CHECK_EQUAL_COLLECTIONS( v->begin(), v->end(),
                                   expected, expected+sizeof(expected) );
}
