#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cores.h"
#include "usuario.h"
#include "alocacao.h"
#include "verificacao.h"

void imprimir_tabuleiro(char **tabuleiro, int linha, int coluna, int linha_superior, int coluna_esquerda) {

  for(int i = 0; i < coluna; i += 2) {
    if(linha_superior < 0) {
      printf("   %d", linha_superior);
    }
    else {
      printf("    %d", linha_superior);
    } 
    linha_superior++;
  }
  printf("\n");

  for(int i = 0; i < linha; i++) {
    if(coluna_esquerda < 0) {
      printf("%d ", coluna_esquerda);
    }
    else {
      printf(" %d ", coluna_esquerda);
    }    
    for(int j = 0; j < coluna; j += 2) {
      switch(tabuleiro[i][j + 1]) {
        case '1': 
          printf("|");
          verde();
          printf("%c%c", tabuleiro[i][j], tabuleiro[i][j + 1]);
          padrao();
          printf("| ");
          break; 
        case '2': 
          printf("|");
          vermelho();
          printf("%c%c", tabuleiro[i][j], tabuleiro[i][j + 1]); 
          padrao();
          printf("| ");
          break;
        case '3':
          printf("|");
          amarelo();
          printf("%c%c", tabuleiro[i][j], tabuleiro[i][j + 1]); 
          padrao();
          printf("| ");
          break;
        case '4':
          printf("|");
          azul();
          printf("%c%c", tabuleiro[i][j], tabuleiro[i][j + 1]); 
          padrao();
          printf("| ");
          break;
        case '5': 
          printf("|");
          roxo();
          printf("%c%c", tabuleiro[i][j], tabuleiro[i][j + 1]); 
          padrao();
          printf("| ");
          break;
        case '6':
          printf("|");
          marinho();
          printf("%c%c", tabuleiro[i][j], tabuleiro[i][j + 1]); 
          padrao();
          printf("| ");
          break;
        default: 
          printf("|%c%c| ", tabuleiro[i][j], tabuleiro[i][j + 1]); 
      }      
    }
    printf("\n");
    coluna_esquerda++;
  } 
  return;
}

int opcoes(int mode) {

  int flag;
  int seleciona;
  char *entrada;

  entrada = (char *) malloc(sizeof(char) * 100);
  if(entrada == NULL) {
    vermelho();
    printf("Nao foi possivel alocar memoria\n");
    padrao();
    exit(1);
  }
 
  verde();
  printf("Opcoes:\n");
  padrao();
  printf("1 - Jogar |");
  
  if(mode == 1) {
    printf(" 2 - Trocar |");
    printf(" 3 - Passar\n");
  }
  else {
    printf(" 2 - Passar\n");
  }

  verde();
  printf("Qual a opcao desejada: ");
  padrao();

  do {
    flag = 0;
    scanf("%s", entrada);
    if(is_alpha(entrada) == 1) {
      vermelho();
      printf("Voce nao digitou um numero !!\n");
      printf("Digite o valor corretamente: ");
      padrao();      
    }
    else {
      seleciona = atoi(entrada);
      if(mode == 1) {
        if(seleciona < 1 || seleciona > 3) {
          vermelho();
          printf("Valor invalido, digite novamente: ");
          padrao();
          flag = 1;
        }
      }
      else {
        if(seleciona != 1 && seleciona != 2) {
          vermelho();
          printf("Valor invalido, digite novamente: ");
          padrao();
          flag = 1;
        }
      }
    }
  } while((is_alpha(entrada) == 1) || flag == 1);
  
  free(entrada);  

  return seleciona;
}

void cheat_mode(char **pecas, char *disponivel, int quant_disponivel) {

  char jogada[10];
  int existe = 0;
  int i, j;

  verde();
  printf("Qual peca deseja trocar: ");
  padrao();
  do {
    setbuf(stdin, NULL);  
    fgets(jogada, 10, stdin);

    for(i = 0; i < quant_disponivel; i += 2) {
      if((jogada[0] == disponivel[i]) && (jogada[1] == disponivel[i + 1])) {
        existe = 1;
        break;
      }      
    }
    if(!existe) {
      vermelho();
      printf("A peca que deseja trocar nao existe. Escolha novamente: ");
      padrao();
    }
  } while(!existe);

  // Sorteio de uma nova peça

  int linha;
  int coluna;

  srand(time(NULL));
  coluna = rand() % 36;

  for(j = 0; j < 2; j += 2) {    
    while(coluna % 2 != 0) {
      coluna = rand() % 36;      
    }

    linha = rand() % 6;

    if(pecas[linha][coluna] != ' ') {
      disponivel[i] = pecas[linha][coluna];
      disponivel[i + 1] = pecas[linha][coluna + 1];
    }
    else {
      i += -2;    // Decrementa i para procura outra posição
    }
    coluna = rand() % 36;
  }
  return;
}

