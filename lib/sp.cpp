/**
 * @file       sp.cpp
 * @headerfile sp.h
 * @author     sean
 * @brief      fe::serial_port null implementation
 *
 * freeems-cst: freeems 'comms smoke test'
 *
 * Copyright (C) 2011 Sean Stasiak sstasiak at gmail
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

#include "sp.h"

using namespace std;
using namespace fe;

void serial_port::open( void )
{
  throw runtime_error(
    "'void serial_port::open( void )'"
    " not implemented" );
}

void serial_port::open( string const &path )
{
  (void)path;
  throw runtime_error(
    "'void serial_port::open( std::string const &path )'"
    " not implemented" );
}

bool serial_port::is_open( void )
{
  throw runtime_error(
    "'bool serial_port::is_open( void )'"
    " not implemented" );
}

void serial_port::close( void )
{
  throw runtime_error(
    "'void serial_port::close( void )'"
    " not implemented" );
}

void serial_port::set_path( string const &path )
{
  (void)path;
  throw runtime_error(
    "'void serial_port::set_path( std::string const &path )'"
    " not implemented" );
}

void serial_port::get_path( string &path )
{
  (void)path;
  throw runtime_error(
    "'void serial_port::get_path( std::string &path )'"
    " not implemented" );
}

vector<uint8_t> const* serial_port::read( uint32_t timeout )
{
  (void)timeout;
  throw runtime_error(
    "'vector<uint8_t> const* serial_port::read( uint32_t timeout )'"
    " not implemented" );
}

void serial_port::write( vector<uint8_t> const &data )
{
  (void)data;
  throw runtime_error(
    "void serial_port::write( vector<uint8_t> const &data )'"
    " not implemented" );
}
