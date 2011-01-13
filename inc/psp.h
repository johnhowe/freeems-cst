/**
 * @file   psp.h
 * @author sean
 * @brief  posix serial port declaration
 *
 * freeems-cst: freeems 'comms smoke test'
 *
 * Copyright (C) 2010, 2011 Sean Stasiak sstasiak at gmail
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

#ifndef   __psp_h
#define   __psp_h

#include "sp.h"

namespace fe
{
  class posix_serial_port : public serial_port
  {
    public:

      explicit posix_serial_port( std::string const &port_path );

      /**
       * @brief fetch path
       * @param[out] path path to serial port
       * @retval none
       * @throw none
       */
      virtual void get_path( std::string &port_path ) const;

      /**
       * @brief attempt to open port if not so already
       * @retval none
       * @throw std::runtime_error
       */
      virtual void open( void );

      /**
       * @brief test if port is currently open
       * @retval bool true if open, false otherwise
       * @throw none
       */
      virtual bool is_open( void ) const;

      /**
       * @brief close a port if not so already
       * @retval none
       * @throw none
       */
      virtual void close( void );

      /**
       * @brief pend on serial port data
       * @param[in] timeout time to wait for data in milliseconds
       * @note this call blocks for duration of timeout
       * @retval vector<uint8_t> reference to set of raw bytes, will be empty
       *                         upon timeout
       * @throw std::runtime_error
       */
      virtual std::vector<uint8_t> const* read( uint32_t timeout );

      /**
       * @brief write data to serial port
       * @param[in] data raw data to write
       * @note data is queued and this call is non-blocking
       * @retval none
       * @throw std::runtime_error
       */
      virtual void write( std::vector<uint8_t> const &data );

      virtual ~posix_serial_port();

    private:
      posix_serial_port( posix_serial_port const &copy );
      posix_serial_port( posix_serial_port &copy );
      int fd;
      std::string const path;
    };
}

#endif // __psp_h
