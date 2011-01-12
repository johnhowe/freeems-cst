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

/* posix */
#include <fcntl.h>
#include <cerrno>
#include <cstring>
#include <cassert>
#include <unistd.h>

using namespace std;
using namespace fe;

posix_serial_port::posix_serial_port()
{
  init_psp();
}

posix_serial_port::posix_serial_port( std::string const &path )
{
  init_psp();
  set_path( path );
}

void posix_serial_port::init_psp( void )
{
  fd = -1;
  path = 0;
}

bool posix_serial_port::is_open( void )
{
    return fd > 0;
}

void posix_serial_port::set_path( std::string const &path )
{
  if( !is_open() )
  {
      if( path.empty() )
      {
          throw runtime_error( "empty path not allowed" );
      }

      if( this->path )
      {
          delete this->path;
          this->path = 0;
      }

      this->path = new string( path );
  }
}

void posix_serial_port::get_path( std::string &path )
{
  path.clear();
  if( this->path )
  {
      path.assign( *(this->path) );
  }
}

void posix_serial_port::open( std::string const &path )
{
  set_path( path );
  open();
}

void posix_serial_port::close( void )
{
  if( is_open() )
  {
      lockf( fd, F_ULOCK, 0 );
      ::close( fd );
      fd = -1;
  }
}

void posix_serial_port::open( void )
{
  if( !is_open() )
  {
      if( !path )
      {
          throw runtime_error( "path to serial port does not exist" );
      }

      fd = ::open( path->c_str(), O_RDWR | O_NOCTTY | O_NDELAY );
      if( (fd < 0) ||
          lockf( fd, F_TLOCK, 0 ) ) /**< non-block! */
      {
          throw std::runtime_error( strerror(errno) );
      }

      /* TODO: do check to make sure we've opened a serial port
         via tcgetattr */

      /* if this is a serial port, setup as desired */
  }
}

posix_serial_port::~posix_serial_port()
{
  close();

  if( path )
  {
      delete path;
      path = 0;
  }
}

vector<uint8_t> const* posix_serial_port::read( uint32_t timeout )
{
  (void)timeout;
  throw runtime_error(
    "'vector<uint8_t> const* posix_serial_port::read( uint32_t timeout )'"
    " not implemented" );
}

void posix_serial_port::write( vector<uint8_t> const &data )
{
  (void)data;
  throw runtime_error(
    "void posix_serial_port::write( vector<uint8_t> const &data )'"
    " not implemented" );
}
