#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "tabuleiro.h"
#include "cores.h"

int is_alpha(char *s) {     // Verifica numeros e letras
  
  while(*s) {
    if(isalpha(*s)) {
      return 1;
    }    
    else {
      s++;
    }      
  }
  return 0; 
}

void preenche(char **pecas) {
  
  unsigned int letra = 65;      // Caracteres letras 
  unsigned int numero = 49;     // Caracteres numero (a partir de 1) 
  int i, j;
  int k = 0;
  
  //numeracao das pecas
  for(i = 0; i < 6; i++) {
    for(j = 0; j < 36; j += 2) {
      pecas[i][j] = letra;
      pecas[i][j+1] = numero;
      k++;
      if(k == 3) {
        numero++;
        k = 0;
      }
    }
    numero = 49;
    letra++;
  }
  return;
}

void usuario(void) {

// Insercao dos usuarios 
  int num_jog = 0;
  char *quant_jog;
  char **jogadores;
  char **tabuleiro;
  char **pecas;

  quant_jog = (char *) malloc(sizeof(char) * 100);
  if(quant_jog == NULL) {
    vermelho();
    printf("Nao foi possivel alocar memoria\n");
    padrao();
    exit(1);
  }
  
  //inicializacao da quantidade de jogadores
  printf("Quantidade de jogadores: ");
  do {
    scanf("%s", quant_jog);
    if(is_alpha(quant_jog) == 1) {
      vermelho();
      printf("Voce nao digitou um numero !!\n");
      printf("Digite o valor corretamente: ");
      padrao();      
    }
    else {
      num_jog = atoi(quant_jog);
      if(num_jog < 1 || num_jog > 4) {
        vermelho();
        printf("Quantidade de jogadores invalida, digite novamente: ");
        padrao();      
      }
    }
  } while((is_alpha(quant_jog) == 1) || (num_jog < 1 || num_jog > 18));

  free(quant_jog);    

  jogadores = (char **) malloc(sizeof(char *) * num_jog);
  if(jogadores == NULL) {
    vermelho();
    printf("Nao foi possivel alocar memoria!");
    padrao();
    exit(1);
  }
  for(int i = 0; i < num_jog; i++) {
    jogadores[i] = (char *) malloc(sizeof(char) * 100);
    if(jogadores[i] == NULL) {
      vermelho();
      printf("Nao foi possivel alocar memoria!");
      padrao();
      exit(1);      
    }
  }
  pecas = (char **) malloc(sizeof(char *) * 6);
  if(pecas == NULL) {
    vermelho();
    printf("Nao foi possivel alocar memoria!");
    padrao();
    exit(1);
  }
  for(int i = 0; i < 6; i++) {
    pecas[i] = (char *) malloc(sizeof(char) * 36);
    if(pecas[i] == NULL) {
      vermelho();
      printf("Nao foi possivel alocar memoria!");
      padrao();
      exit(1);
    }
  }
  
  //insercao de nomes para os jogadores
  int num_letra;
  for(int i = 0; i < num_jog; i++) {
    verde();
    printf("Nome do jogador #%d: ", i + 1);
    padrao();

    setbuf(stdin, NULL);
    fgets(jogadores[i], 100, stdin);
    
    num_letra = strlen(jogadores[i]);
    jogadores[i][strlen(jogadores[i]) - 1] = '\0';

    jogadores[i] = (char *) realloc(jogadores[i] ,sizeof(char) * (num_letra + 1)); // Conta o '\0'
    if(jogadores[i] == NULL) {
      vermelho();
      printf("Nao foi possivel alocar memoria!");
      padrao();
      exit(1);
    }
  }
  
  //inicializacao para jogar em cheat mode
  verde();
  printf("Desejam jogar em 'Cheat mode'?\n");
  padrao();
  printf("1 - Sim\n");
  printf("2 - Não\n");
  verde();
  printf("Confirmacao: ");
  padrao();

  char *seleciona;
  int mode;
  seleciona = (char *) malloc(sizeof(char) * 100);
  if(seleciona == NULL) {
    vermelho();
    printf("Não foi possivel alocar memoria\n");
    padrao();
    exit(1);
  }
  
  //condicionais para entradas de erro
  do {
    scanf("%s", seleciona);    
    if(is_alpha(seleciona) == 1) {
      vermelho();
      printf("Digite o valor correto: ");
      padrao();      
    }
    else {
      mode = atoi(seleciona);
      if(mode != 1 && mode != 2) {
        vermelho();
        printf("Valor invalido, digite novamente: ");
        padrao(); 
      }
    }
  } while(is_alpha(seleciona) == 1 || (mode != 1 && mode != 2));

  free(seleciona);

  preenche(pecas);  // preenche a matriz com as peças do jogo
  quadro_pecas(pecas, tabuleiro, jogadores, num_jog, mode);
  
  for(int i = 0; i < num_jog; i++) {
    free(jogadores[i]);
  }
  for(int i = 0; i < 6; i++) {
    free(pecas[i]);
  }
  free(pecas);
  free(jogadores);

  return;  
}