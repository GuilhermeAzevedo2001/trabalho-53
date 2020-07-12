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
  int static first = 0;
  int static input = 0;
  int static valida = 0;
  int static set;
  
  int verifica_linha;
  int verifica_coluna;
  int quant_jog = 0;
  

  if(linha_atual == 1 || valida == 1) {
    set = 0;
    input = 1;
    if(first == 0) {
      ref_linha = 1;
      ref_coluna = 2;  
      first++;
      valida = 0;
      return 1;      
    }
    verifica_linha = ver_linha(tabuleiro, jogada, pos1, pos2, coluna);
    if(verifica_linha == 1) {
      quant_jog++;
    }
    else {
      if(verifica_linha == 0) {
        valida = 1;
        return 0;
      }
    }
    verifica_coluna = ver_coluna(tabuleiro, jogada, pos1, pos2, linha);
    if(verifica_coluna == 1) {
      quant_jog++;
    }
    else {
      if(verifica_coluna == 0) {
        ref_linha = pos1;
        ref_coluna = pos2; 
        valida = 1;
        return 0;
      }
    }
    if(quant_jog > 0) {
      valida = 0;
      return 1;
    }
    else {
      valida = 1;
      return 0;
    }
  }
  //printf("linha_atual = %d\n", linha_atual);
  //printf("input = %d\n", input);
  //printf("pos1 = %d\n", pos1);
  //printf("pos2 = %d\n", pos2);
  //printf("ref_linha = %d\n", ref_linha);
  //printf("ref_coluna = %d\n", ref_coluna);

  if(input == 1) { 
    verifica_linha = ver_linha(tabuleiro, jogada, pos1, pos2, coluna);
    if(verifica_linha == 1) {
      quant_jog++;
    }
    else {
      if(verifica_linha == 0) {
        return 0;
      }
    }
    verifica_coluna = ver_coluna(tabuleiro, jogada, pos1, pos2, linha);
    if(verifica_coluna == 1) {
      quant_jog++;
    }
    else {
      if(verifica_coluna == 0) {
        return 0;
      }
    }
    if(quant_jog > 0) {
      input++;
      printf("set = %d\n", set);
      if(pos1 == ref_linha) {
        set = 1;
        printf("set = %d\n", set);
      }
      if(pos2 == ref_coluna) {
        set = 2;
      }
      return 1;      
    }
    else {
      return 0;
    }
  }
  //printf("set = %d\n", set);
  quant_jog = 0;
  if(set == 1) {
    if(pos1 == ref_linha) {
      verifica_linha = ver_linha(tabuleiro, jogada, pos1, pos2, coluna);
      if(verifica_linha == 1) {
        quant_jog++;
      }
      else {
        if(verifica_linha == 0) {
          return 0;
        }
      }
      verifica_coluna = ver_coluna(tabuleiro, jogada, pos1, pos2, linha);
      if(verifica_coluna == 1) {
        quant_jog++;
      }
      else {
        if(verifica_coluna == 0) {
          return 0;
        }
      }
      if(quant_jog > 0) {
        return 1;
      }
      else {
        return 0;
      }
    }
  }
  if(set == 2) {
    if(pos2 == ref_coluna) {
      verifica_linha = ver_linha(tabuleiro, jogada, pos1, pos2, coluna);
      if(verifica_linha == 1) {
        quant_jog++;
      }
      else {
        if(verifica_linha == 0) {
          return 0;
        }
      }
      verifica_coluna = ver_coluna(tabuleiro, jogada, pos1, pos2, linha);
      if(verifica_coluna == 1) {
        quant_jog++;
      }
      else {
        if(verifica_coluna == 0) {
          return 0;
        }
      }
      if(quant_jog > 0) {
        return 1;
      }
      else {
        return 0;
      }
    }
  }
  return 0;
}