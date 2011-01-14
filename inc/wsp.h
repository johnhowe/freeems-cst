/**
 * @file   wsp.h
 * @author sean
 * @brief  windows serial port declaration
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

#ifndef   __wsp_h
#define   __wsp_h

#include "sp.h"

namespace fe
{
    class win_serial_port : public serial_port
    {
    public:
      explicit win_serial_port( std::string const &port_path );

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
       * @brief non-blocking fetch of data from serial port
       * @retval vector<uint8_t> reference to set of raw bytes caller
       *                         is responsible for disposal
       * @throw std::runtime_error
       */
      virtual std::vector<uint8_t> const* read();

      /**
       * @brief write data to serial port
       * @param[in] data raw data to write
       * @note data is queued and this call is non-blocking
       * @retval none
       * @throw std::runtime_error
       */
      virtual void write( std::vector<uint8_t> const &data );

      virtual ~win_serial_port();
    };
}

#endif // __wsp_h
