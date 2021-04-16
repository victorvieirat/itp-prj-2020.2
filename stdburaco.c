#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stdburaco.h"

void readline(char *line) {
  fgets(line, MAX_LINE, stdin);
  int l = strlen(line) - 1;
  if(line[l] == '\n') {
    line[l] = '\0';
  }
}

Cards converte_carta(char *line){
    char  aux1[2];
    Cards carta;
    if(strstr(line,"♥")){
            carta.naipe= Copas;
        }else if(strstr(line,"♠")){
            carta.naipe= Espadas;
        }else if(strstr(line,"♣")){
            carta.naipe= Paus;
        }else if(strstr(line,"♦")){
            carta.naipe= Ouro;
        } 
        
        memset(aux1, '\0', sizeof(aux1));
        if(strlen(line) == 5){
            strncpy(aux1, line, 2);
        }else{
            strncpy(aux1, line, 1);
        }

        if(strstr(aux1,"A"))
            carta.numero = 14;
        else if(strstr(aux1,"K"))
            carta.numero = 13;
        else if(strstr(aux1,"Q"))
            carta.numero = 12;
        else if(strstr(aux1,"J"))
            carta.numero = 11;
        else
            carta.numero = atoi(aux1);
    return carta;
}

Cards* converte_entrada(char *line, int *tamanho){
    char *aux1;
    int indice =0, num_espacos =0;
    Cards *mao;
    
    for(int a=strlen(line)-1;a >= 0;a--){
        if(line[a] == ' ')
            num_espacos++;
    }
    (*tamanho) = num_espacos -1;
    mao = malloc(sizeof(Cards) * (*tamanho));
    aux1 = strtok(line,"[");
    aux1 = strtok(aux1," ");
    
    while(strstr(aux1, "]") == NULL){
        mao[indice] = converte_carta(aux1);
        aux1= strtok(NULL," ");
        indice++;
    }
    return mao;
}

void ordernar(Cards *mao, int *tamanho){
    int num_aux, naip_aux;
    for(int a=0;a<(*tamanho); a++){
        for(int b=a;b<(*tamanho); b++){
             if(mao[a].numero> mao[b].numero){
                naip_aux = mao[b].naipe;
                num_aux = mao[b].numero;
                mao[b].naipe= mao[a].naipe;
                mao[b].numero = mao[a].numero;
                mao[a].naipe= naip_aux;
                mao[a].numero = num_aux;
            }
            if(mao[a].naipe> mao[b].naipe){
                naip_aux = mao[b].naipe;
                num_aux = mao[b].numero;
                mao[b].naipe= mao[a].naipe;
                mao[b].numero = mao[a].numero;
                mao[a].naipe= naip_aux;
                mao[a].numero = num_aux;
            }
        }
    }
    num_aux =0;
    for(int a = (*tamanho)-1;mao[a].naipe ==Removido;a--)
        num_aux++;
    if(num_aux){
        mao = realloc(mao, sizeof(Cards)  * (*tamanho)-num_aux);
        (*tamanho)-= num_aux;
    } 
}

void imprimir(int num, int naipe){
    if(num <= 10){
        printf("%d", num);
    }else{
        switch (num){
            case 11:
                printf("J");
                break;
            case 12:
                printf("Q");
                break;
            case 13:
                printf("K");
                break;
            case 14:
                printf("A");
                break;
        }
    }
    switch (naipe){
        case Copas:
            printf("♥");
            break;
        case Ouro:
            printf("♦");
            break;
        case Espadas:
            printf("♠");
            break;
        case Paus:
            printf("♣");
            break;
    }
    return;
}

void imprimir_console(int num, int naipe){
    if(num <= 10){
        fprintf(stderr, "%d", num);
    }else{
        switch (num){
            case 11:
                fprintf(stderr, "J");
                break;
            case 12:
                fprintf(stderr, "Q");
                break;
            case 13:
                fprintf(stderr, "K");
                break;
            case 14:
                fprintf(stderr, "A");
                break;
        }
    }
    switch (naipe){
        case Copas:
            fprintf(stderr, "♥ ");
            break;
        case Ouro:
            fprintf(stderr, "♦ ");
            break;
        case Espadas:
            fprintf(stderr, "♠ ");
            break;
        case Paus:
            fprintf(stderr, "♣ ");
            break;
    }
    return;
}

void adicionar_carta(Cards *mao, Cards nova_carta, int *tamanho){
    mao = realloc(mao, sizeof(Cards)  * (*tamanho)+1);
    mao[(*tamanho)].numero = nova_carta.numero;
    mao[(*tamanho)].naipe = nova_carta.naipe;
    (*tamanho)++;
    return;
}

void baixar_jogos(Cards *mao,int *tamanho, int ***matriz, int *linha_matriz){
    int sequencia = 1;
    for(int a=0;a <(*tamanho);a++){
        if(mao[a].naipe == mao[a+1].naipe && (mao[a].numero - mao[a+1].numero) == -1){
            sequencia++;
        }else{
            if(sequencia >= 3){
                printf("MELD_NEW [");
                for(int b= a-(sequencia-1); b<=a;b++){
                    printf(" ");
                    imprimir(mao[b].numero, mao[b].naipe);
                }
                printf(" ]\n");
                
                (*linha_matriz)++;
                if((*linha_matriz) == 1){
                    (*matriz) = calloc(1,sizeof(int*));
	                (*matriz)[0] = calloc(14,sizeof(int));
                }else{
                    (*matriz) = realloc((*matriz), sizeof(int*) *(*linha_matriz));
                    (*matriz)[(*linha_matriz)-1] = calloc(14,sizeof(int));
                }
                (*matriz)[(*linha_matriz)-1][0] = mao[a].naipe;
                for(int b= a-(sequencia-1); b<=a;b++){
                    (*matriz)[(*linha_matriz)-1][mao[b].numero-1] =1;
                    mao[b].naipe = Removido;
                }
                
                ordernar(mao, tamanho);
                a =0;
            }
            sequencia =1 ;
        }  
    }
    return;
}

