#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stdburaco.h"

#define MAX_LINE 400

#define ID_SIZE 10

int main() {
	Cards *mao_atual, carta_nova, top_morto, *mao_morto;
	int quantidade = 11, tam_morto =0;
	int **matriz , linha_matriz =0;
	int indice;
	
	char line[MAX_LINE];   // dados temporários
	char myId[ID_SIZE];    // identificador do bot em questão
	setbuf(stdin, NULL);   
	setbuf(stdout, NULL);  
	setbuf(stderr, NULL);
							// DADOS DO INÍCIO DA PARTIDA
	readline(line);         // lê os identificadores dos jogadores
	readline(line);         // lê o identificador do bot (seu id)
	strncpy(myId, line, ID_SIZE); // guarda para uso futuro
	readline(line);         // lê as cartas que o bot tem na mão
	mao_atual = converte_entrada(line, &quantidade);
	readline(line);         // lê a carta inicial da pilha de descarte.

	char *aux1;
	while(1){              // DADOS DURANTE A PARTIDA
		do {                  
			readline(line);     
			if(strstr(line, "DISCARD") != NULL){
				aux1 = strtok(line," ");
				aux1= strtok(NULL," ");
				top_morto = converte_carta(aux1);
			}
	} while (strcmp(line, myId)); // sai do laço quando for a sua vez!

	if(jogo_morto(mao_atual, &quantidade, top_morto, &matriz, &linha_matriz)){
		ordernar(mao_atual, &quantidade);
		readline(line);
		mao_morto = converte_entrada(line, &tam_morto); 
		mao_atual = realloc(mao_atual, sizeof(Cards)  * (quantidade+tam_morto));
		for(int a=0; a< tam_morto; a++){
			mao_atual[quantidade+a].numero = mao_morto[a].numero;
			mao_atual[quantidade+a].naipe = mao_morto[a].naipe;
		}
		quantidade += tam_morto;
	}else{
		printf("GET_STOCK\n");   // envia a ação para puxar uma carta
		readline(line);			 // recebe a carta que puxou
		carta_nova = converte_carta(line);  
    	adicionar_carta(mao_atual, carta_nova, &quantidade); 
	}     

    ordernar(mao_atual, &quantidade);  
	anexar_cartas(mao_atual, &quantidade, &matriz, &linha_matriz);
	ordernar(mao_atual, &quantidade);  
    baixar_jogos(mao_atual, &quantidade, &matriz, &linha_matriz);
	ordernar(mao_atual, &quantidade);  
	
	indice = pior_carta(mao_atual, &quantidade);  
	printf("DISCARD ");
	imprimir(mao_atual[indice].numero,mao_atual[indice].naipe);
	mao_atual[indice].naipe = Removido;
	ordernar(mao_atual, &quantidade);
	printf("\n");
	
  }
	free(mao_atual);
	free(mao_morto);
	for(int a=0; a< linha_matriz;a++)
		free(matriz[a]);
	free(matriz);
  return 0;
}