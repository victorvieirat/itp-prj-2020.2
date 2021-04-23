#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stdburaco2.h"

#define MAX_LINE 400

#define ID_SIZE 10

int main() {
	Cards carta_nova, top_morto;
	int indice;
	Hand mao_morto, mao_atual, aux_mao, lixo;
	Sequence jogo_adv, jogo_meu;

	jogo_adv.mao = malloc(sizeof(Hand));
	jogo_meu.mao = malloc(sizeof(Hand));
	lixo.cartas = malloc(sizeof(Cards));

	jogo_adv.linha = 0;
	jogo_meu.linha = 0;
	lixo.tamanho =1;

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
	mao_atual = converte_entrada(line);

	readline(line);         // lê a carta inicial da pilha de descarte.
	lixo.cartas[0] = converte_carta(line);

	char *aux1, *aux2, line_copy[MAX_LINE];
	const char ch = '[';
	while(1){              // DADOS DURANTE A PARTIDA
		do{                  
			readline(line);     
			//Oponente pegou morto
			if(strstr(line, "GET_DISCARD") != NULL){
				aux1 = strchr(line, ch);
				jogo_adv.linha++;
				if(jogo_adv.linha != 1)
					jogo_adv.mao = realloc(jogo_adv.mao, sizeof(Hand)  * jogo_adv.linha);
				jogo_adv.mao[jogo_adv.linha-1] = converte_entrada(aux1);
				adicionar_carta(&jogo_adv.mao[jogo_adv.linha-1], lixo.cartas[lixo.tamanho-1]);
				lixo.tamanho = 0;
			}
			//Carta descartada
			else if(strstr(line, "DISCARD") != NULL){
				aux1 = strtok(line," ");
				aux1= strtok(NULL," ");
				top_morto = converte_carta(aux1);
				adicionar_carta(&lixo, top_morto);
			}
			//Novo jogo feito pelo oponente
			else if(strstr(line, "MELD_NEW") != NULL){
				aux1 = strchr(line, ch);
				jogo_adv.linha++;
				if(jogo_adv.linha != 1)
					jogo_adv.mao = realloc(jogo_adv.mao, sizeof(Hand)  * jogo_adv.linha);
				jogo_adv.mao[jogo_adv.linha-1] = converte_entrada(aux1);
				ordernar(&jogo_adv.mao[jogo_adv.linha-1],1);
			}
			//Oponente anexou carta aos jogos feitos
			else if(strstr(line, "MELD_JOIN") != NULL){
				strcpy(line_copy, line);
				aux2 = strtok(line_copy," ");
				aux2= strtok(NULL," ");
				indice = atoi(aux2);
				aux1 = strchr(line, ch);
				aux_mao = converte_entrada(aux1);
				for(int a=0; a < aux_mao.tamanho;a++){
					adicionar_carta(&jogo_adv.mao[indice], aux_mao.cartas[a]); 
				}
				ordernar(&jogo_adv.mao[indice],1);
			}	
		} while (strcmp(line, myId)); // sai do laço quando for a sua vez!
		if(jogo_lixo(&mao_atual, top_morto ,&jogo_meu)){ //Ta aqui o problema
			lixo.tamanho = 0;
			ordernar(&mao_atual,0);
			readline(line);
			mao_morto = converte_entrada(line); 
			if(strlen(line)> 4){
				mao_atual.cartas = realloc(mao_atual.cartas, sizeof(Cards)  * (mao_atual.tamanho+mao_morto.tamanho));
				for(int a=0; a< mao_morto.tamanho; a++){
					mao_atual.cartas[mao_atual.tamanho+a].numero = mao_morto.cartas[a].numero;
					mao_atual.cartas[mao_atual.tamanho+a].naipe = mao_morto.cartas[a].naipe;
				}
				mao_atual.tamanho += mao_morto.tamanho;
			}
		}else{
			printf("GET_STOCK\n");   // envia a ação para puxar uma carta
			readline(line);			 // recebe a carta que puxou
			carta_nova = converte_carta(line);  
			adicionar_carta(&mao_atual, carta_nova); 
		}     
		ordernar(&mao_atual,0);  
		anexar_cartas(&mao_atual,&jogo_meu);
		ordernar(&mao_atual,0);  
		baixar_jogos(&mao_atual, &jogo_meu);
		ordernar(&mao_atual,0);  

		//Imprimir jogos feitos
		/*
		fprintf(stderr, "S: ");	
		for(int a=0; a<jogo_meu.linha;a++){
			for(int b=0; b<jogo_meu.mao[a].tamanho;b++){
				imprimir_console(jogo_meu.mao[a].cartas[b].numero, jogo_meu.mao[a].cartas[b].naipe);
			}
			fprintf(stderr, "\n");
		}
		fprintf(stderr, ":E\n");
		*/
		
		indice = pior_carta(mao_atual);  
		printf("DISCARD ");
		imprimir(mao_atual.cartas[indice]);
		adicionar_carta(&lixo, mao_atual.cartas[indice]);
		mao_atual.cartas[indice].naipe = Removido;
		if(mao_atual.tamanho > 1){
			ordernar(&mao_atual,0);
		}
		printf("\n");
	}
	return 0;
}


/*
		//Impressão dos jogos do aponente
		fprintf(stderr, "Start\n");	
		for(int a=0; a<jogo_adv.linha;a++){
				for(int b=0; b<jogo_adv.mao[a].tamanho; b++){
					imprimir_console(jogo_adv.mao[a].cartas[b].numero, jogo_adv.mao[a].cartas[b].naipe);
				}
				fprintf(stderr, "\n");
			}	
		fprintf(stderr, "End\n");	
		
		//Imprimir lixo
		fprintf(stderr, "Tam %d Start: ", lixo.tamanho);	
		for(int a=0; a<lixo.tamanho;a++)
			imprimir_console(lixo.cartas[a].numero, lixo.cartas[a].naipe);
		fprintf(stderr, " :End\n");
		
		//Imprimir mão
		fprintf(stderr, "Mao: ");	
		for(int a=0; a<mao_atual.tamanho;a++){
			imprimir_console(mao_atual.cartas[a].numero, mao_atual.cartas[a].naipe);
		}
		fprintf(stderr, ":E\n");
*/