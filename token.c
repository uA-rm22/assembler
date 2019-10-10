#include "asm.h"

Token *current_token;
Token head;

Token *new_token(char *name, int len, int val, Kind kind){
	Token *tok = calloc(1, sizeof(Token));
	tok->name = name;
	tok->len = len;
	tok->val = val ;
	tok->kind = kind;
  tok->next = NULL;
  current_token->next = tok;
  current_token = tok;
	return tok;
}

void tokenize(char *p){
  head.next = NULL;
  current_token = &head;

  while( *p ){
    if( isspace(*p) ){
			p++;
			continue;
		}

		if(strncmp(p, "mov", 3) == 0 ){
			current_token->next = new_token( p, 3, 0, op);
			p += 3;
			continue;
		}

		if(strncmp(p, "eax", 3) == 0 ){
			current_token->next = new_token( p, 3, 0, op);
			p += 3;
			continue;
		}

		if(*p == ','){
			current_token->next = new_token( p, 1, 0, symbol);
			p += 1;
			continue;
		}

		if(*p == '\n'){
			current_token->next = new_token( p, 1, 0, symbol);
			p += 1;
			continue;
		}
    
		if(isdigit(*p)){
			current_token->next = new_token( p, 1, 0, num);
      current_token->val = strtol(p, &p, 10);
			continue;
    }
  }
}

/*
int main(){
  tokenize("mov eax,9");
  Token *token = &head;
  while( token->next ){
    token = token->next;
    printf("%s\n", token->name);
  }
  return 0;
}
*/