/**
 * @file       psp.cpp
 * @headerfile psp.h
 * @author     sean
 * @brief      fe::posix_serial_port implementation
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

#include "psp.h"

/* std:: */
#include <stdexcept>

/* posix */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

using namespace std;
using namespace fe;

posix_serial_port::posix_serial_port( std::string const &path )
{
  fd = open( path.c_str(), O_RDWR | O_NOCTTY );
  if( fd < 0 )
  {
      throw std::runtime_error( strerror(errno) );
  }
  // attempt lock
  // throw on fail
}

posix_serial_port::~posix_serial_port()
{
  if( fd >= 0 )
  {
      // flush ? not sure if thats done on close
      close( fd );    // check retval!
  }
}
