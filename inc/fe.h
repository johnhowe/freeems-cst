/**
 * @file   fe.h
 * @author sean
 * @brief  freeems library
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

#ifndef   __fe_h
#define   __fe_h

#include "endec.h"
#include "sp.h"
#include "psp.h"
#include "wsp.h"

/**
 * statically determine element size of 1d array
 */
#define EDIM( arg_ )        (sizeof(arg_)/sizeof(arg_[0]))

#endif // __fe_h