int jogo_morto(Cards *mao,int *tamanho, Cards morto, int ***matriz, int *linha_matriz){
    for(int a=0;a <(*tamanho)-1; a++){
        if(morto.naipe == mao[a].naipe && mao[a].naipe == mao[a+1].naipe){
            if((morto.numero + 1 == mao[a].numero && mao[a].numero +1 == mao[a+1].numero) ||
               (mao[a].numero +1 ==morto.numero  && morto.numero +1 ==  mao[a+1].numero) ||
               (mao[a].numero +1 ==mao[a+1].numero  &&  mao[a+1].numero +1 == morto.numero)){
                printf("GET_DISCARD [ ");
                imprimir(mao[a].numero, mao[a].naipe);
                printf(" ");
                imprimir(mao[a+1].numero, mao[a+1].naipe);
                printf(" ]\n");
                
                (*linha_matriz)++;
                if((*linha_matriz) == 1){
                    (*matriz) = calloc(1,sizeof(int*));
	                (*matriz)[0] = calloc(14,sizeof(int));
                }else{
                    (*matriz) = realloc((*matriz), sizeof(int*) *(*linha_matriz));
                    (*matriz)[(*linha_matriz)-1] = calloc(14,sizeof(int));
                }
                (*matriz)[(*linha_matriz)-1][0] = mao[a].naipe;
                (*matriz)[(*linha_matriz)-1][mao[a].numero-1] = 1;
                (*matriz)[(*linha_matriz)-1][mao[a+1].numero-1] = 1;
                (*matriz)[(*linha_matriz)-1][morto.numero -1] = 1;
                
                mao[a].naipe = Removido;
                mao[a+1].naipe = Removido;
                return 1;
            }
        }
    }
    return 0;
}

void anexar_cartas(Cards *mao,int *tamanho, int ***matriz, int *linha_matriz){
    Suit linha_naipe;
    for(int a=0;a <(*tamanho);a++){ //Passa pelas cartas da mao
        for(int b=0; b<(*linha_matriz); b++){ //Passa pelos jogos feitos
        linha_naipe = (*matriz)[b][0];
            if(mao[a].naipe == linha_naipe){ // Se tem o mesmo naipe...
                if(mao[a].numero < 14 && a>=0 &&
                   (*matriz)[b][mao[a].numero] != 0 &&
                   (*matriz)[b][mao[a].numero-1] == 0){
                    printf("MELD_JOIN %d [ ", b);
                    do{
                        (*matriz)[b][mao[a].numero-1] = 1;
                        imprimir(mao[a].numero, mao[a].naipe);
                        printf(" ");
                        mao[a].naipe = Removido;
                        a--;
                    } while (a >= 0 && mao[a].naipe ==  linha_naipe 
                            && (*matriz)[b][mao[a].numero-1] == 0 
                            && mao[a+1].numero +1==mao[a+1].numero);
                    printf("]\n");
                    ordernar(mao, tamanho);
                }else if(mao[a].numero > 2 && a>=0 &&
                         (*matriz)[b][mao[a].numero-2] != 0 &&
                         (*matriz)[b][mao[a].numero-1] == 0 ){
                    printf("MELD_JOIN %d [ ", b);
                    do{
                        (*matriz)[b][mao[a].numero-1] = 1;
                        imprimir(mao[a].numero, mao[a].naipe);
                        printf(" ");
                        mao[a].naipe = Removido;
                        a++;
                    } while (a < (*tamanho) && mao[a].naipe == linha_naipe && 
                             (*matriz)[b][mao[a].numero-1] == 0 && mao[a+1].numero +1==mao[a+1].numero);
                    printf("]\n");
                    ordernar(mao, tamanho);           
                }

            }
        }
    }
    return;
}

int pior_carta(Cards *mao, int *tamanho){
    int indice = -1, maior_diferenca=0;
    for(int a=0; a< (*tamanho); a++){
        if(indice == -1 && mao[a].naipe == mao[a+1].naipe){
            indice = a;
            maior_diferenca = mao[a+1].numero -mao[a].numero;
        }else if(a==0 && mao[a].naipe != mao[a+1].naipe ||(a == (*tamanho) -1 && mao[a].naipe != mao[a-1].naipe)){
            return a;
        }else if(mao[a].naipe != mao[a-1].naipe && mao[a].numero -mao[a-1].numero > maior_diferenca){
            indice = a;
            maior_diferenca = mao[a].numero -mao[a-1].numero;
        }else if(mao[a].naipe != mao[a+1].naipe && mao[a+1].numero -mao[a].numero > maior_diferenca){
            indice = a;
            maior_diferenca = mao[a+1].numero -mao[a].numero;
        }
    }
    return indice;
}



/*

- Funcionar bom melé
- Priorizar o uso do melé nos jogos com mesmo naipe;
- Buscar formas jogos novos quando uma canastra já estiver abaixada;
- Priorizar jogos com morto:
    -Evitar usar melé para baixar jogos da mão;
(Extra)
 -Segurar os jogos que estão na mão o maior tempo possível;
- Priorizar descartas cartas semelhantes ao do oponente;

1 - Get discard usando mele
2 - Meld new usando mele
3 - Implementar "pior_carta" para levar em consideração possíveis jogos do lixo.
4- Struct com vetor e tamanho (opcional).
*/