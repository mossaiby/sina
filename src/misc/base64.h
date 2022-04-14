//        _             
//    ___(_)_ __   __ _ 
//   / __| | '_ \ / _` |    simple and intuitive numerical analysis
//   \__ \ | | | | (_| |    Farshid Mossaiby, University of Isfahan
//   |___/_|_| |_|\__,_|    (c) copyright 2019, all rights reserved
//                      
//
// base64.h
//
// base64 encoder / decoder class
//

#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <cstdint>

#include "sina.h"
#include "utils.h"


namespace sina
{
  namespace utils
  {
    class base64
    {
      public:

      static inline std::uint8_t *encode(const std::uint8_t *data, const sina::kernel::index_t size)
      {
        const char encode_lookup[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        const char base64_padding = '=';

        std::uint8_t *output = new uint8_t[4 * ((size + 2) / 3) + 1];
        std::uint8_t *current_output = output;

        std::uint32_t buffer;

        for (sina::kernel::index_t i = 0; i < size / 3; i++)
        {
          buffer = (*data++) << 16;
          buffer += (*data++) << 8;
          buffer += (*data++);
          *current_output++ = encode_lookup[(buffer & 0x00FC0000) >> 18];
          *current_output++ = encode_lookup[(buffer & 0x0003F000) >> 12];
          *current_output++ = encode_lookup[(buffer & 0x00000FC0) >> 6];
          *current_output++ = encode_lookup[buffer & 0x0000003F];
        }

        switch (size % 3)
        {
          case 1:
            buffer = (*data++) << 16;
            *current_output++ = encode_lookup[(buffer & 0x00FC0000) >> 18];
            *current_output++ = encode_lookup[(buffer & 0x0003F000) >> 12];
            *current_output++ = base64_padding;
            *current_output++ = base64_padding;
            break;
            
          case 2:
            buffer = (*data++) << 16;
            buffer += (*data++) << 8;
            *current_output++ = encode_lookup[(buffer & 0x00FC0000) >> 18];
            *current_output++ = encode_lookup[(buffer & 0x0003F000) >> 12];
            *current_output++ = encode_lookup[(buffer & 0x00000FC0) >> 6];
            *current_output++ = base64_padding;
            break;
        }

        *current_output = 0;
        return output;
      }

      static inline std::uint8_t *decode(const std::uint8_t *data, const sina::kernel::index_t size)
      {
        const char base64_padding = '=';
        if (size % 4 != 0)
        {
          SINA_ERROR("invalid length");
        }

        sina::kernel::index_t padding = 0;

        if (size != 0)
        {
          if (data[size - 1] == base64_padding) {
            padding++;
          }

          if (data[size - 2] == base64_padding) {
            padding++;
          }
        }

        std::uint8_t *output = new uint8_t[((size / 4) * 3) - padding + 1];
        std::uint8_t *current_output = output;

        std::uint32_t buffer = 0;

        const std::uint8_t *current_input = data;

        while (current_input != data + size)
        {
          for(sina::kernel::index_t i = 0; i < 4; i++)
          {
            buffer <<= 6;

            if (*current_input >= 0x41 && *current_input <= 0x5A)
            {
              buffer |= *current_input - 0x41;
            }
            
            else if (*current_input >= 0x61 && *current_input <= 0x7A)
            {
              buffer |= *current_input - 0x47;
            }
            
            else if (*current_input >= 0x30 && *current_input <= 0x39)
            {
              buffer |= *current_input + 0x04;
            }
            
            else if (*current_input == 0x2B)
            {
              buffer |= 0x3E;
            }
            
            else if (*current_input == 0x2F)
            {
              buffer |= 0x3F;
            }
            
            else if (*current_input == base64_padding)
            {
              switch(data + size - current_input)
              {
                case 1:
                  *current_output++ = (buffer >> 16) & 0x000000FF;
                  *current_output++ = (buffer >> 8 ) & 0x000000FF;
                  *current_output = 0;
                  return output;
            
                case 2:
                  *current_output++ = (buffer >> 10) & 0x000000FF;
                  *current_output = 0;
                  return output;
                  
                default:
                  SINA_ERROR("invalid padding");
              }
            }
            
            else
            {
              SINA_ERROR("invalid input data");
            }

            current_input++;
          }

          *current_output++ = (buffer >> 16) & 0x000000FF;
          *current_output++ = (buffer >> 8) & 0x000000FF;
          *current_output++ = buffer & 0x000000FF;
        }

        *current_output = 0;
        return output;
      }
    };
  }
}