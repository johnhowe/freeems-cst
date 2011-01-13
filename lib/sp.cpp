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

/**
 * @brief attempt to open port if not so already
 * @retval none
 * @throw std::runtime_error
 */
void serial_port::open( void )
{
  throw runtime_error(
    "'void serial_port::open( void )'"
    " not implemented" );
}

/**
 * @brief test if port is currently open
 * @retval bool true if open, false otherwise
 * @throw none
 */
bool serial_port::is_open( void ) const
{
  throw runtime_error(
    "'bool serial_port::is_open( void )'"
    " not implemented" );
}

/**
 * @brief close a port if not so already
 * @retval none
 * @throw none
 */
void serial_port::close( void )
{
  throw runtime_error(
    "'void serial_port::close( void )'"
    " not implemented" );
}

/**
 * @brief fetch path
 * @param[out] path path to serial port
 * @retval none
 * @throw none
 */
void serial_port::get_path( string &path ) const
{
  (void)path;
  throw runtime_error(
    "'void serial_port::get_path( std::string &path )'"
    " not implemented" );
}

/**
 * @brief pend on serial port data
 * @param[in] timeout time to wait for data in milliseconds
 * @note this call blocks for duration of timeout
 * @retval vector<uint8_t> reference to set of raw bytes, will be empty
 *                         upon timeout
 * @throw std::runtime_error
 */
vector<uint8_t> const* serial_port::read( uint32_t timeout )
{
  (void)timeout;
  throw runtime_error(
    "'vector<uint8_t> const* serial_port::read( uint32_t timeout )'"
    " not implemented" );
}

/**
 * @brief write data to serial port
 * @param[in] data raw data to write
 * @note data is queued and this call is non-blocking
 * @retval none
 * @throw std::runtime_error
 */
void serial_port::write( vector<uint8_t> const &data )
{
  (void)data;
  throw runtime_error(
    "void serial_port::write( vector<uint8_t> const &data )'"
    " not implemented" );
}
