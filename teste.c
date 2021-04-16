#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#include "stdburaco.h"

#define MAX_LINE 200

void readline(char *line) {
  fgets(line, MAX_LINE, stdin);
  int l = strlen(line) - 1;
  if(line[l] == '\n') {
    line[l] = '\0';
  }
  return;
}

void testando(char *line){
    char * pch;
    int cont =0;
    pch=strchr(line,'s');
    while (pch!=NULL){
        cont++;
        pch=strchr(pch+1,'s');
    }
    printf("Há %d espaços", cont);
    return;
}
int main(){
    char *line;
    readline(line);
    testando(line);
    return 0;
}
