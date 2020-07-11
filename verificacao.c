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

int ver_coluna(char **tabuleiro, char jogada[10], int pos1, int pos2, int linha) {

  int valida = 0;
  int aux_valida = 0;
  int k;

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

  if(valida == 0 && aux_valida == 0) {
    return -1;
  }
  else {
    if(valida == aux_valida) {
      return 1;
    }
    else {
      return 0;
    }
  }
}

int ver_linha(char **tabuleiro, char jogada[10], int pos1, int pos2, int coluna) {

  int valida = 0;
  int aux_valida = 0;
  int k;
  int j;

  // Verifica a esquerda da posição seleciona 
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

  // Verifica a direita da posição seleciona 
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

  if(valida == 0 && aux_valida == 0) {
    return -1;
  }
  else {
    if(valida == aux_valida) {
      return 1;
    }
    else {
      return 0;
    }
  }
}

int jog_valida(char **tabuleiro, char jogada[10], int pos1, int pos2, int linha, int coluna, int linha_atual) {

  int static ref_linha;
  int static ref_coluna;
  int static jog;
  int static set = 0;
  int verifica_linha;
  int verifica_coluna;
  int k, j;

  if(linha_atual == 1) {
    jog = 0;
    set = 0;
    verifica_linha = ver_linha(tabuleiro, jogada, pos1, pos2, coluna);
    if(verifica_linha == 1) {
      if(pos1 == 0) {
        ref_linha = 1;
      }
      else {
        ref_linha = pos1;
      }
      
      if(pos2 == 0) {
        ref_coluna = 2;
      }
      else {
        ref_coluna = pos2;
      }
      jog++;
    }
    else {
      if(verifica_linha == 0) {
        return 0;
      }
    }
    verifica_coluna = ver_coluna(tabuleiro, jogada, pos1, pos2, linha); 
    if(verifica_coluna == 1) {
      if(pos1 == 0) {
        ref_linha = 1;
      }
      else {
        ref_linha = pos1;
      }
      if(pos2 == 0) {
        ref_coluna = 2;
      }
      else {
        ref_coluna = pos2;
      }
      jog++;
    }
    else {
      if(verifica_coluna == 0) {
        return 0;
      }
    }
    if(jog > 0) {
      return 1;
    }
    else {
      return 0;
    }
  }

  //printf("set = %d\n", set);
  //printf("ref linha - %d\n", ref_linha);
  //printf("ref coluna - %d\n", ref_coluna);
  //printf("pos1 - %d\n", pos1);
  //printf("pos2 - %d\n", pos2);
  if(ref_linha == pos1 && set == 0) {
    set = 1;
  }
  else {
    if(ref_coluna == pos2 && set == 0) {
      set = 2;
    }
  }

  if(set == 1) {
    if(ref_linha == pos1) {
      verifica_linha = ver_linha(tabuleiro, jogada, pos1, pos2, coluna);
      verifica_coluna = ver_coluna(tabuleiro, jogada, pos1, pos2, linha); 
      if(verifica_linha == 1 && (verifica_coluna == 1 || verifica_coluna == -1)) {
        return 1;
      }
      else {        
        return 0;        
      }
    }
    else {
      return 0;
    }
  }
  if(set == 2) {
    if(ref_coluna == pos2) {
      verifica_linha = ver_linha(tabuleiro, jogada, pos1, pos2, coluna);
      verifica_coluna = ver_coluna(tabuleiro, jogada, pos1, pos2, linha); 
      if((verifica_linha == 1 || verifica_linha == -1) && verifica_coluna == 1) {
        return 1;
      }
      else {        
        return 0;        
      }
    }
    else {
      return 0;
    }
  }
  return 0;
}