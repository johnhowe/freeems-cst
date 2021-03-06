/**
 * @file       wsp.cpp
 * @headerfile wsp.h
 * @author     sean
 * @brief      fe::win_serial_port implementation
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

#include "wsp.h"

/* std:: */
#include <stdexcept>

using namespace std;
using namespace fe;

win_serial_port::win_serial_port( std::string const &port_path )
 : serial_port( port_path )
{
  throw runtime_error(
    "win_serial_port::win_serial_port( std::string const &port_path )'"
    " not implemented" );
}
