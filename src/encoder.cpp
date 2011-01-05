/**
 * @file       encoder.cpp
 * @headerfile fe.h
 * @author     sean
 * @brief      fe::encoder implementation
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

#include "fe.h"

/**
 * @public
 * @brief encode a flattened packet
 * @param[in] p reference to flattened packet
 * @retval vector<uint8_t> packet encoded in accordance with the freeems
 *                         core protocol spec. caller is responsible for
 *                         destruction when use is complete.
 */
std::vector<uint8_t> *
  fe::encode( std::vector<uint8_t> const &p )
{
    std::vector<uint8_t> *const v = new std::vector<uint8_t>();
    v->reserve( default_resv_size ); /**< reserve initial worst case capacity */

    std::vector<uint8_t>::const_iterator pkt_iter = p.begin();
    while( pkt_iter != p.end() )
    {
        uint8_t b = *pkt_iter;

        /* ESC any reserved bytes in the stream */
        if( (b == fe::STX ) ||
            (b == fe::ETX ) ||
            (b == fe::ESC ) )
        {
            v->push_back( fe::ESC );
            b ^= 0xFF;
        }

        v->push_back( b );
        pkt_iter++;
    }

    return v;
}
