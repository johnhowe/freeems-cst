/**
 * @file       endec.cpp
 * @headerfile endec.h
 * @author     sean
 * @brief      encoder/decoder implementation
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
 * @brief decode to a raw flattened packet
 * @param[in] encoded_pkt reference to encoded packet
 * @retval vector<uint8_t> decoded packet. caller is responsible for
 *                         destruction when use is complete.
 * @throw escxor_error
 */
vector<uint8_t> *
  endec::decode( vector<uint8_t> const &encoded_pkt )
{
    vector<uint8_t> *const raw_pkt = new vector<uint8_t>();

    /* reserve initial worst case capacity to avoid
       multiple reallocations as decoding progresses */
    raw_pkt->reserve( default_resv_size );

    bool esc_prev = false;  /**< track if prev byte was an ESC */

    for( vector<uint8_t>::const_iterator byte_iter = encoded_pkt.begin();
      byte_iter != encoded_pkt.end() ;byte_iter++ )
    {
        uint8_t b = *byte_iter;

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
                delete raw_pkt;
                throw escxor_error();     /* TODO: pass curr idx to ctor */
            }
            esc_prev = false;
        }
        raw_pkt->push_back( b );
    }

    return raw_pkt;
}

/**
 * @public
 * @brief encode a raw flattened packet
 * @param[in] raw_pkt reference to flattened packet
 * @retval vector<uint8_t> packet encoded in accordance with the freeems
 *                         core protocol spec. caller is responsible for
 *                         destruction when use is complete.
 */
vector<uint8_t> *
  endec::encode( vector<uint8_t> const &raw_pkt )
{
    vector<uint8_t> *const encoded_pkt = new vector<uint8_t>();

    /* reserve initial worst case capacity to avoid
       multiple reallocations as encoding progresses */
    encoded_pkt->reserve( default_resv_size );

    for( vector<uint8_t>::const_iterator byte_iter = raw_pkt.begin();
      byte_iter != raw_pkt.end() ;byte_iter++ )
    {
        uint8_t b = *byte_iter;

        /* ESC any reserved bytes in the stream */
        if( (b == STX ) ||
            (b == ETX ) ||
            (b == ESC ) )
        {
            encoded_pkt->push_back( ESC );
            b ^= 0xFF;
        }

        encoded_pkt->push_back( b );
    }

    return encoded_pkt;
}
