/*
 * gifdump
 */

#include "gifdump.h"

void
usage ()
{
  fprintf(stderr, "Usage: gifdump <gif>\n");
}

int
main (int argc, const char **argv)
{
  if (argc < 2) {
    usage();
    return EXIT_FAILURE;
  }

  FILE *fh;
  if ((fh = fopen(argv[1], "rb")) == NULL) {
    fprintf(stderr, "Cannot open file '%s'!\n", argv[1]);
  }

  gif *target = gif_from_file(fh);
  if (!target->valid) {
    fprintf(stderr, "Invalid GIF format!\n");
    return EXIT_FAILURE;
  } else {
    gif_dump(target);
    return EXIT_SUCCESS;
  }
}
