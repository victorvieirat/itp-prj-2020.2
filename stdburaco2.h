#ifndef stdburaco2_h
#define stdburaco2_h

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

//Usado para guarda mão do bot, mão inimiga e o lixo
typedef struct Hand{
    Cards *cartas;
    int tamanho;
}Hand;
//Guarda jogos feitos do bot e inimigos
typedef struct Sequence{
    Hand *mao;
    int linha;

}Sequence;
void readline(char *line);

Cards converte_carta(char *line);

Hand converte_entrada(char *line);

void ordernar(Hand *mao, int organiza_mele);

void imprimir(Cards carta);

void imprimir_console(int num, int naipe);

void adicionar_carta(Hand *mao, Cards nova_carta);

void baixar_jogos(Hand *mao, Sequence *jogos);

int jogo_lixo(Hand *mao, Cards lixo_matriz, Sequence *jogos);

void anexar_cartas(Hand *mao_matriz, Sequence *jogos);

int pior_carta(Hand mao);

#endif //stdburaco2_h