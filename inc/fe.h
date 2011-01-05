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

#include <stdint.h>
#include <vector>
#include "fe_exception.h"

namespace fe
{

  /**
   * @public
   * @enum
   * @li @b STX todo description
   * @li @b ETX todo description
   * @li @b ESC todo description
   */
  enum
  {
      STX = 0xAA,
      ESC = 0xBB,
      ETX = 0xCC
  };

  /**
   * default reservation size for packet encode
   * and decode buffers
   */
  uint32_t const default_resv_size = 1024 * 4;

  /**
   * @public
   * @brief encode a flattened packet
   * @param[in] p reference to flattened packet
   * @retval vector<uint8_t> packet encoded in accordance with the freeems
   *                         core protocol spec. caller is responsible for
   *                         destruction when use is complete.
   */
  std::vector<uint8_t> *
    encode( std::vector<uint8_t> const &p );

  /**
   * @brief decode to a flattened packet
   * @param[in] p reference to encoded packet
   * @retval vector<uint8_t> decoded packet. caller is responsible for
   *                         destruction when use is complete.
   * @throw escxor_error
   */
   std::vector<uint8_t> *
     decode( std::vector<uint8_t> const &p )
       throw( escxor_error );

}

#endif // __fe_h
