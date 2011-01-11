/**
 * @file       cst-test2.cpp
 * @headerfile
 * @author     sean
 * @brief      figure out a 'stripper' which takes fragments of
 *             the input stream and yields packets which are
 *             stripped of the STX/ETX
 *
 * freeems-cst: freeems 'comms smoke test'
 *
 * Copyright (C) 2010,2011 Sean Stasiak sstasiak at gmail
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

#include <boost/signal.hpp>
#include <iostream>

void func1()
{
  std::cout << "Hello" << std::flush;
}

void func2()
{
  std::cout << ", world!" << std::endl;
}

int
main( int argc,
      char *argv[] )
{
  (void)argc, (void)argv;

  boost::signal<void ()> s;
  s.connect(1,func2);
  s.connect(0,func1);
  s();

  return 0;
}

