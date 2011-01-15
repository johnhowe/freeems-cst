/**
 * @file   sp.h
 * @author sean
 * @brief  serial port declaration
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

#ifndef   __sp_h
#define   __sp_h

/* std:: */
#include <string>
#include <vector>
#include <stdint.h>

/* boost:: */
#include <boost/utility.hpp>

namespace fe
{

  /**
   * @brief base abstraction for common serial port functionality
   *        never intended to be directly instantiated, use the
   *        create_serial_port() factory function to make.
   *
   * @warning this or any of its derivatives are not guaranteed to
   *          be threadsafe
   */
  class serial_port : private boost::noncopyable
  {
    public:
      /**
       * @brief attempt to open port if not so already
       * @retval none
       * @throw std::runtime_error
       */
      virtual void open( void ) = 0;

      /**
       * @brief test if port is currently open
       * @retval bool true if open, false otherwise
       * @throw none
       */
      virtual bool is_open( void ) const = 0;

      /**
       * @brief close a port if not so already
       * @retval none
       * @throw none
       */
      virtual void close( void ) = 0;

      /**
       * @brief fetch path
       * @param[out] path path to serial port
       * @retval none
       * @throw none
       */
      virtual void get_path( std::string &path ) const;

      /**
       * @brief non-blocking fetch of data from serial port
       * @retval vector<uint8_t> reference to set of raw bytes for which
       *                         caller is responsible for disposal. NULL
       *                         otherwise (no data available).
       * @throw std::runtime_error
       */
      virtual std::vector<uint8_t> const* read() = 0;

      /**
       * @brief write data to serial port
       * @param[in] data raw data to write
       * @note data is queued and this call is non-blocking
       * @retval none
       * @throw std::runtime_error
       */
      virtual void write( std::vector<uint8_t> const &data ) = 0;

      virtual ~serial_port() {};

    protected:
      explicit serial_port( std::string const &port_path );
      std::string const path;
  };

  /**
   * @public
   * @brief serial_port factory function
   *
   * creates a platform specific serial_port for use in your application.
   * this is the recommended method to maintain maximum portability. If you
   * know your platform; downcasting is acceptable, but not a good idea.
   *
   * @param[in] path path to serial port
   * @retval serial_port caller is responsible for disposal
   */
  serial_port *
    create_serial_port( std::string const &port_path );

}

#endif // __sp_h
