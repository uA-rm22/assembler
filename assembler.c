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
  char *data;

  data = calloc(1, sizeof(char) );

  header.magic = 0x00640107;
  header.text_size = 8;
  header.data_size = 0;
  header.bss_size = 0;
  header.symtab_size = 0;
  header.entry_point = 0;
  header.re_text_size = 0;
  header.re_data_size = 0;

  fp = fopen("a.out", "wb");
/*  if(argc != 2){
    printf("引数の数が正しくない");
    return 1;
  }
*/
  fwrite( &header, sizeof(aout_header) , 1, fp );

  p = "mov eax,9";
  tokenize(p);
  printf("I'm here. tokenize end\n");

  token = &head;

  while( token ){
    token = token->next;
//    printf("%s\n", token->name);
    switch(token->kind){
    case op:
      if(strncmp(token->name , "mov", 3) == 0 && token->len == 3){
        printf("I'm here. mov\n");
        token = token->next;
        if(strncmp(token->name, "eax", 3) == 0 && token->len == 3){
          printf("I'm here. eax\n");
          token = token->next;
          *data = 0xb8;
          fwrite( data, 1, 1, fp);
          if(strncmp(token->name, ",", 1) == 0){
            token = token->next;
            printf("I'm here. colon\n");
            if(token->kind == num){
              printf("I'm here. num\n");
              *data = token->val;
              token = token->next;
              fwrite( data, 1, 1, fp);
              *data = 0;
              fwrite( data, 1, 1, fp);
              fwrite( data, 1, 1, fp);
              fwrite( data, 1, 1, fp);

              *data = 0x90;
              fwrite( data, 1, 1, fp);
              fwrite( data, 1, 1, fp);
              fwrite( data, 1, 1, fp);
            }
          }              
        }
      }
      break;
    }
	}
  fclose(fp);
  return 0;
}