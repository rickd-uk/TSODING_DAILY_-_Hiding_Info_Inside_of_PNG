#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

#define PNG_SIG_CAP 8 
const uint8_t png_sig[PNG_SIG_CAP] = {137,80,78,71,13,10,26,10 };

void read_buffer_or_panic(FILE *file, uint8_t *buf,  size_t buf_cap) {

    size_t n = fread(buf, sizeof(buf_cap),  1, file);
if (n != 1){
  if (ferror(file))
{
   fprintf(stderr, "Error: Could not read PNG header: %s\n", strerror(errno));
   exit(1);
 } else if (feof(file))
 {
   fprintf(stderr, "Error: Could not read PNG header: reached the end of file\n");exit(1);
 } else {
     assert(0 && "Unreachable");
 } }
}

void print_bytes( uint8_t *buf,  size_t buf_cap){
   for (size_t i =0; i < buf_cap; ++i){
   printf("%u ", buf[i]);
 }
 printf("\n");
}

int main(int argc, char **argv) {

  (void) argc;
  assert(*argv != NULL);
  char *program = *argv++;

 if (*argv == NULL) {
     fprintf(stderr,"Usage: %s <input.png>\n", program);
    fprintf(stderr, "Error: no input file is provided\n");
     exit(1);
 }

 char *input_filepath = *argv++;

FILE *input_file = fopen(input_filepath, "rb");
if (input_file == NULL) {
  fprintf(stderr, "Error' Could not open file %s: %s\n", input_filepath, strerror(errno));
  exit(1);
}

uint8_t  sig[PNG_SIG_CAP];
read_buffer_or_panic(input_file, sig, PNG_SIG_CAP);
print_bytes(sig, PNG_SIG_CAP);

if (memcmp(sig, png_sig, PNG_SIG_CAP) != 0) {
 fprintf(stderr, "Error: %s does not appear to be a valid PNG image\n", input_filepath); 
 exit(1);
}

 printf("%s is a valid PNG image\n", input_filepath); 



fclose(input_file);

  return 0;
}