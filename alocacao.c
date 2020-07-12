#include <stdio.h>
#include <stdlib.h>
#include "cores.h"

void alocar_int(int *vet, int tam) {

  // Alocação de "tam" posiçoes
  vet = (int *) malloc(sizeof(int) * tam);
  if(vet == NULL) {
    vermelho();
    printf("Não foi possivel alocar memoria\n");
    padrao();
    exit(1);
  }
  // Iniciliza as posiçoes alocada 
  for(int i = 0; i < tam; i++) {
    vet[i] = 0;
  }
  
  return;
}

void desaloca_int(int *vet) {

  free(vet);

  return;
}