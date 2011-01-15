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

#include "fe.h"

/* std:: */
#include <cassert>
#include <memory>
#include <stdint.h>
#include <iostream>

/* posix */
#include <unistd.h>

using namespace std;
using namespace fe;

int
main( int argc,
      char *argv[] )
{
  (void)argc, (void)argv;

  auto_ptr<serial_port> const sp( create_serial_port( "/dev/ttyS0" ) );
  assert( sp.get() );
  sp->open();

  /* attempt quick-n-dirty loopback */
  uint8_t const d[] = "testing ... ";
  vector<uint8_t> const v( d, d+sizeof(d) );
  sp->write( v );
  usleep( 50000 );  /* block 50ms */
  vector<uint8_t> const *resp = sp->read();
  assert( resp );
  assert( resp->size() == sizeof(d) );
  /* TODO: is it really a mirror of d[]? */
  delete resp;

  return 0;
}

