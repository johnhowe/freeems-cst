/**
 * @file       cst-test1.cpp
 * @headerfile
 * @author     sean
 * @brief      figure out how to start wrapping up open()
 *             read()/write()/select()
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

#include <cassert>
#include "fe.h"
using namespace std;
using namespace fe;

int
main( int argc,
      char *argv[] )
{
  (void)argc, (void)argv;

  /* in the future this operation will be aliased under a
     find_first operation which abstracts away the platform
     specifics:

     serial_port *const sp = find_first( ordered_path_collection );
     if( sp == 0 )
     {
        // fail
     }

      */

  /* otherwise, brute force it until the above is implemented */
  serial_port *const sp = new posix_serial_port( "/dev/ttyS0" );
  assert( sp );
  delete sp;

  return 0;
}
