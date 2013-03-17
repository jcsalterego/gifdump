
#include "stream.h"

uint16_t
read_uint16 (char *data)
{
  unsigned char* udata = (unsigned char*)data;
  return ((uint16_t)(*(&udata[0])) +
          (uint16_t)(*(&udata[1]) << 8));
}

uint8_t
read_uint8 (char *data)
{
  unsigned char* udata = (unsigned char*)data;
  return (uint8_t)(*(&udata[0]));
}
