#include <stdio.h>
#include "cores.h"
#include "usuario.h"

int main(void) {
  
  // Apresentação do jogo 
  printf("Bem vindo ao jogo ");
  verde();
  printf("Qwirkle.\n");
  padrao();
  printf("Para iniciar, insira a quantidade de jogadores e seus respectivos nomes.\n(Obs: limitado a um maximo de 18 jogadores.)\n");
  
  usuario();  // Inserir os usuarios e dar continuidade ao jogo

  return 0;
}