/**
 * @file       sp.cpp
 * @headerfile sp.h
 * @author     sean
 * @brief      fe::serial_port null implementation
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

using namespace fe;

serial_port::serial_port( std::string const &port_path )
  : path( port_path )
{
}

/**
 * @brief fetch path
 * @param[out] path path to serial port
 * @retval none
 * @throw none
 */
void serial_port::get_path( std::string &port_path ) const
{
  port_path.assign( path );    /**< clobber anything which pre-exists */
}
