/**
 * @file       psp.cpp
 * @headerfile psp.h
 * @author     sean
 * @brief      fe::posix_serial_port implementation
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

#include "psp.h"

/* std:: */
#include <stdexcept>

/* posix */
#include <fcntl.h>
#include <cerrno>
#include <cstring>
#include <termios.h>

using namespace std;
using namespace fe;

posix_serial_port::posix_serial_port( std::string const &port_path )
 : serial_port( port_path )
{
  fd = -1;
}

/**
 * @brief test if port is currently open
 * @retval bool true if open, false otherwise
 * @throw none
 */
bool posix_serial_port::is_open( void ) const
{
  return fd > 0;
}

/**
 * @brief attempt to open port if not so already
 * @retval none
 * @throw std::runtime_error
 */
void posix_serial_port::open( void )
{
  if( !is_open() )
  {
      fd = ::open( path.c_str(), O_RDWR | O_NOCTTY | O_NDELAY );
      if( (fd < 0) ||
          lockf( fd, F_TLOCK, 0 ) ) /**< non-block! */
      {
          throw std::runtime_error( "'"+path+"': "+strerror(errno) );
      }

      /* fetch current set of values */
      struct termios options;
      if( tcgetattr( fd, &options ) )
      {
          /* highly likely throw will occur here if
             the specified path is not to a serial port */
          throw std::runtime_error( strerror(errno) );
      }

      /* raw input */
      options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

      /* setup to hardcoded values initially, 115.2 8E1
         fred is ok with this first step */

      /* store new attributes */
      if( tcsetattr( fd, TCSANOW, &options ) )
      {
          throw std::runtime_error( strerror(errno) );
      }
  }
}

/**
 * @brief pend on serial port data
 * @param[in] timeout time to wait for data in milliseconds
 * @note this call blocks for duration of timeout
 * @retval vector<uint8_t> reference to set of raw bytes, will be empty
 *                         upon timeout
 * @throw std::runtime_error
 */
vector<uint8_t> const* posix_serial_port::read( uint32_t timeout )
{
  (void)timeout;
  throw runtime_error(
    "'vector<uint8_t> const* posix_serial_port::read( uint32_t timeout )'"
    " not implemented" );
}

/**
 * @brief write data to serial port
 * @param[in] data raw data to write
 * @note data is queued and this call is non-blocking
 * @retval none
 * @throw std::runtime_error
 */
void posix_serial_port::write( vector<uint8_t> const &data )
{
  (void)data;
  throw runtime_error(
    "void posix_serial_port::write( vector<uint8_t> const &data )'"
    " not implemented" );
}

/**
 * @brief close a port if not so already
 * @retval none
 * @throw none
 */
void posix_serial_port::close( void )
{
  if( is_open() )
  {
      lockf( fd, F_ULOCK, 0 ); /**< TODO: check retvals and throw on failure! */
      ::close( fd );
      fd = -1;
  }
}

posix_serial_port::~posix_serial_port()
{
  close();      /**< TODO: decide on how to handle if close()
                     throws: swallow? - normally, a user of
                     this class should close() ahead of the destructor
                     so that proper application specific actions
                     can be taken - not good practice to depend
                     on the destructor to close() for you */
}
