#include <stdio.h>
#include <stdlib.h>
#include "cores.h"

void alocar_tam(char *vet, int tam) {

  vet = (char *) realloc(vet, sizeof(char) * tam);
  if(vet == NULL) {
    vermelho();
    printf("Não foi possivel alocar memoria\n");
    padrao();
    exit(1);
  }
  return;
}

void desaloca_tam(char *vet) {

  free(vet);

  return;
}