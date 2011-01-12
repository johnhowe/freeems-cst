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
      explicit posix_serial_port();
      explicit posix_serial_port( std::string const &path );

      virtual void set_path( std::string const &path );
      virtual void get_path( std::string &path );
      virtual void open( void );
      virtual void open( std::string const &path );
      virtual bool is_open( void );
      virtual void close( void );

      virtual std::vector<uint8_t> const* read( uint32_t timeout );
      virtual void write( std::vector<uint8_t> const &data );

      virtual ~posix_serial_port();

    private:
      void init_psp( void );
      int fd;
      std::string path;
    };
}

#endif // __psp_h
