/**
 * @file       psp-test.cpp
 * @headerfile
 * @author     sean
 * @brief      fe::posix_serial_port tests
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
#define BOOST_TEST_MODULE psp-tests
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>

/* std:: */
#include <string>

#include "fe.h"
using namespace std;
using namespace fe;

BOOST_AUTO_TEST_CASE( ctor_allows_any_path )
{
    /* bad paths are caught on open attempt */
    posix_serial_port psp0( "path" );
    posix_serial_port psp1( "" );
    posix_serial_port psp2( "/dev/null" );
}

BOOST_AUTO_TEST_CASE( get_path )
{
    posix_serial_port psp( "path" );

    string s;
    psp.get_path( s );

    BOOST_CHECK( s == "path" );
}

BOOST_AUTO_TEST_CASE( multiple_opens_allowed )
{
    /* requires a valid serial path, not sure how
       to do this generically. everyone's setup is
       different. I wish there was a way that a test
       (this one) could be marked explicit like
       NUnit allows */
    posix_serial_port psp( "/dev/ttyS0" );
    BOOST_REQUIRE( !psp.is_open() );

    psp.open();
    BOOST_CHECK( psp.is_open() );

    psp.open();
    BOOST_CHECK( psp.is_open() );

    psp.open();
    BOOST_CHECK( psp.is_open() );

    /*  ... and on and on */
}

BOOST_AUTO_TEST_CASE( multiple_closes_allowed )
{
    posix_serial_port psp( "/dev/ttyS0" );
    psp.open();
    BOOST_REQUIRE( psp.is_open() );

    psp.close();
    BOOST_CHECK( !psp.is_open() );

    psp.close();
    BOOST_CHECK( !psp.is_open() );

    psp.close();
    BOOST_CHECK( !psp.is_open() );

    /*  ... and on and on */
}
