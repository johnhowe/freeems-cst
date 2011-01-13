/**
 * @file   endec.h
 * @author sean
 * @brief  encoder/decoder declaration
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

#ifndef   __endec_h
#define   __endec_h

#include <string>
#include <vector>
#include <stdint.h>
#include "feexc.h"

namespace fe
{
  class endec
  {
    public:
      /**
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
       * @brief encode a flattened packet
       * @param[in] p reference to flattened packet
       * @retval vector<uint8_t> packet encoded in accordance with the freeems
       *                         core protocol spec. caller is responsible for
       *                         destruction when use is complete.
       */
      static std::vector<uint8_t> *
        encode( std::vector<uint8_t> const &p );

      /**
       * @brief decode to a flattened packet
       * @param[in] p reference to encoded packet
       * @retval vector<uint8_t> decoded packet. caller is responsible for
       *                         destruction when use is complete.
       * @throw escxor_error
       */
       static std::vector<uint8_t> *
         decode( std::vector<uint8_t> const &p );

    private:
      /**
       * default reservation size for packet encode
       * and decode buffers
       */
      static uint32_t const default_resv_size;

      endec();  /**< static class */
  };
}

#endif // __endec_h
