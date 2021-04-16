#ifndef stdburaco_h
#define stdburaco_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 400

typedef enum Suit{
    Paus,
    Espadas,
    Copas,
    Ouro,
    Removido
} Suit; 

typedef struct Cards{
    int numero;
    Suit naipe;
}Cards;

typedef struct Vcards{
    Cards *cartas;
    int tamanho;
}Vcards;
void readline(char *line);

Cards converte_carta(char *line);

Cards* converte_entrada(char *line, int *tamanho);

void ordernar(Cards *mao, int *tamanho);

void imprimir(int num, int naipe);

void imprimir_console(int num, int naipe);

void adicionar_carta(Cards *mao, Cards nova_carta, int *tamanho);

void baixar_jogos(Cards *mao,int *tamanho, int ***matriz, int *linha);

int jogo_morto(Cards *mao,int *tamanho, Cards morto, int ***matriz, int *linha_matriz);

void anexar_cartas(Cards *mao,int *tamanho, int ***matriz, int *linha);

int pior_carta(Cards *mao, int *tamanho);

#endif //stdburaco_h