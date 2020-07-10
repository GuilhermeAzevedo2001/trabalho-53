#include<stdio.h>

// Altera a cor do texto para a padrao
void padrao(void) {
    printf("\033[0m");
}

// Altera a cor do texto para vermelho
void vermelho(){
    printf("\033[1;31m");
}

// Altera a cor do texto para verde
void verde(){
    printf("\033[1;32m");
}

// Altera a cor do texto para amarelo 
void amarelo(){
    printf("\033[1;33m");
}

// Altera a cor do texto para azul
void azul(){
    printf("\033[1;34m");
}

void roxo(){
    printf("\033[1;35m");
}

void marinho(){
    printf("\033[1;96m");
}

void negrito(void) {
    printf("\033[1;37m");
}