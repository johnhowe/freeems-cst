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
#include <stdexcept>
#include <vector>
#include <stdint.h>

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
  class serial_port
  {
    public:
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
       * @brief fetch path
       * @param[out] path path to serial port
       * @retval none
       * @throw none
       */
      virtual void get_path( std::string &path ) const;

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

      virtual ~serial_port() {};

    protected:
      explicit serial_port() {};   /**< not meant to be instantiated directly */

      /**
       * serial ports cannot be copied. be aware that passing by value
       * is also automatically prohibited too
       */
      serial_port( serial_port const &copy );
      serial_port( serial_port &copy );

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
    create_serial_port( std::string const &path );  /**< TODO */

}

#endif // __sp_h
