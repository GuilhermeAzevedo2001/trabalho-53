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

int jog_valida(char **tabuleiro, char jogada[10], int pos1, int pos2, int linha, int coluna) {

  int valida = 0, aux_valida = 0;

  // Verifica a direita de sua posição 
  if(pos2 != (coluna - 1) && tabuleiro[pos1][pos2 + 2] != ' ') {
    aux_valida++;
    if(jogada[0] == tabuleiro[pos1][pos2 + 2]) {
      if(jogada[1] != tabuleiro[pos1][pos2 + 3]) {
        valida++;
      }
    }
    else {
      if(jogada[1] == tabuleiro[pos1][pos2 + 3]) {
        valida++;
      }
    }
  }
  // Verifica a sua esquerda 
  if(pos2 != 0 && tabuleiro[pos1][pos2 - 1] != ' ') {
    aux_valida++;
    if(jogada[0] == tabuleiro[pos1][pos2 - 2]) {
      if(jogada[1] != tabuleiro[pos1][pos2 - 1]) {
        valida++;
      }
    }
    else {
      if(jogada[1] == tabuleiro[pos1][pos2 - 1]) {
        valida++;
      }
    }
  }

  // Verificação em cima da sua posição
  if(pos1 != 0 && tabuleiro[pos1 - 1][pos2] != ' ') {
    aux_valida++;
    if(jogada[0] == tabuleiro[pos1 - 1][pos2]) {
      if(jogada[1] != tabuleiro[pos1 - 1][pos2 + 1]) {
        valida++;
      }
    }
    else {
      if(jogada[1] == tabuleiro[pos1 - 1][pos2 + 1]) {
        valida++;
      }
    }
  }

  // Verifica embaixo de sua posição  
  if(pos1 != (linha - 1) && tabuleiro[pos1 + 1][pos2] != ' ') {
    aux_valida++;
    if(jogada[0] == tabuleiro[pos1 + 1][pos2]) {
      if(jogada[1] != tabuleiro[pos1 + 1][pos2 + 1]) {
        valida++;
      }
    }
    else {  // jogada[0] != tabuleiro[linha + 1][coluna]
      if(jogada[1] == tabuleiro[pos1 + 1][pos2 + 1]) {
        valida++;
      }
    }
  }

  if(valida == aux_valida) {
    return 1;
  }
  else {
    return 0;
  }
}