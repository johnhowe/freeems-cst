/**
 * @file       endec.cpp
 * @headerfile endec.h
 * @author     sean
 * @brief      fe::endec implementation
 *
 * freeems-cst: freeems 'comms smoke test'
 *
 * Copyright (C) 2010, 2011 Sean Stasiak sstasiak at gmail
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

#include "endec.h"
using namespace fe;
using namespace std;

/**
 * @private
 * default reservation size for packet encode
 * and decode buffers
 */
uint32_t const endec::default_resv_size = (1024 * 2);

/**
 * @public
 * @brief decode to a flattened packet
 * @param[in] p reference to encoded packet
 * @retval vector<uint8_t> decoded packet. caller is responsible for
 *                         destruction when use is complete.
 * @throw escxor_error
 */
vector<uint8_t> *
  endec::decode( vector<uint8_t> const &p )
    throw( escxor_error )
{
    vector<uint8_t> *const v = new vector<uint8_t>();
    v->reserve( default_resv_size ); /**< reserve initial worst case capacity */

    bool esc_prev = false;  /**< track if prev byte was an ESC */

    for( vector<uint8_t>::const_iterator pkt_iter = p.begin();
      pkt_iter != p.end() ;pkt_iter++ )
    {
        uint8_t b = *pkt_iter;

        if( b == ESC )
        {
            esc_prev = true;
            continue;
        }

        if( esc_prev )
        {
            b ^= 0xFF;
            /* this byte can ONLY be 3 possible values: */
            if( (b != STX) &&
                (b != ETX) &&
                (b != ESC) )
            {
                /* if not, destroy and throw */
                delete v;
                throw escxor_error();     /* TODO: pass curr idx to ctor */
            }
            esc_prev = false;
        }
        v->push_back( b );
    }

    return v;
}

/**
 * @public
 * @brief encode a flattened packet
 * @param[in] p reference to flattened packet
 * @retval vector<uint8_t> packet encoded in accordance with the freeems
 *                         core protocol spec. caller is responsible for
 *                         destruction when use is complete.
 */
vector<uint8_t> *
  endec::encode( vector<uint8_t> const &p )
{
    vector<uint8_t> *const v = new vector<uint8_t>();
    v->reserve( default_resv_size ); /**< reserve initial worst case capacity */

    vector<uint8_t>::const_iterator pkt_iter = p.begin();
    while( pkt_iter != p.end() )
    {
        uint8_t b = *pkt_iter;

        /* ESC any reserved bytes in the stream */
        if( (b == STX ) ||
            (b == ETX ) ||
            (b == ESC ) )
        {
            v->push_back( ESC );
            b ^= 0xFF;
        }

        v->push_back( b );
        pkt_iter++;
    }

    return v;
}
