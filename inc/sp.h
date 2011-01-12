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

#include <stdexcept>

namespace fe
{
    /* TODO: add util func to find_first() from a list of supplied paths */

    /* TODO: add set/get settings */

    class serial_port
    {
      public:

        virtual void open( void )
            { throw std::runtime_error( "open() not implemented" ); }

        virtual void open( std::string const &path )
            { (void)path; throw std::runtime_error( "open(&path) not implemented" ); }

        virtual bool is_open( void )
            { throw std::runtime_error( "is_open() not implemented" ); }

        virtual void close( void )
            { throw std::runtime_error( "close() not implemented" ); }

        virtual void set_path( std::string const &path )
            { (void)path; throw std::runtime_error( "set_path() not implemented" ); }

        virtual void get_path( std::string &path )
            { (void)path; throw std::runtime_error( "get_apth() not implemented" ); }

        virtual void read( void )
            { throw std::runtime_error( "read() not implemented" ); }

        virtual void write( void )
            { throw std::runtime_error( "write() not implemented" ); }

        virtual ~serial_port() {};

      protected:
        serial_port() {};
    };
}

#endif // __sp_h
