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

namespace fe
{
    /* add util func to find_first() from a list of supplied paths */

    class serial_port
    {
      public:
        virtual void read( void ) {};
        virtual void write( void ) {};
        virtual ~serial_port() {};
      protected:
        serial_port() {};
    };
}

#endif // __sp_h
