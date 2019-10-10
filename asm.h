#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {num, op, reg, symbol, label } Kind;
typedef struct Token Token;
struct Token{
  char *name;
  int len;
  int val;
  Kind kind;
  Token *next;
};

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

Token *new_token(char *name, int len, int val, Kind kind);
void tokenize(char *p);

void error(char *str);

extern Token *current_token;
extern Token head;