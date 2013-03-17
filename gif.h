
#ifndef __GIF_H__
#define __GIF_H__

typedef struct gif gif;

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stream.h"

struct gif {
  bool valid;
  char *signature;
  char *version;

  unsigned width;
  unsigned height;

  unsigned char global_color_table_flag;
  unsigned char color_resolution;
  unsigned char sort_flag;
  unsigned char global_color_table_size;

  unsigned char background_color_index;
  unsigned char pixel_aspect_ratio;
};

gif *gif_new ();
void gif_init (gif *self);

void gif_dump (gif *self);
void gif_dump_txt (gif *self);
gif *gif_from_file (FILE *fh);

#endif
