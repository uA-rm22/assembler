#include "asm.h"

void error(char *str){
  printf("%s\n", str);
  exit(1);
}

int main( int argc, char **argv ){
  FILE *fp;
  aout_header header;
  char *p;
  Token *token;
  char data[8];
  struct stat st;
  int data_size = 0;

  header.magic = 0x00640107;
  header.text_size = 0;
  header.data_size = 0;
  header.bss_size = 0;
  header.symtab_size = 0;
  header.entry_point = 0;
  header.re_text_size = 0;
  header.re_data_size = 0;

  fp = fopen("a.out", "wb");
  fwrite( &header, sizeof(aout_header) , 1, fp );

  p = "mov eax,9";
  tokenize(p);
  token = &head;
  if( !token->next ){
    printf("空のアセンブリファイル\n");
  }
  token = token->next;

  while( token ){
    switch(token->kind){
    case op:
      if(strncmp(token->name , "mov", 3) == 0 && token->len == 3){
        token = token->next;
        if(strncmp(token->name, "eax", 3) == 0 && token->len == 3){
          token = token->next;
          data[0] = 0xb8;
          if(strncmp(token->name, ",", 1) == 0){
            token = token->next;
            if(token->kind == num){
              data[1] = token->val;
              token = token->next;
              data[2] = 0;
              data[3] = 0;
              data[4] = 0;

              data_size += 5;

              fwrite( data, 5, 1, fp);
            }
          }              
        }
      }
      break;
    }
	}

  while(data_size % 8 != 0 && data_size != 0){
    data_size += 1;
    data[0] = 0x90; //nop

    fwrite( data, 1, 1, fp );
  }

  rewind(fp);
  header.text_size = data_size;
  fwrite( &header, sizeof(aout_header) , 1, fp );
  fclose(fp);
  return 0;
}