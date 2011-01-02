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
#include <string>
using namespace std;

int
main( int argc,
      char *argv[] )
{
    (void)argc, (void)argv;

    const int cmax = numeric_limits<char>::max();
    cout <<"cmax: " << cmax << endl;

    cout << hex << 0x20 << endl;
}

