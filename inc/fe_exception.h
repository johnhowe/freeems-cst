/**
 * @file   fe_exception.h
 * @author sean
 * @brief  freeems library exceptions
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

#ifndef   __fe_exception_h
#define   __fe_exception_h

#include <stdexcept>

namespace fe
{
  class escxor_error : public std::runtime_error
  {
    /* an incorrectly xor'ed byte has followed
       an esc byte */
    public:
      escxor_error( void ) :
        runtime_error( "escxor_error: TODO: take an index" ) {}
  };

  class stx_error : public std::runtime_error
  {
    /* a STX arrived unexpectedly mid frame */
    public:
      stx_error( void ) :
        runtime_error( "stx_error: TODO: take an index" ) {}
  };
}

#endif // __fe_exception_h
