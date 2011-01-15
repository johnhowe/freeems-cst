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
#include <cassert>

/* posix */
#include <fcntl.h>
#include <cerrno>
#include <cstring>
#include <termios.h>
#include <unistd.h>

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
          ::lockf( fd, F_TLOCK, 0 ) ) /**< non-block! */
      {
          throw runtime_error( "'"+path+"': "+strerror(errno) );
      }

      /* all reads are NON-BLOCKING */
      if( ::fcntl( fd, F_SETFL, FNDELAY ) )
      {
          throw runtime_error( strerror(errno) );
      }

      /* fetch current set of values */
      struct termios options;
      if( ::tcgetattr( fd, &options ) )
      {
          /* highly likely throw will occur here if
             the specified path is not to a serial port */
          throw runtime_error( strerror(errno) );
      }

      /* input modes: */
      options.c_iflag |= IGNBRK;    /**< ignore breaks */
      options.c_iflag |= IGNPAR;    /**< ignore parity errs */

      /* output modes: */
      options.c_oflag &= ~OPOST;    /**< raw */

      /* control modes: */
      options.c_cflag &= ~CSIZE;
      options.c_cflag |=  CS8;      /**< 8 bits */
      options.c_cflag |=  PARENB;   /**< parity enabled .. */
      options.c_cflag |=  PARODD;   /**< .. odd */
      options.c_cflag &= ~CSTOPB;   /**< 1 stop bit */
      options.c_cflag |=  CREAD;    /**< enb receiver */
      options.c_cflag |=  CLOCAL;   /**< ignore control lines */

      /* local modes: */
      options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

      if( ::cfsetspeed( &options, B115200 ) )
      {
          /* unable to set speed */
          throw runtime_error( strerror(errno) );
      }

      /* store new attributes */
      if( ::tcsetattr( fd, TCSANOW, &options ) )
      {
          throw runtime_error( strerror(errno) );
      }

      /* TODO: man pages specify that the call to tcsetattr()
         will not fail if ANY of the items in the termios
         are set correctly. this means that a failure is only
         reported if ALL fail - it is recommended to read back
         the termios struct and validate that the settings match */
  }
}

/**
 * @brief non-blocking fetch of data from serial port
 * @retval vector<uint8_t> reference to set of raw bytes for which
 *                         caller is responsible for disposal. NULL
 *                         otherwise (no data available).
 * @throw std::runtime_error
 */
vector<uint8_t> const* posix_serial_port::read()
{
  vector<uint8_t> const* retval = 0;

  if( !is_open() )
  {
      throw runtime_error( "port is closed" );
  }

  uint8_t rd_buf[1024 * 2];
  ssize_t const rd_cnt = ::read( fd, rd_buf, sizeof(rd_buf) );
  if( rd_cnt < 0 )
  {
      throw runtime_error( strerror(errno) );
  }

  if( rd_cnt > 0 )  /**< return null on 0 length */
  {
      retval = new vector<uint8_t>( rd_buf, rd_buf+rd_cnt );
  }

  return retval;
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
  if( !is_open() )
  {
      throw runtime_error( "port is closed" );
  }

  /* avoid undefined behavior of writing O length buffers to
     !regular files, see man pg for clarification while paying
     special attention to the RETURN VALUE section */
  size_t const buf_size = data.size();
  if( buf_size > 0 )
  {
      ssize_t const wr_cnt = ::write( fd, &data[0], buf_size );
      if( wr_cnt < 0 )
      {
          throw runtime_error( strerror(errno) );
      }

      if( static_cast<size_t>(wr_cnt) != buf_size )
      {
          /* iaw man pages, this is also considered a failure
             since the wr_cnt IS >0 BUT != the actual buffer size.
             I've seen this happen before when writing large chunks
             to a usb adapter and it's yanked mid write */
          throw runtime_error( "wtf: buf_size != wr_cnt" );
      }
  }
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
      if( ::lockf( fd, F_ULOCK, 0 ) )
      {
          throw runtime_error( strerror(errno) );
      }
      if( ::close( fd ) )
      {
          throw runtime_error( strerror(errno) );
      }
      fd = -1;
  }
}

posix_serial_port::~posix_serial_port()
{
  /* @note intended usage is to close() before destroy so
     you have the opportunity to capture anything thrown
     and handle in an application specific manner

     you've been warned
     */
  try
  {
      close();
  }
  catch( ... )
  {
      /* gulp ... yummy */
  }
}
