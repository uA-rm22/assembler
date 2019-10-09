#include <stdio.h>
#include <stdlib.h>

typedef struct {
	unsigned int   magic;
	unsigned int   text_size;
	unsigned int   data_size;
	unsigned int   bss_size;
	unsigned int   symtab_size;
	unsigned int   entry_point;
	unsigned int   re_text_size;
	unsigned int   re_data_size;
} aout_header;

int main( int argc, char **argv ){
  FILE *fp;
  aout_header header;
  char data[120];

  header.magic = 0x00640107;
  header.text_size = 0;
  header.data_size = 0;
  header.bss_size = 0;
  header.symtab_size = 0;
  header.entry_point = 0;
  header.re_text_size = 0;
  header.re_data_size = 0;

  fp = fopen("a.out", "wb");
  if(argc != 2){
    printf("引数の数が正しくない");
    return 1;
  }

  fwrite( &header, sizeof(aout_header) , 1, fp );

  fclose(fp);

//  fwirte( data, 1, num, fp);
  return 0;
}