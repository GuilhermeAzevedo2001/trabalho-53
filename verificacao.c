#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Recebe como parametro o tabuleiro
*  onde são dispostas todas as peças 
*  e a linha e coluna onde será inserida
*  a peça atual 
*/

// pos1 = i     pos2 = j     , linha é quant de linhas da matriz

int jog_valida(char **tabuleiro, char jogada[10], int pos1, int pos2, int linha, int coluna, int linha_atual) {

  int static ref_linha;
  int static ref_coluna;
  int valida = 0;
  int aux_valida = 0;
  int k, j;

  if(linha_atual == 1) {
    ref_linha = pos1;
    ref_coluna = pos2;
  }
  //printf("ref_pos = %d\n", ref_pos);
  //printf("linha_atual = %d\n", linha_atual);

  // Verifica a direita de sua posição 
  k = 2;
  j = 3;
  while(pos2 != (coluna - 2) && tabuleiro[pos1][pos2 + k] != ' ') {
    aux_valida++;
    if(jogada[0] == tabuleiro[pos1][pos2 + k]) {
      if(jogada[1] != tabuleiro[pos1][pos2 + j]) {
        valida++;
      }
    }
    else {
      if(jogada[1] == tabuleiro[pos1][pos2 + j]) {
        valida++;
      }
    }
    k += 2;
    j += 2;
  }

  // Verifica a sua esquerda 
  k = 2;
  j = 1;
  while(pos2 != 0 && tabuleiro[pos1][pos2 - k] != ' ') {
    aux_valida++;
    if(jogada[0] == tabuleiro[pos1][pos2 - k]) {
      if(jogada[1] != tabuleiro[pos1][pos2 - j]) {
        valida++;
      }
    }
    else {
      if(jogada[1] == tabuleiro[pos1][pos2 - j]) {
        valida++;
      }
    }
    k += 2;
    j += 2;
  }

  // Verificação em cima da sua posição
  k = 1;
  while(pos1 != 0 && tabuleiro[pos1 - k][pos2] != ' ') {
    aux_valida++;
    if(jogada[0] == tabuleiro[pos1 - k][pos2]) {
      if(jogada[1] != tabuleiro[pos1 - k][pos2 + 1]) {
        valida++;
      }
    }
    else {
      if(jogada[1] == tabuleiro[pos1 - k][pos2 + 1]) {
        valida++;
      }
    }
    k++;
  }

  // Verifica embaixo de sua posição  
  k = 1;
  while(pos1 != (linha - 1) && tabuleiro[pos1 + k][pos2] != ' ') {
    aux_valida++;
    if(jogada[0] == tabuleiro[pos1 + k][pos2]) {
      if(jogada[1] != tabuleiro[pos1 + k][pos2 + 1]) {
        valida++;
      }
    }
    else {  // jogada[0] != tabuleiro[linha + 1][coluna]
      if(jogada[1] == tabuleiro[pos1 + k][pos2 + 1]) {
        valida++;
      }
    }
    k++;
  }

  if(valida == aux_valida) {
    return 1;
  }
  else {
    return 0;
  }
}