void quadro_pecas(char **pecas, char **tabuleiro, char **jogadores, int num_jog, int mode) {

  int linha = 1;
  int linha_superior = 0;
  int coluna = 2;
  int coluna_esquerda = 0;
  int i, j;         // Contadores 
  char *disponivel = NULL;

  //alocar_tam(disponivel, 12);
  disponivel = (char *) malloc(sizeof(char) * 12);

  // Aloca a primeiro linha e as duas colunas iniciais 
  tabuleiro = NULL;
  tabuleiro = (char **) realloc(tabuleiro, sizeof(char *) * linha);
  if(tabuleiro == NULL) {
    vermelho();
    printf("Nao foi possivel adicinar linhas no tabuleiro\n");
    padrao();
    exit(1);
  }
  tabuleiro[0] = NULL;
  tabuleiro[0] = (char *) realloc(tabuleiro[0], sizeof(char) * coluna);   // Duas colunas (1 peça)
  if(tabuleiro[0] == NULL) {
    vermelho();
    printf("Nao foi possivel adicinar colunas no tabuleiro\n");
    padrao();
    exit(1);
  }
  tabuleiro[0][0] = ' ';
  tabuleiro[0][1] = ' ';

  char jogada[10];      // Armazena a peça digitada pelo usuario
  int pos1, pos2;       // Posição do tabuleiro impresso
  int existe = 0;       // Auxilia na verificação de existencia de peças 
  int ref_linha = 0, ref_coluna = 0;  // Relação entre o valor da posição digitada com as coordenadas das peças no vetor
  int quant_disponivel = 12; // Peças disponiveis para os jogadores em cada rodada
  int quant_jog = 0;      // Quantidade de jogadores
  int quant_pecas = 108;  // Quantidade total de peças
  int lim_linha = 1;  // Quantidade de linhas que o usuario pode escolher 
  int lim_coluna = 1; // Quantidade de colunas que o usuario pode escolher 
  int valida = 1; // Verifica se a jogada é valido
  int linha_atual = 1;
  int sair;
  int seleciona = 0;
  int flag = 0;
  
  do {    
    if(quant_jog == num_jog) {
      quant_jog = 0;
    }
    pecas_disponiveis(pecas, disponivel); // Sortei de novas peças 
    if(quant_disponivel != 0) {
      imprimir_tabuleiro(tabuleiro, linha, coluna, linha_superior, coluna_esquerda);
    }
    quant_disponivel = 12;
    sair = 0;
    do {
      do {
        if(!valida) {
          imprimir_tabuleiro(tabuleiro, linha, coluna, linha_superior, coluna_esquerda);
        }      
        printf("------------------------\n");
        verde();
        printf("Jogada de ");
        amarelo();
        printf("%s\n", jogadores[quant_jog]);
        negrito();
        printf("Pecas disponiveis: ");
        padrao();
        imprimir_disponivel(disponivel, quant_disponivel);
        seleciona = opcoes(mode);   // Opções selecionadas pelo jogador da rodada atual

        if(mode == 1 && seleciona == 2) {   // Troca das peças
          do {
            cheat_mode(pecas, disponivel, quant_disponivel);
            imprimir_tabuleiro(tabuleiro, linha, coluna, linha_superior, coluna_esquerda);
            printf("------------------------\n");
            verde();
            printf("Jogada de ");
            amarelo();
            printf("%s\n", jogadores[quant_jog]);   
            negrito();
            printf("Pecas disponiveis: ");
            padrao();
            imprimir_disponivel(disponivel, quant_disponivel);
            seleciona = opcoes(mode);   
          } while(seleciona == 2);     
        }

        if(mode == 1 && seleciona == 3) {   // Passa a vez para o proximo adversario
          sair = 1;
          break;
        }
        if(mode == 2 && seleciona == 2) {
          sair = 1;
          break;
        }

        existe = 0;
        negrito();
        printf("Escolha a peca desejada: ");
        padrao();
      
        do {    // Verifica se a peça selecionada pelo usuario existe
          setbuf(stdin, NULL);
          fgets(jogada, 10, stdin);  
          
          for(i = 0; i < quant_disponivel; i += 2) {
            if((jogada[0] == disponivel[i]) && (jogada[1] == disponivel[i + 1])) {
              existe = 1;
            }      
          }
          if(!existe) {
            vermelho();
            printf("Peca invalida, escolha novamente: "); 
            padrao();
          }
        } while(!existe);

        do {
          negrito();
          printf("Linha: ");
          padrao();
          
          char *pos_aux;
          pos_aux = (char *) malloc(sizeof(char) * 100);
          if(pos_aux == NULL) {
            vermelho();
            printf("Não foi possivel alocar memoria\n");
            padrao();
            exit(1);
          }
                  
          do {
            existe = 0;
            setbuf(stdin, NULL);
            fgets(pos_aux, 100, stdin);
            if(is_alpha(pos_aux) == 1) {
              vermelho();
              printf("Digite um numero: ");
              padrao();
              existe = 1;
            }
            else {
              pos1 = atoi(pos_aux);
              if(pos1 < coluna_esquerda || pos1 >= lim_linha) {
                vermelho();
                printf("Linha invalida, digite novamente: ");
                padrao();
                existe = 1;
              }
            }          
          } while(existe);

          negrito();
          printf("Coluna: ");
          padrao();
          do {
            existe = 0;
            scanf("%s", pos_aux);
            if(is_alpha(pos_aux) == 1) {
              vermelho();
              printf("Digite um numero: ");
              padrao();
              existe = 1;
            }
            else {
              pos2 = atoi(pos_aux);
              if(pos2 < linha_superior || pos2 >= lim_coluna) {
                vermelho();
                printf("Coluna invalida, digite novamente: ");
                padrao();
                existe = 1;
              }
            }
          } while(existe);
          
          free(pos_aux);
          // Relaciona as posições impressas com as posições da matrzi tabuleiro 

          i = ref_linha + pos1;
          j = ref_coluna + pos2;
          j = 2 * j; 

          if(tabuleiro[i][j] != ' ') {
            vermelho();
            printf("Posicao ja preenchida, insira novamente\n");
            padrao();
          }                             
        } while(tabuleiro[i][j] != ' '); 

        if(linha != 1 && tabuleiro[i][j] == ' ') {
          valida = jog_valida(tabuleiro, jogada, i, j, linha, coluna, linha_atual);  
          linha_atual = 0;
          if(!valida) {
            vermelho();
            printf("Jogada invalida\n");
            padrao();
          }
        }        
      } while(!valida);  // enquanto a jogada não for valida

      if(sair == 1) { // troca o jogador
        valida = 1;
        linha_atual = 1;
        break;
      }
      tabuleiro[i][j] = jogada[0];
      tabuleiro[i][j + 1] = jogada[1];

      // Apaga do vetor disponivel a peça jogada
      int k = 0, elimina = 0;
      for(i = 0; i < quant_disponivel; i += 2) {
        if(disponivel[i] != jogada[0] || disponivel[i + 1] != jogada[1] || elimina) {
          disponivel[k] = disponivel[i];
          disponivel[k + 1] = disponivel[i + 1];
          k += 2;      
        }
        else {
          elimina = 1;
        }        
      }
      // Reinicializa o valor das ultimas posições do vetor disponivel
      quant_disponivel += -2;
      //alocar_tam(disponivel, quant_disponivel);
      disponivel[quant_disponivel] = ' ';
      disponivel[quant_disponivel + 1]  = ' ';

      // Apaga do da matriz pecas(onde são listadas todas as peças do jogo)a peça que foi inserida do tabuleiro
      flag = 0;  
      for(i = 0; i < 6 && !flag; i++) { 
        for(j = 0; j < 36 && !flag; j += 2) {
          if(pecas[i][j] == jogada[0] && pecas[i][j + 1] == jogada[1]) {
            pecas[i][j] = ' ';
            pecas[i][j + 1] = ' ';
            quant_pecas--;
            flag = 1;
          }
        }    
      }
      
      // Verificação na linha superior
      flag = 0;
      for(i = 0; i < coluna; i++) { 
        if(tabuleiro[0][i] != ' ') { // Se a linha mais superior não estiver vazia
          //linha_superior += - 1;
          coluna_esquerda += -1;
          ref_linha++;
          flag = 1;
          break;
        }
      }
      
      if(flag) {
        linha += 1;     // Aumenta a quantidade de linhas 
        tabuleiro = (char **) realloc(tabuleiro, sizeof(char *) * linha);
        if(tabuleiro == NULL) {
          vermelho();
          printf("Nao foi possivel adicinar linhas no tabuleiro\n");
          padrao();
          exit(1);
        }
        tabuleiro[linha - 1] = NULL;
        tabuleiro[linha - 1] = (char *) realloc(tabuleiro[linha - 1], sizeof(char ) * coluna);
        if(tabuleiro[linha - 1] == NULL) {
          vermelho();
          printf("Nao foi possivel adicinar colunas no tabuleiro\n");
          padrao();
          exit(1);
        }
        
        // Inicializa as posições alocadas
        for(i = 0; i < coluna; i++) {
          tabuleiro[linha - 1][i] = ' ';
        }
        
        // Coloca as peças uma posição abaixo na matriz tabuleiro 
        int copia = linha - 2;
        for(i = 0; i < (linha - 1); i++) {
          for(j = 0; j < coluna; j += 2) {
            if(tabuleiro[copia][j] != ' ') { 
              tabuleiro[copia + 1][j] = tabuleiro[copia][j];
              tabuleiro[copia + 1][j + 1] = tabuleiro[copia][j + 1];
              tabuleiro[copia][j] = ' ';
              tabuleiro[copia][j + 1] = ' ';
            }
          }
          copia += -1;
        }
      }

      // Adiciona linha mais inferior da matriz tabuleiro
      flag = 0;
      for(i = 0; i < coluna; i++) {
        if(tabuleiro[linha - 1][i] != ' ') {  // verifica se a ultima linha da matriz tem peças 
          linha += 1;
          flag = 1;
          break;
        }
      }

      lim_linha = linha + coluna_esquerda; // limita os valores das linhas que podem ser inseridos pelo usuario

      if(flag) {
        tabuleiro = (char **) realloc(tabuleiro, sizeof(char *) * linha);   // adicinar uma linha
        if(tabuleiro == NULL) {
          vermelho();
          printf("Nao foi possivel adicinar linhas no tabuleiro\n");
          padrao();
          exit(1);
        }
        tabuleiro[linha - 1] = (char *) realloc(tabuleiro[linha - 1], sizeof(char ) * coluna);  // Aloca as colunas na nova linha alocada 
        if(tabuleiro[linha - 1] == NULL) {
          vermelho();
          printf("Nao foi possivel adicinar colunas no tabuleiro\n");
          padrao();
          exit(1);
        }
        // Inicializa a nova linha alocada
        for(i = 0; i < coluna; i++) {
          tabuleiro[linha - 1][i] = ' ';  
        }
      }

      // Verifica a coluna mais a esquerda 
      flag = 0;
      for(i = 0; i < linha; i++) {
        if(tabuleiro[i][0] != ' ') {    // Se a coluna esquerda não estiver vazia
          //coluna_esquerda += - 1;
          linha_superior += - 1;
          ref_coluna += 1;
          flag = 1;
          break;
        }
      }
      // Adiciona colunas e reorganiza as peças na matriz
      if(flag) {
        coluna += 2;      // Adiciona 2 colunas para inserir uma peça a esquerda
        for(i = 0; i < linha; i++) {
          tabuleiro[i] = (char *) realloc(tabuleiro[i], sizeof(char ) * coluna);
          if(tabuleiro[i] == NULL) {
            vermelho();
            printf("Nao foi possivel adicinar colunas no tabuleiro\n");
            padrao();
            exit(1);
          }
          // Inicializa as colunas alocadas
          tabuleiro[i][coluna - 2] = ' '; 
          tabuleiro[i][coluna - 1] = ' ';      
        }
        // Movimenta todas as peças para a direita do tabuleiro
        int copia = linha - 1;
        for(i = 0; i < (linha - 1); i++) {
          for(j = (coluna - 4); j >= 0; j += -2) {
            if(tabuleiro[copia][j] != ' ') {
              tabuleiro[copia][j + 2] = tabuleiro[copia][j];
              tabuleiro[copia][j + 3] = tabuleiro[copia][j + 1];
              tabuleiro[copia][j] = ' ';
              tabuleiro[copia][j + 1] = ' ';
            }
          }
          copia += -1;
        }
      }

      // Adiciona coluna a direita do tabuleiro
      flag = 0;
      for(i = 0; i < linha; i++) {
        if(tabuleiro[i][coluna - 1] != ' ') {
          coluna += 2; // Adicina mais duas colunas (Armazena mais uma peça) 
          lim_coluna++;
          flag = 1;
          break;
        }
      }
      
      if(flag) {
        for(i = 0; i < linha; i++) {
          tabuleiro[i] = (char *) realloc(tabuleiro[i], sizeof(char) * coluna);
          if(tabuleiro[i] == NULL) {
            vermelho();
            printf("Nao foi possivel adicionar novas colunas no tabuleiro\n");
            padrao();
            exit(1);
          }
          // Inicializa as novas colunas alocadas 
          tabuleiro[i][coluna - 2] = ' ';
          tabuleiro[i][coluna - 1] = ' ';      
        }
      }

      // Imprimir tabuleiro
      imprimir_tabuleiro(tabuleiro, linha, coluna, linha_superior,  coluna_esquerda);

      if(quant_disponivel == 0) {
        vermelho();
        printf("Nao existem mais pecas disponiveis !!\n");
        padrao();
      }
    } while(quant_disponivel > 0);
    
    quant_jog++; // proximo jogador
    linha_atual = 1;
    
  } while(quant_pecas > 0);

  free(disponivel);

  return;
}