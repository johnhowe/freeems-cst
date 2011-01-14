/**
 * @file       create_serial_port.cpp
 * @headerfile sp.h
 * @author     sean
 * @brief      factory function for generating downcasted platform
 *             specific serial port
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

#include "sp.h"
#include "psp.h"
#include "wsp.h"

/* std:: */
#include <stdexcept>

#define __USE_POSIX_SP__ 1      /**< hard coded until win implemented then this
                                     will be pulled out into a build time define
                                     through the usual '-D' */

using namespace std;
using namespace fe;

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
  fe::create_serial_port( string const &port_path )
{
#ifdef __USE_POSIX_SP__
  return new posix_serial_port( port_path );
#else
  throw runtime_error(
    "'serial_port *create_serial_port( std::string const &path )'"
    " not implemented" );
#endif
}
