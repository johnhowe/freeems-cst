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

BOOST_AUTO_TEST_CASE( default_ctor_no_throw )
{
    posix_serial_port psp;
}

BOOST_AUTO_TEST_CASE( ctor_allows_any_path )
{
    /* bad paths are caught on open attempt */
    posix_serial_port psp0( "path" );
    posix_serial_port psp1( "" );
    posix_serial_port psp2( "/dev/null" );
}

BOOST_AUTO_TEST_CASE( get_path_from_empty_ctor )
{
    posix_serial_port psp;

    string s;
    psp.get_path( s );

    BOOST_CHECK( s.empty() );
}

BOOST_AUTO_TEST_CASE( get_path_from_ctor )
{
    posix_serial_port psp( "path" );    /**< not necessarily valid
                                             (but !empty) */
    string s;
    psp.get_path( s );

    BOOST_CHECK( s == "path" );         /**< but stored as such */
}

BOOST_AUTO_TEST_CASE( set_path_allowed_if_not_open )
{
    posix_serial_port psp;
    string s;

    psp.get_path( s );
    BOOST_REQUIRE( s.empty() );

    psp.set_path( "path" );
    psp.get_path( s );
    BOOST_CHECK( s == "path" );
}

BOOST_AUTO_TEST_CASE( open_throws_on_empty_path )
{
    posix_serial_port psp;

    BOOST_REQUIRE_THROW(
     psp.open(),            /**< results in 'No such file or directory' */
     runtime_error ) ;
}
