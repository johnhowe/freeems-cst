/**
 * @file       cst-test2.cpp
 * @headerfile
 * @author     sean
 * @brief      experiment with some cout and stuff found in utility
 *
 * freeems-cst: freeems 'comms smoke test'
 *
 * Copyright (C) 2010 Sean Stasiak sstasiak at gmail
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

/* std:: */
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>
#include <stdint.h>
using namespace std;

int
main( int argc,
      char *argv[] )
{
    (void)argc, (void)argv;

    const int cmax = numeric_limits<char>::max();
    cout <<"cmax: " << cmax << endl;

    cout << hex << 0x20 << endl;
    cout << 0x20 << endl;   /**< does it 'stick' ? */   /* yep */

    /* use stringstream to build something as a dumper
       (like a pkt dumper) */
    stringstream ss;
    ss << "test" << hex << 0x20;
    cout << ss.str() << endl;

    cout << endl << endl;

    /* try something pkt dumper like */
    uint8_t const data[] = { 0x11, 0x22, 0x33, 0xaa };
    vector<uint8_t> const v( data, data+sizeof(data) );

    cout << "data: " << hex << showbase << 0x10 << " "
         << 0x110 << " " << static_cast<int>(data[3]) << endl;
    ss.str("");

    // 8 hex .. space .. 8 ascii if printable

}

