
#include "gif.h"

gif *
gif_new ()
{
  gif *self = (gif *)malloc(sizeof(gif));
  gif_init(self);
  return self;
}

void
gif_init (gif *self)
{
  self->valid = false;
  self->signature = (char *)malloc(sizeof(char)*4);
  self->version = (char *)malloc(sizeof(char)*4);
  self->width = 0;
  self->height = 0;
}

void
gif_dump (gif *self)
{
  gif_dump_txt(self);
}

void
gif_dump_txt (gif *self)
{
  printf("valid:\t%s\n", self->valid ? "yes" : "no");
  if (self->valid) {
    printf("width:\t%d\n", self->width);
    printf("height:\t%d\n", self->height);
    printf("global color table\n");
    printf("\tpresent:\t%d (%s)\n",
           self->global_color_table_flag,
           self->global_color_table_flag == 1 ? "yes" : "no");
    if (self->global_color_table_flag) {
      printf("\tcolor res:\t%d (%d bits/pixel)\n",
             self->color_resolution, self->color_resolution + 1);
      printf("\tsort flag:\t%d (%s)\n", self->sort_flag,
             self->sort_flag == 1 ? "desc" : "asc");
      printf("\tsize:     \t%d (%d)\n",
             self->global_color_table_size,
             1 << (self->global_color_table_size + 1));
      printf("\tbgcolor index:\t%d\n", self->background_color_index);
    }
    printf("pixel aspect ratio:\t%d\n", self->pixel_aspect_ratio);
  }
}

gif *
gif_from_file (FILE *fh)
{
  int i;
  gif *self = gif_new();

  char tmp[1024];
  char *ptr = &tmp[0];
  size_t read_bytes;
  read_bytes = fread(tmp, sizeof(char), 1024, fh);
  char *end_ptr = &tmp[read_bytes];

  memcpy(self->signature, ptr, 3);
  self->signature[3] = '\0';
  ptr += 3;

  memcpy(self->version, ptr, 3);
  self->version[3] = '\0';
  ptr += 3;

  self->valid =
    (strncmp(self->signature, "GIF", 3) == 0)
    && (strncmp(self->version, "89a", 3) == 0);

  self->width = read_uint16(ptr);
  ptr += sizeof(uint16_t);

  self->height = read_uint16(ptr);
  ptr += sizeof(uint16_t);

  unsigned char packed = read_uint8(ptr);
  ptr += sizeof(uint8_t);

  self->global_color_table_flag =
    ((packed & 0x40) == 0x40) ? 1 : 0;

  self->color_resolution = (packed >> 4) && 0x07;
  self->sort_flag = (packed >> 3) && 0x01;
  self->global_color_table_size = packed & 0x07;

  self->background_color_index = read_uint8(ptr);
  ptr += sizeof(uint8_t);

  self->pixel_aspect_ratio = read_uint8(ptr);
  ptr += sizeof(uint8_t);

  // read global color table
  if (self->global_color_table_flag == 1) {
    unsigned num_colors = (1 << (self->global_color_table_size + 1));
    for (i = 0; i < num_colors; i++) {
      /*
      printf("r:%3d g:%3d b:%3d\n",
             *((unsigned char *)&ptr[0]),
             *((unsigned char *)&ptr[1]),
             *((unsigned char *)&ptr[2]));
      */
      ptr += 3;
      if (ptr > end_ptr) {
        fprintf(stderr, "warning: went past tmp buffer!\n");
        break;
      }
    }
  }

  return self;
}
