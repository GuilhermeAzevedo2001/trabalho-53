void imprimir_tabuleiro(char **tabuleiro, int linha, int coluna, int linha_superior, int coluna_esquerda);

int opcoes(int mode);

void troca_peca(char **pecas, char *disponivel, int quant_disponivel);

void quadro_pecas(char **pecas, char **tabuleiro, char **jogadores, int num_jog, int mode);

void cont_pontos(char **tabuleiro, int pos1, int pos2, int linha, int coluna, int *pontos, int quant_jog);

void imprimir_disponivel(char *disponivel, int quant);

void pecas_disponiveis(char **pecas, char *disponivel, int quant, int num_jog);